#ifndef LM_SEMAPHORE_H
#define LM_SEMAPHORE_H

#ifdef __unix__
    #include <semaphore.h>
#endif

///Wrapper class for semaphores in Windows and Linux
class lmSemaphore
{
public:
    lmSemaphore();
    ~lmSemaphore();
    #ifndef __unix__
        void* m_sem;
        long m_semCount;
    #else
        sem_t m_sem;
    #endif // __unix__
};

int lmCreateSemaphore(lmSemaphore &sem, int initialCount, int maxCount);
int lmDestroySemaphore(lmSemaphore &sem);
int lmSem_wait(lmSemaphore &sem, unsigned long timeout_ms);
int lmSem_post(lmSemaphore &sem);
int lmSem_getvalue(lmSemaphore &sem);

#endif // LM_SEMAPHORE_H
