////////////////////////////////////////////////////////////////////////
// SoapySDR module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#include "NovenaRF.hpp"
#include "novena_rf.h" //shared kernel module header

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Registry.hpp>
#include <SoapySDR/Logger.hpp>

#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h> //mmap
#include <unistd.h> //close
#include <stdint.h>

/***********************************************************************
 * Device interface
 **********************************************************************/
class NovenaRF : public SoapySDR::Device
{
public:
    NovenaRF(const std::string &fpgaImage):
        _novena_fd(-1),
        _regs(NULL),
        _framer0_mem(NULL),
        _deframer0_mem(NULL)
    {
        //open the file descriptor for the novena rf module
        _novena_fd = open(NOVENA_RF_DEVFS, O_RDWR | O_SYNC);
        if (_novena_fd <= 0)
        {
            throw std::runtime_error("Failed to open "NOVENA_RF_DEVFS": " + std::string(strerror(errno)));
        }

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

        //do some tests with the dma
        SoapySDR::logf(SOAPY_SDR_TRACE, "FIFO regs: 0x%x", this->readRegister(REG_DMA_FIFO_RDY_CTRL_ADDR));

        //fill buffer and push the mm2s
        uint32_t *p = (uint32_t *)_framer0_mem;
        for (size_t i = 0; i < 10; i++) p[i] = 0xA0000000 | i;

        //push a control cmd for s2mm
        this->writeRegister(REG_S2MM_FRAMER0_CTRL_ADDR, 32); //start addr

        //push a control cmd for mm2s
        this->writeRegister(REG_MM2S_FRAMER0_CTRL_ADDR, 0); //start addr
        this->writeRegister(REG_MM2S_FRAMER0_CTRL_ADDR, 16); //end addr

        //should get stat done for both
        sleep(1);
        SoapySDR::logf(SOAPY_SDR_TRACE, "FIFO regs: 0x%x", this->readRegister(REG_DMA_FIFO_RDY_CTRL_ADDR));

        //lets read stat fifos
        SoapySDR::logf(SOAPY_SDR_TRACE, "S2MM stat: 0x%x", this->readRegister(REG_S2MM_FRAMER0_STAT_ADDR));
        SoapySDR::logf(SOAPY_SDR_TRACE, "MM2S stat: 0x%x", this->readRegister(REG_MM2S_FRAMER0_STAT_ADDR));

        //pop
        this->writeRegister(REG_S2MM_FRAMER0_STAT_ADDR, 0/*dontcare*/);
        this->writeRegister(REG_MM2S_FRAMER0_STAT_ADDR, 0/*dontcare*/);
        SoapySDR::logf(SOAPY_SDR_TRACE, "FIFO regs: 0x%x", this->readRegister(REG_DMA_FIFO_RDY_CTRL_ADDR));

        //readback print
        uint32_t *o = (uint32_t *)_framer0_mem + (32/sizeof(uint32_t));
        for (size_t i = 0; i < 10; i++)
        {
            SoapySDR::logf(SOAPY_SDR_TRACE, "Buff[%d]: 0x%x", i, o[i]);
        }
    }

    ~NovenaRF(void)
    {
        munmap(_regs, NOVENA_RF_REGS_PAGE_SIZE);
        munmap(_framer0_mem, NOVENA_RF_FRAMER0_PAGE_SIZE);
        munmap(_deframer0_mem, NOVENA_RF_DEFRAMER0_PAGE_SIZE);
        close(_novena_fd);
    }

    void fpgaCheckAndLoad(const std::string &fpgaImage)
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

    void selfTestBus(void)
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
     * Identification API
     ******************************************************************/
    std::string getDriverKey(void) const
    {
        return "NOVENA-RF";
    }

    std::string getHardwareKey(void) const
    {
        return "NOVENA";
    }

    /*******************************************************************
     * Channels API
     ******************************************************************/

    /*******************************************************************
     * Stream API
     ******************************************************************/

    /*******************************************************************
     * Antenna API
     ******************************************************************/

    /*******************************************************************
     * Frontend corrections API
     ******************************************************************/

    /*******************************************************************
     * Gain API
     ******************************************************************/

    /*******************************************************************
     * Frequency API
     ******************************************************************/

    /*******************************************************************
     * Sample Rate API
     ******************************************************************/

    /*******************************************************************
     * Clocking API
     ******************************************************************/

    /*******************************************************************
     * Time API
     ******************************************************************/
    long long ticksToTimeNs(const uint64_t ticks) const
    {
        return (long long)(ticks/(LMS_CLOCK_RATE/1e9));
    }

    uint64_t timeNsToTicks(const long long timeNs) const
    {
        return uint64_t(timeNs*(LMS_CLOCK_RATE/1e9));
    }

    bool hasHardwareTime(const std::string &what) const
    {
        if (not what.empty()) return SoapySDR::Device::hasHardwareTime(what);
        return true;
    }

    long long getHardwareTime(const std::string &what) const
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

    void setHardwareTime(const long long timeNs, const std::string &what)
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

    /*******************************************************************
     * Sensor API
     ******************************************************************/

    /*******************************************************************
     * Register API
     ******************************************************************/
    void writeRegister(const unsigned addr, const unsigned value)
    {
        volatile uint16_t *p = (volatile uint16_t *)(((char *)_regs) + addr);
        *p = value;
    }

    unsigned readRegister(const unsigned addr) const
    {
        volatile uint16_t *p = (volatile uint16_t *)(((char *)_regs) + addr);
        return *p;
    }

    /*******************************************************************
     * Settings API
     ******************************************************************/

    /*******************************************************************
     * GPIO API
     ******************************************************************/

    /*******************************************************************
     * I2C API
     ******************************************************************/

    /*******************************************************************
     * SPI API
     ******************************************************************/

    /*******************************************************************
     * UART API
     ******************************************************************/

private:
    int _novena_fd; //novena_rf kernel module
    void *_regs;
    void *_framer0_mem;
    void *_deframer0_mem;
};

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
