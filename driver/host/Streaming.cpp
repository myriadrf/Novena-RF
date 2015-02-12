////////////////////////////////////////////////////////////////////////
// SoapySDR module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#include "NovenaRF.hpp"
#include "twbw_helper.h"

/*******************************************************************
 * Initialize DMA channels
 ******************************************************************/
void NovenaRF::initDMAChannels(void)
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
    /*
    this->writeRegister(REG_INTERP_FILTER_BYPASS, 0x0); //no bypass
    this->writeRegister(REG_DECIM_FILTER_BYPASS, 0x0); //no bypass
    this->writeRegister(REG_LMS_TRX_LOOPBACK, 1); //loopback for debug
    this->setSampleRate(SOAPY_SDR_TX, 0, 61.44e6/4./2./2./2./2.);
    sleep(1);

    void *handle = this->setupStream(SOAPY_SDR_TX, "CS16", std::vector<size_t>(1, 0), SoapySDR::Kwargs());
    void *buffs[1];
    uint32_t buff[1024];
    buffs[0] = buff;
    for (size_t j = 0; j < 1024; j++) buff[j] = 0xA100B200;
    int flags = 0;//SOAPY_SDR_END_BURST;
    long long timeNs = 0;
    int x = 0;
    while (1)
    {
        for (size_t j = 0; j < 1000; j++)
        {
            buff[j] = (x << 16) | (x & 0xffff);
            x++;
        }
        int ret = this->writeStream((SoapySDR::Stream *)handle, buffs, 1000, flags, timeNs, 1e6);
        //SoapySDR::logf(SOAPY_SDR_TRACE, "ret(%d)=%d", i, ret);
    }
    //*/
}

/*******************************************************************
 * Stream API
 ******************************************************************/
SoapySDR::Stream *NovenaRF::setupStream(
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

void NovenaRF::closeStream(SoapySDR::Stream *)
{
    return;
}

int NovenaRF::sendControlMessage(const int tag, const bool timeFlag, const bool burstFlag, const int burstSize, const long long time)
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

int NovenaRF::activateStream(
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
        //TODO drain stat msgs
        return 0;
    }

    return SOAPY_SDR_STREAM_ERROR;
}

int NovenaRF::deactivateStream(
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
        //send mini end of burst transmission
        void *buffs[1];
        uint32_t buff[1];
        buffs[0] = buff;
        int f = SOAPY_SDR_END_BURST;
        this->writeStream(stream, buffs, 1, f, 0, 100);
        return 0;
    }

    return SOAPY_SDR_STREAM_ERROR;
}

/*******************************************************************
 * read stream API
 ******************************************************************/
int NovenaRF::readStream(
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
    _framer0_rxd_chan->release(handle, len);

    //SoapySDR::logf(SOAPY_SDR_TRACE, "ret=%d", ret);
    return ret;
}

/*******************************************************************
 * write stream API
 ******************************************************************/
int NovenaRF::writeStream(
    SoapySDR::Stream *,
    const void * const *buffs,
    const size_t numElems,
    int &flags,
    const long long timeNs,
    const long timeoutUs
)
{
    size_t len = 0;
    static int id = 0;

    //remove any stat reporting
    while (_deframer0_stat_chan->waitReady(0))
    {
        int handle = _deframer0_stat_chan->acquire(len);
        bool underflow;
        int idTag = 0;
        bool hasTime;
        long long timeTicks;
        bool timeError;
        bool burstEnd;
        twbw_deframer_stat_unpacker(
            _deframer0_stat_chan->buffer(handle), len,
            underflow, idTag, hasTime, timeTicks, timeError, burstEnd);
        //SoapySDR::logf(SOAPY_SDR_TRACE, "handle=%d, TxStat=%d", handle, idTag);
        if (underflow) SoapySDR::log(SOAPY_SDR_TRACE, "U");
        if (timeError) SoapySDR::log(SOAPY_SDR_TRACE, "T");
        if (burstEnd) SoapySDR::log(SOAPY_SDR_TRACE, "B");
        _deframer0_stat_chan->release(handle, len);
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
    _deframer0_txd_chan->release(handle, len);

    return numSamples;
}
