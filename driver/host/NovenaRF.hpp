////////////////////////////////////////////////////////////////////////
// SoapySDR module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#pragma once
#include "NovenaRegs.hpp"
#include "NovenaDMA.hpp"

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Logger.hpp>

#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <memory>

namespace lms6
{
    class LMS6002_MainControl;
}

class NovenaRF : public SoapySDR::Device
{
public:
    NovenaRF(const std::string &fpgaImage);

    ~NovenaRF(void);

    /*******************************************************************
     * RFIC setup and tear-down
     ******************************************************************/
    void initRFIC(void);
    void exitRFIC(void);

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

    size_t getStreamMTU(SoapySDR::Stream *) const;

    //! used by RX to simplify sending a control message (used by various functions)
    int sendControlMessage(const int tag, const bool timeFlag, const bool burstFlag, const int burstSize, const long long time);

    //! used by RX readStream to deal with tiny input buffers from the user
    void stashConversion(const int inHandle, const void *inp, const size_t numInSamps);
    int convertRemainder(void *outp, const size_t numOutSamps, int &flags);

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

    int readStreamStatus(
        SoapySDR::Stream *stream,
        size_t &chanMask,
        int &flags,
        long long &timeNs,
        const long timeoutUs);

    size_t getNumDirectAccessBuffers(SoapySDR::Stream *stream);
    int getDirectAccessBufferAddrs(SoapySDR::Stream *stream, const size_t handle, void **buffs);

    int acquireReadBuffer(
        SoapySDR::Stream *stream,
        size_t &handle,
        const void **buffs,
        int &flags,
        long long &timeNs,
        const long timeoutUs);

    void releaseReadBuffer(
        SoapySDR::Stream *stream,
        const size_t handle);

    int acquireWriteBuffer(
        SoapySDR::Stream *stream,
        size_t &handle,
        void **buffs,
        const long timeoutUs);

    void releaseWriteBuffer(
        SoapySDR::Stream *stream,
        const size_t handle,
        const size_t numElems,
        int &flags,
        const long long timeNs);

    /*******************************************************************
     * Antenna API
     ******************************************************************/
    std::vector<std::string> listAntennas(const int direction, const size_t channel) const;

    void setAntenna(const int, const size_t, const std::string &);

    std::string getAntenna(const int direction, const size_t) const;

    /*******************************************************************
     * Frontend corrections API
     ******************************************************************/
    void setDCOffsetMode(const int direction, const size_t channel, const bool automatic)
    {
        if (direction == SOAPY_SDR_RX)
        {
            _dcOffsetCache = automatic;
            return this->writeRegister(REG_ENABLE_DC_REMOVAL, automatic?1:0);
        }
        return SoapySDR::Device::setDCOffsetMode(direction, channel, automatic);
    }

    bool getDCOffsetMode(const int direction, const size_t channel) const
    {
        if (direction == SOAPY_SDR_RX) return _dcOffsetCache;
        return SoapySDR::Device::getDCOffsetMode(direction, channel);
    }

    bool _dcOffsetCache;

    /*******************************************************************
     * Gain API
     ******************************************************************/
    std::vector<std::string> listGains(const int direction, const size_t channel) const;

    void setGain(const int direction, const size_t channel, const std::string &name, const double value);

    double getGain(const int direction, const size_t channel, const std::string &name) const;

    SoapySDR::Range getGainRange(const int direction, const size_t channel, const std::string &name) const;

    /*******************************************************************
     * Frequency API
     ******************************************************************/
    void setFrequency(const int direction, const size_t channel, const std::string &name, const double frequency, const SoapySDR::Kwargs &args);

    void setRfFrequency(const int direction, const size_t channel, const double frequency, const SoapySDR::Kwargs &args);

    double getFrequency(const int direction, const size_t channel, const std::string &name) const;

    SoapySDR::RangeList getFrequencyRange(const int direction, const size_t channel, const std::string &name) const;

    std::vector<std::string> listFrequencies(const int direction, const size_t channel) const;

    std::map<int, std::map<size_t, double>> _cachedCordics;

    /*******************************************************************
     * Sample Rate API
     ******************************************************************/
    void setSampleRate(const int direction, const size_t, const double rate);

    double getSampleRate(const int direction, const size_t) const;

    std::vector<double> listSampleRates(const int, const size_t) const;

    std::map<int, double> _cachedSampleRates;

    void setBandwidth(const int direction, const size_t channel, const double bw);

    double getBandwidth(const int direction, const size_t channel) const;

    std::vector<double> listBandwidths(const int direction, const size_t channel) const;

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
    template <typename T>
    static T scaleDiv(const T in, const T scalar, const T divisor)
    {
        const auto divRes = std::div(in, divisor);
        const T outQuot = divRes.quot * scalar;
        const T outRem = (divRes.rem * scalar) + (divisor/2);
        return outQuot + (outRem/divisor);
    }

    long long ticksToTimeNs(const long long ticks) const
    {
        return scaleDiv<long long>(ticks, 1e9, LMS_CLOCK_RATE);
    }

    long long timeNsToTicks(const long long timeNs) const
    {
        return scaleDiv<long long>(timeNs, LMS_CLOCK_RATE, 1e9);
    }

    bool hasHardwareTime(const std::string &what) const;

    long long getHardwareTime(const std::string &what) const;

    void setHardwareTime(const long long timeNs, const std::string &what);

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
    int _irq_fd; //sysfs gpio for DMA IRQs
    void *_regs; //mapped register space
    void *_framer0_mem; //mapped RX DMA and RX control
    void *_deframer0_mem; //mapped TX DMA and TX status

    //lms suite instantiation
    lms6::LMS6002_MainControl *_lms6ctrl;
    size_t _calLPFCoreOnce;

    //dma channel management
    std::unique_ptr<NovenaDmaChannel> _framer0_ctrl_chan;
    std::unique_ptr<NovenaDmaChannel> _framer0_rxd_chan;
    std::unique_ptr<NovenaDmaChannel> _deframer0_stat_chan;
    std::unique_ptr<NovenaDmaChannel> _deframer0_txd_chan;

    //rx streaming
    int _remainderHandle;
    size_t _remainderSamps;
    const uint32_t *_remainderBuff;
    long long _nextRxTime;

    //tx streaming
    bool _userHandlesTxStatus;
    bool _inTimedTxBurst;
    long long _nextTxTime;

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
