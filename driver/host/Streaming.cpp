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
#include "xilinx_user_gpio.h"
#include <arm_neon.h>

/*******************************************************************
 * Initialize DMA channels
 ******************************************************************/
void NovenaRF::initDMAChannels(void)
{
    _framer0_rxd_chan.reset(new NovenaDmaChannel(
        NRF_DMA_DIR_S2MM, _irq_fd, 0, _regs, REG_S2MM_FRAMER0_STAT_ADDR, REG_S2MM_FRAMER0_CTRL_ADDR,
        _framer0_mem, FRAMER0_S2MM_NUM_ENTRIES*sizeof(uint32_t), NOVENA_RF_FRAMER0_NUM_FRAMES));
    _framer0_ctrl_chan.reset(new NovenaDmaChannel(
        NRF_DMA_DIR_MM2S, _irq_fd, 1, _regs, REG_MM2S_FRAMER0_STAT_ADDR, REG_MM2S_FRAMER0_CTRL_ADDR,
        _framer0_mem, FRAMER0_MM2S_NUM_ENTRIES*sizeof(uint32_t), NOVENA_RF_FRAMER0_NUM_FRAMES));
    _deframer0_stat_chan.reset(new NovenaDmaChannel(
        NRF_DMA_DIR_S2MM, _irq_fd, 2, _regs, REG_S2MM_DEFRAMER0_STAT_ADDR, REG_S2MM_DEFRAMER0_CTRL_ADDR,
        _deframer0_mem, DEFRAMER0_S2MM_NUM_ENTRIES*sizeof(uint32_t), NOVENA_RF_DEFRAMER0_NUM_FRAMES));
    _deframer0_txd_chan.reset(new NovenaDmaChannel(
        NRF_DMA_DIR_MM2S, _irq_fd, 3, _regs, REG_MM2S_DEFRAMER0_STAT_ADDR, REG_MM2S_DEFRAMER0_CTRL_ADDR,
        _deframer0_mem, DEFRAMER0_MM2S_NUM_ENTRIES*sizeof(uint32_t), NOVENA_RF_DEFRAMER0_NUM_FRAMES));

    //init remainder state for rx
    _remainderHandle = -1;
    _remainderSamps = 0;
    _remainderBuff = nullptr;

    //this->writeRegister(REG_LMS_TRX_LOOPBACK, 1); //loopback for debug
}

/*******************************************************************
 * Conversions
 ******************************************************************/
void convert_cs16_to_word32(const void *inp, void *outp, const size_t n)
{
    std::memcpy(outp, inp, n*sizeof(uint32_t));
}

void convert_cf32_to_word32(const void *inp, void *outp, const size_t n)
{
    const float *in = (const float *)inp;
    int16_t *out = (int16_t *)outp;
    for (size_t i = 0; i < n; i+=2) //simd convert 2 complex samples
    {
        float32x4_t sampsf = vld1q_f32(in);
        float32x4_t scaled = vmulq_n_f32(sampsf, float32_t(30e3f));
        int32x4_t samps32 = vcvtq_s32_f32(scaled);
        int16x4_t samps16 = vmovn_s32(samps32);
        vst1_s16(out, samps16);
        out += 4;
        in += 4;
    }
    if ((n % 2) == 1) //remainder
    {
        *(out++) = int16_t(*(in++)*30e3f);
        *(out++) = int16_t(*(in++)*30e3f);
    }
}

void convert_word32_to_cs16(const void *inp, void *outp, const size_t n)
{
    std::memcpy(outp, inp, n*sizeof(uint32_t));
}

void convert_word32_to_cf32(const void *inp, void *outp, const size_t n)
{
    const int16_t *in = (const int16_t *)inp;
    float *out = (float *)outp;
    for (size_t i = 0; i < n; i+=2) //simd convert 2 complex samples
    {
        int16x4_t samps16 = vld1_s16(in);
        int32x4_t samps32 = vmovl_s16(samps16);
        float32x4_t sampsf = vcvtq_f32_s32(samps32);
        float32x4_t scaled = vmulq_n_f32(sampsf, float32_t(1.0/30e3f));
        vst1q_f32(out, scaled);
        out += 4;
        in += 4;
    }
    if ((n % 2) == 1) //remainder
    {
        *(out++) = float(*(in++)/30e3f);
        *(out++) = float(*(in++)/30e3f);
    }
}

/*******************************************************************
 * Stream API
 ******************************************************************/
SoapySDR::Stream *NovenaRF::setupStream(
    const int direction,
    const std::string &format,
    const std::vector<size_t> &channels_,
    const SoapySDR::Kwargs &)
{
    //check the format config
    StreamFormat f;
    if (format == "CS16") f = SF_CS16;
    else if (format == "CF32") f = SF_CF32;
    else throw std::runtime_error("NovenaRF::setupStream: "+format);

    //check the channel config
    std::vector<size_t> channels(channels_); if (channels.empty()) channels.push_back(0);
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

size_t NovenaRF::getStreamMTU(SoapySDR::Stream *stream) const
{
    if (int(stream) == SOAPY_SDR_RX)
    {
        return _framer0_rxd_chan->frameSize()/sizeof(uint32_t) - 4;
    }
    if (int(stream) == SOAPY_SDR_TX)
    {
        return _deframer0_txd_chan->frameSize()/sizeof(uint32_t) - 4;
    }
    return SoapySDR::Device::getStreamMTU(stream);
}


size_t NovenaRF::getNumDirectAccessBuffers(SoapySDR::Stream *stream)
{
    if (int(stream) == SOAPY_SDR_RX) return NOVENA_RF_FRAMER0_NUM_FRAMES;
    if (int(stream) == SOAPY_SDR_TX) return NOVENA_RF_DEFRAMER0_NUM_FRAMES;
    return SoapySDR::Device::getNumDirectAccessBuffers(stream);
}

int NovenaRF::getDirectAccessBufferAddrs(SoapySDR::Stream *stream, const size_t handle, void **buffs)
{
    if (int(stream) == SOAPY_SDR_RX)
    {
        buffs[0] = ((uint32_t *)_framer0_rxd_chan->buffer(handle)) + 4;
        return 0;
    }
    if (int(stream) == SOAPY_SDR_TX)
    {
        buffs[0] = ((uint32_t *)_deframer0_txd_chan->buffer(handle)) + 4;
        return 0;
    }
    return SoapySDR::Device::getDirectAccessBufferAddrs(stream, handle, buffs);
}

int NovenaRF::sendControlMessage(const int tag, const bool timeFlag, const bool burstFlag, const int burstSize, const long long time)
{
    size_t len = 0;
    int handle = _framer0_ctrl_chan->acquire(len);
    if (handle < 0) return SOAPY_SDR_STREAM_ERROR;

    //frame size without header and some padding
    const int frameSize = this->getStreamMTU((SoapySDR::Stream *)SOAPY_SDR_RX);

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
        _inTimedTxBurst = false;
        _userHandlesTxStatus = false;
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

/*******************************************************************
 * read stream remainder helper
 ******************************************************************/
void NovenaRF::stashConversion(const int inHandle, const void *inp, const size_t numInSamps)
{
    _remainderHandle = inHandle;
    _remainderBuff = (const uint32_t *)inp;
    _remainderSamps = numInSamps;
}

int NovenaRF::convertRemainder(void *outp, const size_t numOutSamps, int &flags)
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
        this->releaseReadBuffer((SoapySDR::Stream *)SOAPY_SDR_RX, _remainderHandle);
        _remainderHandle = -1;
    }
    else
    {
        flags |= SOAPY_SDR_MORE_FRAGMENTS;
    }

    return n;
}

/*******************************************************************
 * read stream API
 ******************************************************************/
int NovenaRF::acquireReadBuffer(
    SoapySDR::Stream *,
    size_t &handleOut,
    const void **buffs,
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
    handleOut = handle;

    //unpack the header
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
        buffs[0], numSamples, overflow, idTag,
        hasTime, timeTicks,
        timeError, isBurst, burstEnd);

    //gather time even if its not valid
    timeNs = this->ticksToTimeNs(timeTicks);

    //infer the time within a burst based on the rate so we always have a valid time
    if (hasTime) _nextRxTime = timeNs;
    timeNs = _nextRxTime;
    hasTime = true;
    _nextRxTime += long((1e9*numSamples)/getSampleRate(SOAPY_SDR_RX, 0));

    //error indicators
    if (overflow) flags |= SOAPY_SDR_END_ABRUPT;
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
        SoapySDR::log(SOAPY_SDR_SSI, "0");
        sendControlMessage(0xff, //restart streaming
            false, //timeFlag
            false, //burstFlag
            0, 0);
    }

    return (ret == 0)?numSamples:ret;
}

void NovenaRF::releaseReadBuffer(
    SoapySDR::Stream *,
    const size_t handle)
{
    _framer0_rxd_chan->release(handle, 0);
}

int NovenaRF::readStream(
    SoapySDR::Stream *stream,
    void * const *buffs,
    const size_t numElems,
    int &flags,
    long long &timeNs,
    const long timeoutUs)
{
    int ret = 0;

    //check remainder
    ret = this->convertRemainder(buffs[0], numElems, flags);
    if (ret != 0) return ret;

    //call into direct buffer access
    size_t handle;
    const void *payload;
    ret = this->acquireReadBuffer(stream, handle, &payload, flags, timeNs, timeoutUs);
    if (ret < 0) return ret;

    //no errors, convert good buffer
    stashConversion(handle, payload, ret);
    const size_t numConvert(std::min(numElems, size_t(ret)));
    return this->convertRemainder(buffs[0], numConvert, flags);
}

/*******************************************************************
 * write stream API
 ******************************************************************/
int NovenaRF::acquireWriteBuffer(
    SoapySDR::Stream *stream,
    size_t &handleOut,
    void **buffs,
    const long timeoutUs)
{
    size_t len = 0;

    //handle stat reporting when user isnt
    if (not _userHandlesTxStatus)
    {
        #define AUTO_READ_STAT_MAGIC 0x1234ABCD
        size_t chanMask = 0;
        int flags_s = AUTO_READ_STAT_MAGIC;
        long long timeNs_s = 0;
        this->readStreamStatus(stream, chanMask, flags_s, timeNs_s, 0);
    }

    //wait with timeout then acquire
    if (not _deframer0_txd_chan->waitReady(timeoutUs)) return SOAPY_SDR_TIMEOUT;
    int handle = _deframer0_txd_chan->acquire(len);
    if (handle == -1) throw std::runtime_error("NovenaRF::writeStream() all claimed");
    handleOut = handle;

    //offset by header space
    buffs[0] = ((uint32_t *)_deframer0_txd_chan->buffer(handle)) + 4;
    return (len/sizeof(uint32_t)) - 4;
}

void NovenaRF::releaseWriteBuffer(
    SoapySDR::Stream *,
    const size_t handle,
    const size_t numElems,
    int &flags,
    long long timeNs)
{
    static int id = 0;
    bool hasTime((flags & SOAPY_SDR_HAS_TIME) != 0);
    const bool burstEnd((flags & SOAPY_SDR_END_BURST) != 0);

    //infer the time within a burst based on the rate so we always have a valid time
    if (hasTime)
    {
        _nextTxTime = timeNs;
        _inTimedTxBurst = true;
    }
    timeNs = _nextTxTime;
    _nextTxTime += long((1e9*numElems)/getSampleRate(SOAPY_SDR_TX, 0));
    if (_inTimedTxBurst) hasTime = true;
    if (burstEnd) _inTimedTxBurst = false;

    //pack the header
    void *payload;
    size_t len = 0;
    const long long timeTicks(this->timeNsToTicks(timeNs));
    twbw_deframer_data_packer(
        _deframer0_txd_chan->buffer(handle), len, sizeof(uint32_t),
        payload, numElems, id++, hasTime, timeTicks, burstEnd);

    //release the buffer back the SG engine
    _deframer0_txd_chan->release(handle, len);
}

int NovenaRF::writeStream(
    SoapySDR::Stream *stream,
    const void * const *buffs,
    const size_t numElems,
    int &flags,
    const long long timeNs,
    const long timeoutUs
)
{
    //acquire from direct buffer access
    size_t handle;
    void *payload;
    int ret = this->acquireWriteBuffer(stream, handle, &payload, timeoutUs);
    if (ret < 0) return ret;

    //only end burst if the last sample can be released
    const size_t numSamples = std::min<size_t>(ret, numElems);
    if (numSamples < numElems) flags &= ~(SOAPY_SDR_END_BURST);

    //convert the samples
    switch (_txFormat)
    {
    case SF_CS16: convert_cs16_to_word32(buffs[0], payload, numSamples); break;
    case SF_CF32: convert_cf32_to_word32(buffs[0], payload, numSamples); break;
    }

    //release to direct buffer access
    this->releaseWriteBuffer(stream, handle, numSamples, flags, timeNs);
    return numSamples;
}

/*******************************************************************
 * read status stream API
 ******************************************************************/
int NovenaRF::readStreamStatus(
    SoapySDR::Stream *stream,
    size_t &chanMask,
    int &flags,
    long long &timeNs,
    const long timeoutUs
)
{
    if (int(stream) != SOAPY_SDR_TX) return SOAPY_SDR_NOT_SUPPORTED;

    //didnt get the magic keyword? then user is calling: disable tx auto stat read
    if (flags != AUTO_READ_STAT_MAGIC) _userHandlesTxStatus = true;

    chanMask = (1 << 0); //always ch0

    if (not _deframer0_stat_chan->waitReady(timeoutUs)) return SOAPY_SDR_TIMEOUT;

    size_t len = 0;
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

    //gather time even if its not valid
    timeNs = this->ticksToTimeNs(timeTicks);

    //error indicators
    if (hasTime) flags |= SOAPY_SDR_HAS_TIME;
    if (burstEnd) flags |= SOAPY_SDR_END_BURST;

    //SoapySDR::logf(SOAPY_SDR_TRACE, "handle=%d, TxStat=%d", handle, idTag);
    if (underflow) SoapySDR::log(SOAPY_SDR_SSI, "U");
    if (timeError) SoapySDR::log(SOAPY_SDR_SSI, "T");

    _deframer0_stat_chan->release(handle, len);

    if (timeError) return SOAPY_SDR_TIME_ERROR;
    if (underflow) return SOAPY_SDR_UNDERFLOW;
    return 0;
}
