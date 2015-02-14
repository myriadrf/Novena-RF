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
    std::vector<std::string> listAntennas(const int direction, const size_t channel) const
    {
        return std::vector<std::string>(1, this->getAntenna(direction, channel));
    }

    std::string getAntenna(const int direction, const size_t) const
    {
        return (direction == SOAPY_SDR_TX)?"TX":"RX";
    }

    /*******************************************************************
     * Frontend corrections API
     ******************************************************************/

    /*******************************************************************
     * Gain API
     ******************************************************************/
    std::vector<std::string> listGains(const int direction, const size_t channel) const;

    void setGain(const int direction, const size_t channel, const double value);

    void setGain(const int direction, const size_t channel, const std::string &name, const double value);

    double getGain(const int direction, const size_t channel, const std::string &name) const;

    double getGain(const int dir, const size_t channel) const;

    SoapySDR::Range getGainRange(const int direction, const size_t channel) const;

    SoapySDR::Range getGainRange(const int direction, const size_t channel, const std::string &name) const;

    /*******************************************************************
     * Frequency API
     ******************************************************************/
    void setFrequency(const int direction, const size_t channel, const double frequency, const SoapySDR::Kwargs &args);

    double getFrequency(const int direction, const size_t channel) const;

    SoapySDR::RangeList getFrequencyRange(const int direction, const size_t channel) const;

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
    long long ticksToTimeNs(const uint64_t ticks) const
    {
        return (long long)(ticks/(LMS_CLOCK_RATE/1e9));
    }

    uint64_t timeNsToTicks(const long long timeNs) const
    {
        return uint64_t(timeNs*(LMS_CLOCK_RATE/1e9));
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
    void *_regs; //mapped register space
    void *_framer0_mem; //mapped RX DMA and RX control
    void *_deframer0_mem; //mapped TX DMA and TX status

    //lms suite instantiation
    lms6::LMS6002_MainControl *_lms6ctrl;

    //dma channel management
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
