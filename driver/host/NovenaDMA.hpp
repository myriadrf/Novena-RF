////////////////////////////////////////////////////////////////////////
// SoapySDR module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdlib>
#include <vector>

enum NovenaDmaBuffState
{
    NRF_DMA_BUFF_STATE_RELEASED, //engine owns it
    NRF_DMA_BUFF_STATE_AVAILABLE, //table owns it
    NRF_DMA_BUFF_STATE_ACQUIRED, //user owns it
};

/*!
 * A helper class to keep track of DMA scatter/gather tables
 * for use in the S2MM and M2SS engines in the FPGA.
 */
class NovenaDmaSgTable
{
public:

    NovenaDmaSgTable(void *mem, const size_t numBytes, const size_t numFrames):
        _mem(mem),
        _numBytes(numBytes),
        _numFrames(numFrames),
        _bytesPerFrame(numBytes/numFrames),
        _states(numFrames),
        _lengths(numFrames),
        _headIndex(0),
        _tailIndex(0),
        _numAcquired(0)
    {
        return;
    }

    //! acquire head frame, return index or -1 for fail
    int acquireHead(size_t &length) const
    {
        
    }

    //! the number of buffers available to acquire
    size_t numAvailable(void) const
    {
        
    }

    //! mark the specified frame completed
    void markReleased(const size_t frameNum)
    {
        
    }

    //! make the tail frame completed/available
    void markTailAvailable(const size_t length)
    {
        
    }

    //! offset into mapped memory
    void *buffFromFrameNum(const size_t frameNum) const
    {
        return ((char *)_mem) + this->offsetFromFrameNum(frameNum);
    }

    //! block ram offset used for sg cmd
    size_t offsetFromFrameNum(const size_t frameNum) const
    {
        return _bytesPerFrame*frameNum;
    }

    size_t bytesPerFrame(void) const
    {
        return _bytesPerFrame;
    }

private:
    void *_mem;
    size_t _numBytes;
    size_t _numFrames;
    size_t _bytesPerFrame;
    std::vector<NovenaDmaBuffState> _states;
    std::vector<size_t> _lengths;
    size_t _headIndex;
    size_t _tailIndex;
    size_t _numAcquired;
};
