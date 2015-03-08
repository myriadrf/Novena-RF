////////////////////////////////////////////////////////////////////////
// Helper methods for packing/unpacking TWBW framer/deframer IOs
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/*!
 * Load an outgoing control buffer.
 * \param buff the pointer to frame start
 * \param [out] length the frame length in bytes
 * \param idTag 8-bit ID tag forwarded to data header
 * \param hasTime true when timeTicks is valid
 * \param timeTicks 64-bit tick count for stream start time
 * \param isBurst true for burst mode, false continuous streaming
 * \param frameSize number of sample transfers per frame
 * \param burstSize number of sample transfers burst (in burst mode)
 */
static inline void twbw_framer_ctrl_packer(
    void *buff,
    size_t &length,
    const int idTag,
    const bool hasTime,
    const long long timeTicks,
    const bool isBurst,
    const size_t frameSize,
    const size_t burstSize
)
{
    uint32_t *msg = (uint32_t *)buff;
    msg[0] = (frameSize-1) | ((idTag & 0xff) << 16);
    if (hasTime) msg[0] |= (1 << 31);
    if (isBurst) msg[0] |= (1 << 28);
    else msg[0] |= (1 << 27);
    msg[1] = burstSize - 1;
    msg[2] = timeTicks >> 32;
    msg[3] = timeTicks & 0xffffffff;
    length = 4*sizeof(uint32_t);
}

/*!
 * Parse an incoming RX data packet.
 * \param buff the pointer to frame start
 * \param length the transfer length in bytes
 * \param width the transfer size in bytes (4, 8, ...)
 * \param [out] payload the start of the payload (offset from header)
 * \param [out] numSamps the number of samples in this packet
 * \param [out] overflow true when this packet was in an overflow
 * \param [out] idTag 8-bit ID tag forwarded from the control msg
 * \param [out] hasTime true when this packet starts a timed burst
 * \param [out] timeTicks 64-bit tick count which is always valid
 * \param [out] timeError true when a time error occurs
 * \param [out] isBurst true for burst mode, false continuous streaming
 * \param [out] burstEnd true when this packet ends a burst
 */
static inline void twbw_framer_data_unpacker(
    const void *buff,
    const size_t length,
    const size_t width,
    const void *&payload,
    size_t &numSamps,
    bool &overflow,
    int &idTag,
    bool &hasTime,
    long long &timeTicks,
    bool &timeError,
    bool &isBurst,
    bool &burstEnd
)
{
    const uint32_t *hdr = (const uint32_t *)buff;
    //supports variable width header unpacking, only lower32 bits
    const uint32_t word0 = hdr[0*(width/sizeof(uint32_t))];
    const uint32_t word1 = hdr[1*(width/sizeof(uint32_t))];
    const uint32_t word2 = hdr[2*(width/sizeof(uint32_t))];
    const uint32_t word3 = hdr[3*(width/sizeof(uint32_t))];

    //first 4 transfers are part of the header
    payload = (const void *)&hdr[4*(width/sizeof(uint32_t))];
    numSamps = (length/width) - 4;

    //extract header flags
    hasTime = ((word0 >> 31) & 0x1) != 0;
    timeError = ((word0 >> 30) & 0x1) != 0;
    isBurst = ((word0 >> 28) & 0x1) != 0;
    idTag = (word0 >> 16) & 0xff;

    //gather time even if its not valid
    timeTicks = (((long long)word2) << 32) | word3;

    //use these counts to determine overflow and end of burst
    const size_t burstCount = word1 + 1;
    const size_t frameSize = (word0 & 0xffff) + 1;

    burstEnd = false;
    overflow = (frameSize != numSamps);
    if (isBurst && burstCount == numSamps)
    {
        burstEnd = true;
        overflow = false;
    }
}

/*!
 * Load an outgoing data packet.
 * \param buff the pointer to frame start
 * \param [out] length the packet length in bytes
 * \param width the transfer size in bytes (4, 8, ...)
 * \param [out] payload the start of the payload (offset from header)
 * \param numSamps the number of samples in this packet
 * \param idTag 8-bit ID tag forwarded to data header
 * \param hasTime true when timeTicks is valid
 * \param timeTicks 64-bit tick count for stream start time
 * \param burstEnd true when this packet ends a burst
 */
static inline void twbw_deframer_data_packer(
    void *buff,
    size_t &length,
    const size_t width,
    void *&payload,
    const size_t numSamps,
    const int idTag,
    const bool hasTime,
    const long long timeTicks,
    const bool burstEnd
)
{
    uint32_t *hdr = (uint32_t *)buff;
    //supports variable width header unpacking, only lower32 bits
    uint32_t &word0 = hdr[0*(width/sizeof(uint32_t))];
    uint32_t &word1 = hdr[1*(width/sizeof(uint32_t))];
    uint32_t &word2 = hdr[2*(width/sizeof(uint32_t))];
    uint32_t &word3 = hdr[3*(width/sizeof(uint32_t))];
    payload = (void *)&hdr[4*(width/sizeof(uint32_t))];

    word0 = ((idTag & 0xff) << 16);
    if (hasTime) word0 |= (1 << 31);
    if (!burstEnd) word0 |= (1 << 27);
    word1 = 0;
    word2 = timeTicks >> 32;
    word3 = timeTicks & 0xffffffff;

    length = width*(4 + numSamps);
}

/*!
 * Parse an incoming status message.
 * \param buff the pointer to frame start
 * \param length the frame in bytes
 * \param [out] underflow true when the deframer experiences an underflow
 * \param [out] idTag 8-bit ID tag forwarded from the control msg
 * \param [out] hasTime true when this packet starts a timed burst
 * \param [out] timeTicks 64-bit tick count which is always valid
 * \param [out] timeError true when a time error occurs
 * \param [out] burstEnd true when this packet ends a burst
 */
static inline void twbw_deframer_stat_unpacker(
    void *buff,
    const size_t,
    bool &underflow,
    int &idTag,
    bool &hasTime,
    long long &timeTicks,
    bool &timeError,
    bool &burstEnd
)
{
    const uint32_t *msg = (const uint32_t *)buff;

    //extract header flags
    hasTime = ((msg[0] >> 31) & 0x1) != 0;
    timeError = ((msg[0] >> 30) & 0x1) != 0;
    underflow = ((msg[0] >> 29) & 0x1) != 0;
    burstEnd = ((msg[0] >> 28) & 0x1) != 0;
    idTag = (msg[0] >> 16) & 0xff;

    //gather time even if its not valid
    timeTicks = (((long long)msg[2]) << 32) | msg[3];
}
