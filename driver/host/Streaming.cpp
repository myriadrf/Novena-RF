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
}

/*******************************************************************
 * Conversions
 ******************************************************************/
void convert_cs16_to_word32(const void *inp, void *outp, const size_t n)
{
    uint32_t *out = (uint32_t *)outp;
    const std::complex<const int16_t> *in = (const std::complex<const int16_t> *)inp;
    for (size_t i = 0; i < n; i++)
    {
        uint16_t i16 = in[i].real();
        uint16_t q16 = in[i].imag();
        out[i] = (uint32_t(i16) << 16) | q16;
    }
}

void convert_cf32_to_word32(const void *inp, void *outp, const size_t n)
{
    uint32_t *out = (uint32_t *)outp;
    const std::complex<const float> *in = (const std::complex<const float> *)inp;
    for (size_t i = 0; i < n; i++)
    {
        uint16_t i16 = int16_t(in[i].real()*30e3f);
        uint16_t q16 = int16_t(in[i].imag()*30e3f);
        out[i] = (uint32_t(i16) << 16) | q16;
    }
}

void convert_word32_to_cs16(const void *inp, void *outp, const size_t n)
{
    const uint32_t *in = (const uint32_t *)inp;
    std::complex<int16_t> *out = (std::complex<int16_t> *)outp;
    for (size_t i = 0; i < n; i++)
    {
        int16_t i16 = uint16_t(in[i] >> 16);
        int16_t q16 = uint16_t(in[i] & 0xffff);
        out[i] = std::complex<int16_t>(i16, q16);
    }
}

void convert_word32_to_cf32(const void *inp, void *outp, const size_t n)
{
    const uint32_t *in = (const uint32_t *)inp;
    std::complex<float> *out = (std::complex<float> *)outp;
    for (size_t i = 0; i < n; i++)
    {
        int16_t i16 = uint16_t(in[i] >> 16);
        int16_t q16 = uint16_t(in[i] & 0xffff);
        out[i] = std::complex<float>(i16/30e3f, q16/30e3f);
    }
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
    //check the format config
    StreamFormat f;
    if (format == "CS16") f = SF_CS16;
    else if (format == "CF32") f = SF_CF32;
    else throw std::runtime_error("NovenaRF::setupStream: "+format);

    //check the channel config
    if (channels.size() != 1 or channels[0] != 0) throw std::runtime_error("NovenaRF::setupStream: only one channel supported");

    //store the format
    if (direction == SOAPY_SDR_TX) _txFormat = f;
    if (direction == SOAPY_SDR_RX) _rxFormat = f;

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
        _remainderHandle = -1;
        _remainderSamps = 0;
        _remainderBuff = nullptr;
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

int NovenaRF::deactivateStream(
    SoapySDR::Stream *stream,
    const int flags,
    const long long timeNs)
{
    if (int(stream) == SOAPY_SDR_RX)
    {
        int r = sendControlMessage(0x00,
            (flags & SOAPY_SDR_HAS_TIME) != 0, //timeFlag
            true, //burstFlag
            1, this->timeNsToTicks(timeNs));

        //flush rx data channel
        _framer0_rxd_chan->flush(100);

        return r;
    }

    if (int(stream) == SOAPY_SDR_TX)
    {
        //send mini end of burst transmission
        void *buffs[1];
        uint32_t buff[1];
        buffs[0] = buff;
        int f = SOAPY_SDR_END_BURST;
        this->writeStream(stream, buffs, 1, f, 0, 100);

        //flush tx stat channel
        _deframer0_stat_chan->flush(100);

        return 0;
    }

    return SOAPY_SDR_STREAM_ERROR;
}

void NovenaRF::stashConversion(const int inHandle, const void *inp, const size_t numInSamps)
{
    _remainderHandle = inHandle;
    _remainderBuff = (const uint32_t *)inp;
    _remainderSamps = numInSamps;
}

int NovenaRF::convertRemainder(void *outp, const size_t numOutSamps)
{
    if (_remainderHandle == -1) return 0; //nothing

    //convert the maximum possible number of samples
    const size_t n = std::min(_remainderSamps, numOutSamps);
    switch (_rxFormat)
    {
    case SF_CS16: convert_word32_to_cs16(_remainderBuff, outp, n); break;
    case SF_CF32: convert_word32_to_cf32(_remainderBuff, outp, n); break;
    }

    //deal with remainder and releasing buffer if done
    _remainderBuff += n;
    _remainderSamps -= n;
    if (_remainderSamps == 0)
    {
        _framer0_rxd_chan->release(_remainderHandle, 0);
        _remainderHandle = -1;
    }

    return n;
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

    //check remainder
    ret = this->convertRemainder(buffs[0], numElems);
    if (ret != 0) return ret;

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

    //no errors yet, copy buffer -- sorry for the copy, zero copy in the future...
    stashConversion(handle, payload, numSamples);
    if (ret == 0) ret = this->convertRemainder(buffs[0], numElems);

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
    switch (_txFormat)
    {
    case SF_CS16: convert_cs16_to_word32(buffs[0], payload, numSamples); break;
    case SF_CF32: convert_cf32_to_word32(buffs[0], payload, numSamples); break;
    }

    //always release the buffer back the SG engine
    _deframer0_txd_chan->release(handle, len);

    return numSamples;
}
