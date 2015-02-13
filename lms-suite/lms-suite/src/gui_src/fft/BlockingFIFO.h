#ifndef BLOCKING_FIFO_H
#define BLOCKING_FIFO_H

#include <stddef.h>
#include "lmSemaphore.h"
#include <string.h>
#include <stdio.h>
template<class T>
class BlockingFIFO
{
public:
    BlockingFIFO()
    {
        m_ppTimeout = 200;
        m_fifo_length = 16;
        int packet_size = 16384;
        memset(m_name, 0, sizeof(m_name));
        //if(name != NULL)
            //strcpy(m_name, name);
        m_elements_filled = 0;
        m_head = 0;
        m_tail = 0;
        m_buffers = new T*[m_fifo_length];
        for(unsigned i=0; i<m_fifo_length; ++i)
            m_buffers[i] = new T(packet_size);
        lmCreateSemaphore(m_semR, 0, m_fifo_length);
        lmCreateSemaphore(m_semW, m_fifo_length, m_fifo_length);
    }

    ~BlockingFIFO()
    {
        for(unsigned i=0; i<m_fifo_length; ++i)
            delete m_buffers[i];
        delete []m_buffers;
        lmDestroySemaphore(m_semR);
        lmDestroySemaphore(m_semW);
    }

    void setLength(unsigned fifo_length, int pck_size)
    {
        for(unsigned i=0; i<m_fifo_length; ++i)
            delete m_buffers[i];
        delete []m_buffers;
        m_buffers = new T*[m_fifo_length];
        for(unsigned i=0; i<m_fifo_length; ++i)
            m_buffers[i] = new T(pck_size);
        lmDestroySemaphore(m_semR);
        lmDestroySemaphore(m_semW);
        lmCreateSemaphore(m_semR, 0, m_fifo_length);
        lmCreateSemaphore(m_semW, m_fifo_length, m_fifo_length);
    }

    /** @brief Copies given src element to queue.
        @param src Source data
        @return true if element was inserted

        Copies element to queue. This function blocks until element is copied to
        queue or certain amount of time has passed.
    */
    bool push_back(T *src, int timeout_ms = 200)
    {
        if(src == NULL)
            return false;

        int waitResult = lmSem_wait(m_semW, timeout_ms);
        if(waitResult == 0)
        {
            *m_buffers[m_tail] = *src;
            m_tail = (m_tail+1) % m_fifo_length;
            ++m_elements_filled;
            lmSem_post(m_semR);
            return true;
        }
        else
        {
            //printf("sem timedout push\n");
        }
        return false;
    }

    /** @brief Copies and removes first element from queue to dest.
        @param dest destination container for data
        @return true if element was copied
        Copies element from queue to destination and then removes it.
        This function blocks until element is returned, or certain amount of time
        has passed.
    */
    bool pop_front(T *dest, long timeout_ms = 200)
    {
        if(dest == NULL)
            return false;
        int waitResult;
        waitResult = lmSem_wait(m_semR, timeout_ms);
        if(waitResult == 0)
        {
            *dest = *m_buffers[m_head];
            m_head = (m_head+1) % m_fifo_length;
            --m_elements_filled;
            lmSem_post(m_semW);
            return true;
        }
        return false;
    }
    void reset()
    {
        m_elements_filled = 0;
        m_head = 0;
        m_tail = 0;
        lmDestroySemaphore(m_semR);
        lmDestroySemaphore(m_semW);
        lmCreateSemaphore(m_semR, 0, m_fifo_length);
        lmCreateSemaphore(m_semW, m_fifo_length, m_fifo_length);
    }
    void status()
    {
        int filled = 0;
        filled = lmSem_getvalue(m_semR);
        printf("%s\nhead: %i\ntail: %i\nfilled: %i\n",m_name, m_head, m_tail, filled);
    }
protected:
    char m_name[64];
    unsigned int m_elements_filled;
    unsigned int m_fifo_length; //maximum number of elements
    unsigned int m_head; //reading pos
    unsigned int m_tail; //writing pos
    unsigned long m_ppTimeout; //timeout for push pop operations

    T **m_buffers;
    lmSemaphore m_semW;
    lmSemaphore m_semR;
};

#endif // FIFO_H
