////////////////////////////////////////////////////////////////////////
// SoapySDR module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#pragma once
#include "NovenaConstants.hpp"
#include "NovenaDMA.hpp"

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Logger.hpp>

#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <memory>

class NovenaRF : public SoapySDR::Device
{
public:
    NovenaRF(const std::string &fpgaImage);

    ~NovenaRF(void);

    /*******************************************************************
     * FPGA checks and loading
     ******************************************************************/
    void fpgaCheckAndLoad(const std::string &fpgaImage);

    /*******************************************************************
     * Self test
     ******************************************************************/
    void selfTestBus(void);

    /*******************************************************************
     * Initialize DMA channels
     ******************************************************************/
    void initDMAChannels(void);

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
        const SoapySDR::Kwargs &);

    void closeStream(SoapySDR::Stream *);

    //! used by RX to simplify sending a control message (used by various functions)
    int sendControlMessage(const int tag, const bool timeFlag, const bool burstFlag, const int burstSize, const long long time);

    //! used by RX readStream to deal with tiny input buffers from the user
    void stashConversion(const int inHandle, const void *inp, const size_t numInSamps);
    int convertRemainder(void *outp, const size_t numOutSamps);

    int activateStream(
        SoapySDR::Stream *stream,
        const int flags,
        const long long timeNs,
        const size_t numElems);

    int deactivateStream(
        SoapySDR::Stream *stream,
        const int flags,
        const long long timeNs);

    int readStream(
        SoapySDR::Stream *,
        void * const *buffs,
        const size_t numElems,
        int &flags,
        long long &timeNs,
        const long timeoutUs);

    int writeStream(
        SoapySDR::Stream *,
        const void * const *buffs,
        const size_t numElems,
        int &flags,
        const long long timeNs,
        const long timeoutUs
    );

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
                enabledFiltersR |= (1 << (NUM_FILTERS-(i+1)));
            }
        }

        //write the bypass word
        if (direction == SOAPY_SDR_RX) this->writeRegister(REG_DECIM_FILTER_BYPASS, ~enabledFilters);
        if (direction == SOAPY_SDR_TX) this->writeRegister(REG_INTERP_FILTER_BYPASS, ~enabledFiltersR);
        SoapySDR::logf(SOAPY_SDR_TRACE, "Actual sample rate %f MHz, enables=0x%x, 0x%x\n", _cachedSampleRates[direction]/1e6, enabledFilters, enabledFiltersR);
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

    //rx streaming
    int _remainderHandle;
    size_t _remainderSamps;
    const uint32_t *_remainderBuff;

    //stream configuration
    enum StreamFormat
    {
        SF_CS16,
        SF_CF32,
    };
    StreamFormat _rxFormat;
    StreamFormat _txFormat;
};

/***********************************************************************
 * Utility functions
 **********************************************************************/
void novenaRF_loadFpga(const std::string &fpgaImage);
unsigned novenaRF_hashFpga(const std::string &fpgaImage);
