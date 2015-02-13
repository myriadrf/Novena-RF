#ifndef FIFO_H
#define FIFO_H

#include <stddef.h>
#include "lmSemaphore.h"
#include <string.h>
template<class T>
class FIFO
{
public:
    FIFO() : m_slotsTaken(0), m_head(0), m_tail(0)
	{
		m_readerBlocked = false;
		m_dataSize = 16384*2*16*60;
		m_data = new T[m_dataSize];
		lmCreateSemaphore(m_lock, 1, 1);
		lmCreateSemaphore(m_blockPop, 0, 1);
    }
	FIFO(int size, const char *name = NULL) : m_slotsTaken(0), m_head(0), m_tail(0)
	{
		m_readerBlocked = false;
		m_dataSize = size;
		m_data = new T[size];
		lmCreateSemaphore(m_lock, 1, 1);
		lmCreateSemaphore(m_blockPop, 0, 1);
	}
	~FIFO()
	{
		delete []m_data;
		lmDestroySemaphore(m_lock);
		lmDestroySemaphore(m_blockPop);
	}

	/**
	@return >0:number of items popped, -1:timeout
	*/
	int pop_front(T *dest, int count, int timeout_ms = 200)
	{
		int waitStatus = lmSem_wait(m_lock, timeout_ms);
		if(waitStatus == 0)
		{
			if(m_slotsTaken < count)
			{
				m_readerBlocked = true;
				lmSem_post(m_lock);
				int readStatus = lmSem_wait(m_blockPop, timeout_ms);
				if(readStatus == 0)
					lmSem_wait(m_lock, timeout_ms);
				else
					return -1;
			}

			int itemsPopped = 0;
			int cToCopy = count;
			if(m_slotsTaken < count)
				cToCopy = m_slotsTaken;

			if( (m_tail+cToCopy) > m_dataSize)
			{
				cToCopy = m_dataSize-m_tail;
				memcpy(dest, &m_data[m_tail], cToCopy*sizeof(T));
				int cLeft = count-cToCopy;
				memcpy(&dest[cToCopy], m_data, cLeft*sizeof(T));
				m_tail = cLeft;
				itemsPopped = cToCopy+cLeft;
			}
			else
			{
				memcpy(dest, &m_data[m_head], cToCopy*sizeof(T));
				m_tail += cToCopy;
				itemsPopped = cToCopy;
			}
			m_slotsTaken -= itemsPopped;
			lmSem_post(m_lock);
			return itemsPopped;
		}
		return -1;
	}

	/**
	@return >0:number of items pushed, 0:success, -1:timeout, -2:container too small
	*/
	int push_back(T *src, const int count, bool overwrite = false, int timeout_ms = 200)
	{
		if(count > m_dataSize)
			return -2;
		int waitStatus = lmSem_wait(m_lock, timeout_ms);
		if(waitStatus == 0)
		{
			int itemsPushed = 0;
			int slotsAvailable = m_dataSize-m_slotsTaken;
			int cToCopy = count;
			if( slotsAvailable < count)
			{
				if(overwrite == false)
					cToCopy = slotsAvailable;
			}
			if( (m_head + cToCopy) > m_dataSize )
			{
				cToCopy = m_dataSize-m_head;
				memcpy(&m_data[m_head], src, cToCopy*sizeof(T));
				int cLeft = count-cToCopy;
				memcpy(m_data, &src[cToCopy], cLeft*sizeof(T));
				m_head = cLeft;
				itemsPushed = cToCopy+cLeft;
			}
			else
			{
				memcpy(&m_data[m_head], src, cToCopy*sizeof(T));
				m_head += cToCopy;
				itemsPushed = cToCopy;
			}
			m_slotsTaken += itemsPushed;
			m_head = m_head % m_dataSize;
			if(m_slotsTaken >= m_dataSize)
			{
				m_slotsTaken = m_dataSize;
				m_tail = (m_head+1)%m_dataSize;
			}
			lmSem_post(m_lock);
			return 0;
		}
		return -1;
	}

	void reset()
	{
		int waitStatus = lmSem_wait(m_lock, 1000);
		if(waitStatus == 0)
		{
			m_head = 0;
			m_tail = 0;
		}
		lmSem_post(m_lock);
	}

protected:
	char m_name[64];
	int m_slotsTaken;
	int m_dataSize;
	T *m_data;

	int m_head;
	int m_tail;

	lmSemaphore m_lock;
	lmSemaphore m_blockPop;

	bool m_readerBlocked;
};

#endif // FIFO_H
