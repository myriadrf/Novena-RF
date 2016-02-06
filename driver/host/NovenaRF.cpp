////////////////////////////////////////////////////////////////////////
// SoapySDR module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#include "NovenaRF.hpp"
#include "xilinx_user_gpio.h"
#include "novena_rf.h" //shared kernel module header
#include <SoapySDR/Registry.hpp>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h> //mmap
#include <unistd.h> //close

/***********************************************************************
 * Device interface
 **********************************************************************/
NovenaRF::NovenaRF(const std::string &fpgaImage):
    _novena_fd(-1),
    _irq_fd(-1),
    _regs(nullptr),
    _framer0_mem(nullptr),
    _deframer0_mem(nullptr),
    _lms6ctrl(nullptr)
{
    setvbuf(stdout, NULL, _IOLBF, 0);

    //open the file descriptor for the novena rf module
    _novena_fd = open(NOVENA_RF_DEVFS, O_RDWR | O_SYNC);
    if (_novena_fd <= 0)
    {
        throw std::runtime_error("Failed to open " NOVENA_RF_DEVFS ": " + std::string(strerror(errno)));
    }

    //open the sysfs gpio used for IRQ
    gpio_export(FPGA_IRQ_GPIO);
    _irq_fd = gpio_fd_open(FPGA_IRQ_GPIO);
    if (_irq_fd <= 0)
    {
        throw std::runtime_error("Failed to open FPGA_IRQ_GPIO: " + std::string(strerror(errno)));
    }
    gpio_set_edge(FPGA_IRQ_GPIO, "rising");

    //initialize the EIM configuration
    int ret = ioctl(_novena_fd, NOVENA_RF_EIM_INIT);
    if (ret != 0)
    {
        throw std::runtime_error("Failed to initialize EIM " + std::string(strerror(errno)));
    }

    //map the register space
    _regs = mmap(NULL, NOVENA_RF_REGS_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, _novena_fd, NOVENA_RF_MAP_OFFSET(NOVENA_RF_REGS_PAGE_NO));
    if (_regs == MAP_FAILED)
    {
        throw std::runtime_error("Failed to map regs " + std::string(strerror(errno)));
    }

    //load the fpga image and verify version
    this->fpgaCheckAndLoad(fpgaImage);

    //self test on register space and bus
    this->selfTestBus();

    //clear hardware time
    this->setHardwareTime(0, "");

    //map the RXD and TXD memory space
    _framer0_mem = mmap(NULL, NOVENA_RF_FRAMER0_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, _novena_fd, NOVENA_RF_MAP_OFFSET(NOVENA_RF_FRAMER0_PAGE_NO));
    if (_framer0_mem == MAP_FAILED)
    {
        throw std::runtime_error("Failed to map framer memory " + std::string(strerror(errno)));
    }
    _deframer0_mem = mmap(NULL, NOVENA_RF_DEFRAMER0_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, _novena_fd, NOVENA_RF_MAP_OFFSET(NOVENA_RF_DEFRAMER0_PAGE_NO));
    if (_deframer0_mem == MAP_FAILED)
    {
        throw std::runtime_error("Failed to map deframer memory " + std::string(strerror(errno)));
    }

    //initiate communication with the frontend
    this->initRFIC();

    //defaults for internal testing
    this->writeRegister(REG_LMS_TRX_LOOPBACK, 0); //disable loopback
    this->writeRegister(REG_TX_IDLE_LEVEL_LO, 0); //DUC input idles 0
    this->writeRegister(REG_TX_IDLE_LEVEL_HI, 0); //DUC input idles 0

    //initialize the DMA channels
    this->initDMAChannels();

    //default to offset removal on
    this->setDCOffsetMode(SOAPY_SDR_RX, 0, true);

    //reset cordics
    this->setFrequency(SOAPY_SDR_RX, 0, "BB", 0.0, SoapySDR::Kwargs());
    this->setFrequency(SOAPY_SDR_TX, 0, "BB", 0.0, SoapySDR::Kwargs());

    //provide a value for the rate until set
    _cachedSampleRates[SOAPY_SDR_RX] = 0.0;
    _cachedSampleRates[SOAPY_SDR_TX] = 0.0;
}

NovenaRF::~NovenaRF(void)
{
    this->exitRFIC();
    munmap(_regs, NOVENA_RF_REGS_PAGE_SIZE);
    munmap(_framer0_mem, NOVENA_RF_FRAMER0_PAGE_SIZE);
    munmap(_deframer0_mem, NOVENA_RF_DEFRAMER0_PAGE_SIZE);
    close(_novena_fd);
    gpio_fd_close(_irq_fd);
}

/*******************************************************************
 * FPGA checks and loading
 ******************************************************************/
void NovenaRF::fpgaCheckAndLoad(const std::string &fpgaImage)
{
    //hash the fpga image
    uint16_t imageHash = uint16_t(novenaRF_hashFpga(fpgaImage));

    //first access turns the bus clock on -- if it was not on...
    this->readRegister(REG_SENTINEL_ADDR);

    //check if the fpga image was loaded -- if not load it
    if (
        this->readRegister(REG_SENTINEL_ADDR) != REG_SENTINEL_VALUE or
        this->readRegister(REG_VERSION_ADDR) != REG_VERSION_VALUE or
        this->readRegister(REG_LOOPBACK_ADDR) != imageHash)
    {
        novenaRF_loadFpga(fpgaImage);
    }

    //check the fpga image and its version number
    const int fpgaSentinel = this->readRegister(REG_SENTINEL_ADDR);
    if (fpgaSentinel != REG_SENTINEL_VALUE)
    {
        SoapySDR::logf(SOAPY_SDR_ERROR, "Expected FPGA sentinel 0x%x, but got 0x%x", REG_SENTINEL_VALUE, fpgaSentinel);
        throw std::runtime_error("Fail FPGA sentinel check");
    }

    const int fpgaVersion = this->readRegister(REG_VERSION_ADDR);
    if (fpgaVersion != REG_VERSION_VALUE)
    {
        SoapySDR::logf(SOAPY_SDR_ERROR, "Expected FPGA version 0x%x, but got 0x%x", REG_VERSION_VALUE, fpgaVersion);
        throw std::runtime_error("FPGA version mismatch");
    }

    //perform reset on FPGA internals
    this->writeRegister(REG_RESET_ADDR, 1);
    this->writeRegister(REG_RESET_ADDR, 0);

    //store the hash in the loopback
    this->writeRegister(REG_LOOPBACK_ADDR, imageHash);
}

/*******************************************************************
 * Self test
 ******************************************************************/
void NovenaRF::selfTestBus(void)
{
    //register loopback test
    SoapySDR::logf(SOAPY_SDR_TRACE, "Register loopback test");
    const int imageHash = this->readRegister(REG_LOOPBACK_ADDR);
    for (size_t i = 0; i < 100; i++)
    {
        short value = std::rand() & 0xffff;
        this->writeRegister(REG_LOOPBACK_ADDR, value);
        short readback = this->readRegister(REG_LOOPBACK_ADDR);
        if (value == readback) continue;
        SoapySDR::logf(SOAPY_SDR_ERROR, "Register loopback fail[%d] wrote 0x%x, but readback 0x%x", i, value, readback);
        throw std::runtime_error("Fail register loopback test");
    }
    this->writeRegister(REG_LOOPBACK_ADDR, imageHash); //save and restore

    //map the test space
    SoapySDR::logf(SOAPY_SDR_TRACE, "Memory loopback test");
    void *test_page = mmap(NULL, NOVENA_RF_TEST0_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, _novena_fd, NOVENA_RF_MAP_OFFSET(NOVENA_RF_TEST0_PAGE_NO));
    if (test_page == MAP_FAILED)
    {
        throw std::runtime_error("Failed to map test page " + std::string(strerror(errno)));
    }

    //memcpy in and out
    char buffOut[NOVENA_RF_TEST0_PAGE_SIZE];
    char buffIn[NOVENA_RF_TEST0_PAGE_SIZE];
    for (size_t i = 0; i < NOVENA_RF_TEST0_PAGE_SIZE; i++)
    {
        buffOut[i] = std::rand() & 0xff;
    }
    std::memcpy(test_page, buffOut, NOVENA_RF_TEST0_PAGE_SIZE);
    std::memcpy(buffIn, test_page, NOVENA_RF_TEST0_PAGE_SIZE);
    for (size_t i = 0; i < NOVENA_RF_TEST0_PAGE_SIZE; i++)
    {
        if (buffOut[i] == buffIn[i]) continue;
        SoapySDR::logf(SOAPY_SDR_ERROR, "Memory loopback fail[%d] wrote 0x%x, but readback 0x%x", i, (int)buffOut[i], (int)buffIn[i]);
        throw std::runtime_error("Fail memory loopback test");
    }

    munmap(test_page, NOVENA_RF_TEST0_PAGE_SIZE);
}

/*******************************************************************
 * Sample Rate API
 ******************************************************************/
void NovenaRF::setSampleRate(const int direction, const size_t, const double rate)
{
    const double baseRate = this->getMasterClockRate()/2.0;
    const double factor = baseRate/rate;
    if (rate > baseRate) throw std::runtime_error("NovenaRF::setSampleRate() -- rate too high");
    int intFactor = 1 << int((std::log(factor)/std::log(2.0)) + 0.5);
    if (intFactor > (1 << NUM_FILTERS)) throw std::runtime_error("NovenaRF::setSampleRate() -- rate too low");
    if (std::abs(factor-intFactor) > 0.01) SoapySDR::logf(SOAPY_SDR_WARNING,
        "NovenaRF::setSampleRate(): not a power of two factor: IF rate = %f MHZ, Requested rate = %f MHz", baseRate/1e6, rate/1e6);

    //stash the actual sample rate
    _cachedSampleRates[direction] = baseRate/intFactor;

    //compute the enabled filters
    int enabledFilters = 0;
    int enabledFiltersR = 0;
    for (int i = NUM_FILTERS-1; i >= 0; i--)
    {
        if (intFactor >= (1 << (i+1)))
        {
            enabledFilters |= (1 << i);
            enabledFiltersR |= (1 << (NUM_FILTERS-(i+1)));
        }
    }

    //write the bypass word
    if (direction == SOAPY_SDR_RX) this->writeRegister(REG_DECIM_FILTER_BYPASS, ~enabledFilters);
    if (direction == SOAPY_SDR_TX) this->writeRegister(REG_INTERP_FILTER_BYPASS, ~enabledFiltersR);
    SoapySDR::logf(SOAPY_SDR_TRACE, "Actual sample rate %f MHz, enables=0x%x, 0x%x", _cachedSampleRates[direction]/1e6, enabledFilters, enabledFiltersR);
}

double NovenaRF::getSampleRate(const int direction, const size_t) const
{
    return _cachedSampleRates.at(direction);
}

std::vector<double> NovenaRF::listSampleRates(const int, const size_t) const
{
    const double baseRate = this->getMasterClockRate()/2.0;
    std::vector<double> rates;
    for (int i = NUM_FILTERS; i >= 0; i--)
    {
        rates.push_back(baseRate/(1 << i));
    }
    return rates;
}

/*******************************************************************
 * Time API
 ******************************************************************/
bool NovenaRF::hasHardwareTime(const std::string &what) const
{
    if (not what.empty()) return SoapySDR::Device::hasHardwareTime(what);
    return true;
}

long long NovenaRF::getHardwareTime(const std::string &what) const
{
    if (not what.empty()) return SoapySDR::Device::getHardwareTime(what);

    //toggle time-in bit to latch the device time into register
    const_cast<NovenaRF *>(this)->writeRegister(REG_TIME_CTRL_ADDR, 1 << 1);
    const_cast<NovenaRF *>(this)->writeRegister(REG_TIME_CTRL_ADDR, 0 << 1);

    uint64_t ticks =
        (uint64_t(this->readRegister(REG_TIME_LO_ADDR)) << 0) |
        (uint64_t(this->readRegister(REG_TIME_ME_ADDR)) << 16) |
        (uint64_t(this->readRegister(REG_TIME_HI_ADDR)) << 32) |
        (uint64_t(this->readRegister(REG_TIME_EX_ADDR)) << 48);

    return this->ticksToTimeNs(ticks);
}

void NovenaRF::setHardwareTime(const long long timeNs, const std::string &what)
{
    if (not what.empty()) return SoapySDR::Device::setHardwareTime(timeNs, what);

    uint64_t ticks = this->timeNsToTicks(timeNs);
    this->writeRegister(REG_TIME_LO_ADDR, (ticks >> 0) & 0xffff);
    this->writeRegister(REG_TIME_ME_ADDR, (ticks >> 16) & 0xffff);
    this->writeRegister(REG_TIME_HI_ADDR, (ticks >> 32) & 0xffff);
    this->writeRegister(REG_TIME_EX_ADDR, (ticks >> 48) & 0xffff);

    //toggle time-out bit to latch the register into device time
    const_cast<NovenaRF *>(this)->writeRegister(REG_TIME_CTRL_ADDR, 1 << 0);
    const_cast<NovenaRF *>(this)->writeRegister(REG_TIME_CTRL_ADDR, 0 << 0);
}

/***********************************************************************
 * Find available devices
 **********************************************************************/
std::vector<SoapySDR::Kwargs> findNovenaRF(const SoapySDR::Kwargs &args)
{
    //always discovery "args" -- the sdr is the board itself
    std::vector<SoapySDR::Kwargs> discovered;
    discovered.push_back(args);
    return discovered;
}

/***********************************************************************
 * Make device instance
 **********************************************************************/
SoapySDR::Device *makeNovenaRF(const SoapySDR::Kwargs &args)
{
    std::string fpgaImage = FPGA_IMAGE_PATH;
    if (args.count("fpga") != 0) fpgaImage = args.at("fpga");
    return new NovenaRF(fpgaImage);
}

/***********************************************************************
 * Registration
 **********************************************************************/
static SoapySDR::Registry registerNovenaRF("novena", &findNovenaRF, &makeNovenaRF, SOAPY_SDR_ABI_VERSION);
