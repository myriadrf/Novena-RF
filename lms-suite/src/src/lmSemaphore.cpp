#include "lmSemaphore.h"

#ifndef __unix__
    #include <windows.h>
#else
    #include <time.h>
#endif
#include <stdio.h>
lmSemaphore::lmSemaphore()
{
#ifndef __unix__
    m_sem = INVALID_HANDLE_VALUE;
    m_semCount = 0;
#endif // __unix__
}
lmSemaphore::~lmSemaphore()
{
}

/** @brief Initializes given semaphore's initial count and max count
    @param sem semaphore to initialize
    @param initialCount initial semaphore counter
    @param maxCount max limit for semaphore counter
*/
int lmCreateSemaphore(lmSemaphore &sem, int initialCount, int maxCount)
{
    #ifndef __unix__
    sem.m_sem = CreateSemaphore(NULL, initialCount, maxCount, NULL);
    sem.m_semCount = initialCount;
    if( sem.m_sem == NULL)
    {
        printf("Error creating semaphore\n");
        return -1;
    }
    #else
    if( sem_init(&sem.m_sem, 0, initialCount) < 0)
    {
        printf("Error creating semaphore\n");
        return -1;
    }
    #endif // __unix__
    return 0;
}

/** @brief Destroys given semaphore
    @return 0 on success, -1 on failure
*/
int lmDestroySemaphore(lmSemaphore &sem)
{
    #ifndef __unix__
    if( CloseHandle(sem.m_sem) == 0)
    {
        printf("Error destroying semaphore\n");
        return -1;
    }
    #else
    if( sem_destroy(&sem.m_sem) < 0)
    {
        printf("Error destroying semaphore\n");
        return -1;
    }
    #endif // __unix__
    return 0;
}

/** @brief Wait for semaphore lock.
    @param sem semaphore object
    @param timeout_ms timeout time in miliseconds
    @return returns 0 if the semaphore is signaled, otherwise returns negative value
*/
int lmSem_wait(lmSemaphore &sem, unsigned long timeout_ms)
{
    #ifndef __unix__
    int ret = WaitForSingleObject(sem.m_sem, timeout_ms);
    if( ret == WAIT_OBJECT_0)
        return 0;
    else
        return -1;
    #else
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += timeout_ms/1000;
    ts.tv_nsec += (timeout_ms%1000)*1000000;
    if(ts.tv_nsec >= 1000000000)
    {
        ts.tv_nsec-= 1000000000;
        ++ts.tv_sec;
    }
    int ret = sem_timedwait(&sem.m_sem, &ts);
    return ret;
    //return sem_wait(&sem.m_sem);
    #endif // __unix__
}

/** @brief Signals given semaphore
    @param sem semaphore object
    @return returns 0 if semaphore was signalled successfully, otherwise returns negative value
*/
int lmSem_post(lmSemaphore &sem)
{
    #ifndef __unix__
    if( ReleaseSemaphore(sem.m_sem, 1, &sem.m_semCount) != 0)
        return 0;
    else
        return -1;
    #else
    return sem_post(&sem.m_sem);
    #endif // __unix__
}

/** @brief Returns semaphore counter
*/
int lmSem_getvalue(lmSemaphore &sem)
{
    #ifndef __unix__
        return sem.m_semCount;
    #else
        int sem_cnt = 0;
        if(sem_getvalue(&sem.m_sem, &sem_cnt) < 0)
            return -1;
        else
            return sem_cnt;
    #endif
}
