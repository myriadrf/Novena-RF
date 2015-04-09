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
#include <atomic>
#include <chrono>
#include <thread>
#include "NovenaRegs.hpp"
#include "xilinx_user_gpio.h"

enum NovenaDmaDir
{
    NRF_DMA_DIR_S2MM,
    NRF_DMA_DIR_MM2S
};

/*!
 * A helper class to keep track of DMA scatter/gather tables
 * for use in the S2MM and M2SS engines in the FPGA.
 */
class NovenaDmaChannel
{
public:

    NovenaDmaChannel(
        const NovenaDmaDir dir,
        int irqFd,
        int irqBit,
        void *regs,
        const size_t statRegOff,
        const size_t ctrlRegOff,
        void *mem,
        const size_t numBytes,
        const size_t numFrames
    ):
        _dir(dir),
        _irqFd(irqFd),
        _irqBit(irqBit),
        _setIrq((uint16_t *)regs + (REG_DMA_SET_IRQ_MASK_ADDR/sizeof(uint16_t))),
        _clrIrq((uint16_t *)regs + (REG_DMA_CLR_IRQ_MASK_ADDR/sizeof(uint16_t))),
        _statReg((uint16_t *)regs + (statRegOff/sizeof(uint16_t))),
        _ctrlReg((uint16_t *)regs + (ctrlRegOff/sizeof(uint16_t))),
        _mem(mem),
        _numBytes(numBytes),
        _numFrames(numFrames),
        _frameSize(numBytes/numFrames),
        _released(numFrames),
        _lengths(numFrames),
        _headIndex(0),
        _tailIndex(0),
        _numAcquired(numFrames),
        _ignoreCount(0)
    {
        for (size_t i = 0; i < numFrames; i++)
        {
            if (_dir == NRF_DMA_DIR_S2MM) this->release(i, 0);
            if (_dir == NRF_DMA_DIR_MM2S) _numAcquired--;
        }

        //dont really check fifo for first round of MM2S
        if (_dir == NRF_DMA_DIR_MM2S) _ignoreCount = numFrames;

        //clear irq
        *_clrIrq = (1 << _irqBit);
    }

    //! wait on the head frame, return true for ready, false for timeout
    bool waitReady(const long timeoutUs)
    {
        if (_ignoreCount != 0) return true;

        //quick check without sleeping
        if (((*_statReg) >> 15) != 0) return true;
        if (timeoutUs <= 0) return false;

        //enable the irq and wait on it
        *_setIrq = (1 << _irqBit);
        const auto exitTime(std::chrono::high_resolution_clock::now() + std::chrono::microseconds(timeoutUs));
        do
        {
            //gpio poll is having wakeup issues, switching to usleep
            #if 1
            usleep(100);
            #else
            gpio_poll_irq(_irqFd, timeoutUs/1000);
            #endif
            if (((*_statReg) >> 15) != 0) break;
            std::this_thread::yield(); //shared irq for other caller
        } while (std::chrono::high_resolution_clock::now() < exitTime);
        *_clrIrq = (1 << _irqBit);

        return (((*_statReg) >> 15) != 0);
    }

    //! acquire head frame, return index or -1 for fail
    int acquire(size_t &length)
    {
        if (_numAcquired == _numFrames) return -2; //user stole all the buffers, give them back

        length = _frameSize;
        if (_ignoreCount == 0)
        {
            if (((*_statReg) >> 15) == 0) return -1; //not ready

            //stat fifo tells us the end address, subtract to get the length
            if (_dir == NRF_DMA_DIR_S2MM) length = ((*_statReg) & 0x7fff)-this->bramOffset(_headIndex);

            //write to the stat register causes pop
            *_statReg = 0;
        }
        else _ignoreCount--;

        int handle = _headIndex;
        _released[handle] = false;
        _headIndex = (_headIndex + 1) % _numFrames;
        _numAcquired++;

        return handle;
    }

    //! release buffer (out of order ok) to DMA engine
    void release(const int handle, const size_t length)
    {
        _released[handle] = true;
        _lengths[handle] = length;
        //determine the new tail (buffers may not be released in order)
        do
        {
            if (not _released[_tailIndex]) break;
            *_ctrlReg = this->bramOffset(_tailIndex);
            //mm2s direction takes 2 writes, the last write is the end addr (exclusive)
            uint16_t endAddr = this->bramOffset(_tailIndex)+_lengths[_tailIndex];
            if (_dir == NRF_DMA_DIR_MM2S) *_ctrlReg = endAddr;
            _tailIndex = (_tailIndex + 1) % _numFrames;
        }
        while (_numAcquired.fetch_sub(1) != 1);
    }

    //! offset into mapped memory for user
    void *buffer(const int handle) const
    {
        return ((char *)_mem) + this->bramOffset(handle);
    }

    //! block ram offset used for ctrl
    size_t bramOffset(const size_t handle) const
    {
        return _frameSize*handle;
    }

    //! frame size in bytes
    size_t frameSize(void) const
    {
        return _frameSize;
    }

    //! flush incoming data - for s2mm
    void flush(const long timeoutUs)
    {
        while (this->waitReady(timeoutUs))
        {
            size_t length = 0;
            int handle = this->acquire(length);
            this->release(handle, length);
        }
    }

private:
    const NovenaDmaDir _dir;
    int _irqFd;
    int _irqBit;
    volatile uint16_t *_setIrq;
    volatile uint16_t *_clrIrq;
    volatile uint16_t *_statReg;
    volatile uint16_t *_ctrlReg;
    void *_mem;
    size_t _numBytes;
    size_t _numFrames;
    size_t _frameSize;
    std::vector<bool> _released;
    std::vector<size_t> _lengths;
    size_t _headIndex;
    size_t _tailIndex;
    std::atomic<size_t> _numAcquired;
    size_t _ignoreCount;
};
