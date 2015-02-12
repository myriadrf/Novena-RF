////////////////////////////////////////////////////////////////////////
// SoapySDR module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#include "NovenaRF.hpp"
#include "NovenaDMA.hpp"
#include "novena_rf.h" //shared kernel module header
#include "twbw_helper.h"

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Registry.hpp>
#include <SoapySDR/Logger.hpp>

#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <memory>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h> //mmap
#include <unistd.h> //close

/***********************************************************************
 * Device interface
 **********************************************************************/
class NovenaRF : public SoapySDR::Device
{
public:
    NovenaRF(const std::string &fpgaImage):
        _novena_fd(-1),
        _regs(nullptr),
        _framer0_mem(nullptr),
        _deframer0_mem(nullptr)
    {
        setvbuf(stdout, NULL, _IOLBF, 0);

        //open the file descriptor for the novena rf module
        _novena_fd = open(NOVENA_RF_DEVFS, O_RDWR | O_SYNC);
        if (_novena_fd <= 0)
        {
            throw std::runtime_error("Failed to open " NOVENA_RF_DEVFS ": " + std::string(strerror(errno)));
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

        this->writeRegister(REG_LMS_TRX_LOOPBACK, 0); //disable loopback
        this->initDMAChannels();
    }

    ~NovenaRF(void)
    {
        munmap(_regs, NOVENA_RF_REGS_PAGE_SIZE);
        munmap(_framer0_mem, NOVENA_RF_FRAMER0_PAGE_SIZE);
        munmap(_deframer0_mem, NOVENA_RF_DEFRAMER0_PAGE_SIZE);
        close(_novena_fd);
    }

    /*******************************************************************
     * FPGA checks and loading
     ******************************************************************/
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

    /*******************************************************************
     * Self test
     ******************************************************************/
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
     * Initialize DMA channels
     ******************************************************************/
    void initDMAChannels(void)
    {
        _framer0_rxd_chan.reset(new NovenaDmaChannel(
            NRF_DMA_DIR_S2MM, _regs, REG_S2MM_FRAMER0_STAT_ADDR, REG_S2MM_FRAMER0_CTRL_ADDR,
            _framer0_mem, FRAMER0_S2MM_NUM_ENTRIES*sizeof(uint32_t), NOVENA_RF_FRAMER0_NUM_FRAMES));
        _framer0_ctrl_chan.reset(new NovenaDmaChannel(
            NRF_DMA_DIR_MM2S, _regs, REG_MM2S_FRAMER0_STAT_ADDR, REG_MM2S_FRAMER0_CTRL_ADDR,
            _framer0_mem, FRAMER0_MM2S_NUM_ENTRIES*sizeof(uint32_t), NOVENA_RF_FRAMER0_NUM_FRAMES));
        _deframer0_stat_chan.reset(new NovenaDmaChannel(
            NRF_DMA_DIR_S2MM, _regs, REG_S2MM_DEFRAMER0_STAT_ADDR, REG_S2MM_DEFRAMER0_CTRL_ADDR,
            _deframer0_mem, DEFRAMER0_S2MM_NUM_ENTRIES*sizeof(uint32_t), NOVENA_RF_DEFRAMER0_NUM_FRAMES));
        _deframer0_txd_chan.reset(new NovenaDmaChannel(
            NRF_DMA_DIR_MM2S, _regs, REG_MM2S_DEFRAMER0_STAT_ADDR, REG_MM2S_DEFRAMER0_CTRL_ADDR,
            _deframer0_mem, DEFRAMER0_MM2S_NUM_ENTRIES*sizeof(uint32_t), NOVENA_RF_DEFRAMER0_NUM_FRAMES));


        this->writeRegister(REG_LMS_TRX_LOOPBACK, 1); //loopback for debug

        /*
        this->writeRegister(REG_INTERP_FILTER_BYPASS, ~0x1); //all bypass - full rate
        this->writeRegister(REG_DECIM_FILTER_BYPASS, ~0x1); //all bypass - full rate
        this->writeRegister(REG_LMS_TRX_LOOPBACK, 1); //loopback for debug
        sleep(1);

        void *handle = this->setupStream(SOAPY_SDR_RX, "CS16", std::vector<size_t>(1, 0), SoapySDR::Kwargs());
        this->activateStream((SoapySDR::Stream *)handle, 0, 0, 0);
        void *buffs[1];
        uint32_t buff[1024];
        buffs[0] = buff;
        int flags = 0;
        long long timeNs = 0;
        for (int i = 0; i < 100; i++)
        {
            int ret = this->readStream((SoapySDR::Stream *)handle, buffs, 1024, flags, timeNs, 1e6);
            SoapySDR::logf(SOAPY_SDR_TRACE, "ret(%d)=%d", i, ret);
        }
        //*/
        //*
        this->writeRegister(REG_INTERP_FILTER_BYPASS, ~0x1); //all bypass - full rate
        this->writeRegister(REG_DECIM_FILTER_BYPASS, ~0x1); //all bypass - full rate
        this->writeRegister(REG_LMS_TRX_LOOPBACK, 1); //loopback for debug
        sleep(1);

        void *handle = this->setupStream(SOAPY_SDR_TX, "CS16", std::vector<size_t>(1, 0), SoapySDR::Kwargs());
        void *buffs[1];
        uint32_t buff[1024];
        buffs[0] = buff;
        for (size_t j = 0; j < 1024; j++) buff[j] = 0xA100B200;
        int flags = SOAPY_SDR_END_BURST;
        long long timeNs = 0;
        for (int i = 0; i < 10; i++)
        {
            int ret = this->writeStream((SoapySDR::Stream *)handle, buffs, 1000, flags, timeNs, 1e6);
            SoapySDR::logf(SOAPY_SDR_TRACE, "ret(%d)=%d", i, ret);
        }
        //*/
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
    size_t getNumChannels(const int) const
    {
        return 1;
    }

    bool getFullDuplex(const int, const size_t) const
    {
        return true;
    }

    /*******************************************************************
     * Stream API
     ******************************************************************/
    SoapySDR::Stream *setupStream(
        const int direction,
        const std::string &format,
        const std::vector<size_t> &channels,
        const SoapySDR::Kwargs &)
    {
        if (format != "CS16") throw std::runtime_error("NovenaRF::setupStream: "+format);
        if (channels.size() != 1 or channels[0] != 0) throw std::runtime_error("NovenaRF::setupStream: only one channel supported");

        //use the directions as handles since there is only one dma channel per direction
        return reinterpret_cast<SoapySDR::Stream *>(direction);
    }

    void closeStream(SoapySDR::Stream *)
    {
        return;
    }

    int sendControlMessage(const int tag, const bool timeFlag, const bool burstFlag, const int burstSize, const long long time)
    {
        size_t len = 0;
        int handle = _framer0_ctrl_chan->acquire(len);
        if (handle < 0) return SOAPY_SDR_STREAM_ERROR;

        //frame size without header and some padding
        const int frameSize = _framer0_rxd_chan->frameSize()/sizeof(uint32_t) - 6;

        twbw_framer_ctrl_packer(
            _framer0_ctrl_chan->buffer(handle), len,
            tag, timeFlag, time,
            burstFlag, frameSize, burstSize
        );

        _framer0_ctrl_chan->release(handle, len);
        return 0;
    }

    int activateStream(
        SoapySDR::Stream *stream,
        const int flags,
        const long long timeNs,
        const size_t numElems)
    {
        if (int(stream) == SOAPY_SDR_RX)
        {
            return this->sendControlMessage(0xff,
                (flags & SOAPY_SDR_HAS_TIME) != 0, //timeFlag
                (flags & SOAPY_SDR_END_BURST) != 0, //burstFlag
                numElems, this->timeNsToTicks(timeNs));
        }

        if (int(stream) == SOAPY_SDR_TX)
        {
            return 0;
        }

        return SOAPY_SDR_STREAM_ERROR;
    }

    int deactivateStream(
        SoapySDR::Stream *stream,
        const int flags,
        const long long timeNs)
    {
        if (int(stream) == SOAPY_SDR_RX)
        {
            return sendControlMessage(0x00,
                (flags & SOAPY_SDR_HAS_TIME) != 0, //timeFlag
                true, //burstFlag
                1, this->timeNsToTicks(timeNs));
        }

        if (int(stream) == SOAPY_SDR_TX)
        {
            return 0;
        }

        return SOAPY_SDR_STREAM_ERROR;
    }

    /*******************************************************************
     * read stream API
     ******************************************************************/
    int readStream(
        SoapySDR::Stream *,
        void * const *buffs,
        const size_t numElems,
        int &flags,
        long long &timeNs,
        const long timeoutUs)
    {
        size_t len = 0;
        int ret = 0;
        flags = 0;

        //wait with timeout then acquire
        if (not _framer0_rxd_chan->waitReady(timeoutUs)) return SOAPY_SDR_TIMEOUT;
        int handle = _framer0_rxd_chan->acquire(len);
        if (handle == -2) throw std::runtime_error("NovenaRF::readStream() all claimed");

        //unpack the header
        const void *payload;
        size_t numSamples;
        bool overflow;
        int idTag;
        bool hasTime;
        long long timeTicks;
        bool timeError;
        bool isBurst;
        bool burstEnd;
        twbw_framer_data_unpacker(
            _framer0_rxd_chan->buffer(handle), len, sizeof(uint32_t),
            payload, numSamples, overflow, idTag,
            hasTime, timeTicks,
            timeError, isBurst, burstEnd);

        //gather time even if its not valid
        timeNs = this->ticksToTimeNs(timeTicks);

        //error indicators
        if (overflow) ret = SOAPY_SDR_OVERFLOW;
        if (hasTime) flags |= SOAPY_SDR_HAS_TIME;
        if (burstEnd) flags |= SOAPY_SDR_END_BURST;

        //old packet from the deactivate command, just ignore it with timeout
        if (idTag == 0x00)
        {
            ret = SOAPY_SDR_TIMEOUT;
        }

        //not an activate or deactivate tag, this is bad!
        else if (idTag != 0xff)
        {
            SoapySDR::logf(SOAPY_SDR_ERROR,
                "readStream tag error tag=0x%x, len=%d", idTag, len);
            ret = SOAPY_SDR_STREAM_ERROR;
        }

        //a bad time was specified in the command packet
        else if (timeError)
        {
            SoapySDR::logf(SOAPY_SDR_ERROR,
                "readStream time error time now %f, time pkt %f, len=%d",
                this->getHardwareTime("")/1e9, timeNs/1e9, len);
            ret = SOAPY_SDR_STREAM_ERROR;
        }

        //restart streaming when overflow in continuous mode
        if (overflow and not isBurst)
        {
            SoapySDR::log(SOAPY_SDR_TRACE, "O");
            sendControlMessage(0xff, //restart streaming
                false, //timeFlag
                false, //burstFlag
                0, 0);
        }

        if (ret == 0) //no errors yet, copy buffer -- sorry for the copy, zero copy in the future...
        {
            //TODO if numElems < numSamples, keep remainder...
            if (numElems < numSamples) SoapySDR::log(SOAPY_SDR_TRACE, "Truncated!");
            ret = std::min(numSamples, numElems);
            const uint32_t *in = (const uint32_t *)payload;
            std::complex<int16_t> *out = (std::complex<int16_t> *)buffs[0];
            for (int i = 0; i < ret; i++)
            {
                int16_t i16 = uint16_t(in[i] >> 16);
                int16_t q16 = uint16_t(in[i] & 0xffff);
                out[i] = std::complex<int16_t>(i16, q16);
            }
        }

        //always release the buffer back the SG engine
        _framer0_rxd_chan->release(handle, 0);

        //SoapySDR::logf(SOAPY_SDR_TRACE, "ret=%d", ret);
        return ret;
    }

    /*******************************************************************
     * write stream API
     ******************************************************************/
    int writeStream(
        SoapySDR::Stream *,
        const void * const *buffs,
        const size_t numElems,
        int &flags,
        const long long timeNs,
        const long timeoutUs
    )
    {
        size_t len = 0;

        //remove any stat reporting
        static int id = 0;
        while (_deframer0_stat_chan->waitReady(0))
        {
            int handle = _deframer0_stat_chan->acquire(len);
            bool underflow;
            int idTag;
            bool hasTime;
            long long timeTicks;
            bool timeError;
            bool burstEnd;
            twbw_deframer_stat_unpacker(
                _deframer0_stat_chan->buffer(handle), len,
                underflow, idTag, hasTime, timeTicks, timeError, burstEnd);
            SoapySDR::logf(SOAPY_SDR_TRACE, "handle=%d, TxStat=%d", handle, idTag);
            if (underflow) SoapySDR::log(SOAPY_SDR_TRACE, "U");
            if (timeError) SoapySDR::log(SOAPY_SDR_TRACE, "T");
            _deframer0_stat_chan->release(handle, 0);
            sleep(1);
        }

        //wait with timeout then acquire
        if (not _deframer0_txd_chan->waitReady(timeoutUs)) return SOAPY_SDR_TIMEOUT;
        int handle = _deframer0_txd_chan->acquire(len);
        if (handle == -1) throw std::runtime_error("NovenaRF::writeStream() all claimed");

        //pack the header
        void *payload;
        size_t numSamples = std::min<size_t>(_deframer0_txd_chan->frameSize()/sizeof(uint32_t)-6, numElems);
        twbw_deframer_data_packer(
            _deframer0_txd_chan->buffer(handle), len, sizeof(uint32_t),
            payload, numSamples, id++,
            (flags & SOAPY_SDR_HAS_TIME) != 0,
            this->timeNsToTicks(timeNs),
            (flags & SOAPY_SDR_END_BURST) != 0
        );

        //convert the samples
        uint32_t *out = (uint32_t *)payload;
        std::complex<const int16_t> *in = (std::complex<const int16_t> *)buffs[0];
        for (size_t i = 0; i < numSamples; i++)
        {
            uint16_t i16 = in[i].real();
            uint16_t q16 = in[i].imag();
            out[i] = (uint32_t(i16) << 16) | q16;
        }

        //always release the buffer back the SG engine
        _deframer0_txd_chan->release(handle, 0);

        return numSamples;
    }

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
    void setSampleRate(const int direction, const size_t, const double rate)
    {
        const double baseRate = this->getMasterClockRate()/2.0;
        const double factor = baseRate/rate;
        if (rate > baseRate) throw std::runtime_error("NovenaRF::setSampleRate() -- rate too high");
        int intFactor = int(factor + 0.5);
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
                enabledFiltersR |= ((NUM_FILTERS-(i+1)) << 1);
            }
        }

        //write the bypass word
        if (direction == SOAPY_SDR_RX) this->writeRegister(REG_DECIM_FILTER_BYPASS, ~enabledFilters);
        if (direction == SOAPY_SDR_TX) this->writeRegister(REG_INTERP_FILTER_BYPASS, ~enabledFiltersR);
        SoapySDR::logf(SOAPY_SDR_TRACE, "Actual sample rate %f MHz, enables=0x%x\n", _cachedSampleRates[direction]/1e6, enabledFilters);
    }

    double getSampleRate(const int direction, const size_t) const
    {
        return _cachedSampleRates.at(direction);
    }

    std::vector<double> listSampleRates(const int, const size_t) const
    {
        const double baseRate = this->getMasterClockRate()/2.0;
        std::vector<double> rates;
        for (int i = NUM_FILTERS; i >= 0; i--)
        {
            rates.push_back(baseRate/(1 << i));
        }
        return rates;
    }

    std::map<int, double> _cachedSampleRates;

    /*******************************************************************
     * Clocking API
     ******************************************************************/
    double getMasterClockRate(void) const
    {
        return LMS_CLOCK_RATE;
    }

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
    void *_regs; //mapped register space
    void *_framer0_mem; //mapped RX DMA and RX control
    void *_deframer0_mem; //mapped TX DMA and TX status
    std::unique_ptr<NovenaDmaChannel> _framer0_ctrl_chan;
    std::unique_ptr<NovenaDmaChannel> _framer0_rxd_chan;
    std::unique_ptr<NovenaDmaChannel> _deframer0_stat_chan;
    std::unique_ptr<NovenaDmaChannel> _deframer0_txd_chan;
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
