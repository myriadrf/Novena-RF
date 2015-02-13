#ifndef LM_THREAD_H
#define LM_THREAD_H

#ifndef __unix__
    #include <windows.h>
#else
    #include <pthread.h>
#endif // __UNIX__

///Wrapper class for threads in Windows and Linux
class lmThread
{
public:
    lmThread()
    {
#ifndef __unix__
        m_thread=NULL;
#else
        m_thread=0;
#endif
    }
    ~lmThread()
    {

    }
#ifndef __unix__
    HANDLE m_thread;
    unsigned long m_threadID;
#else
    pthread_t m_thread;
#endif // __UNIX__
};

int lmThread_create( lmThread &thread, void* (*func)(void*), void* param);
int lmThread_join( lmThread &thread);

#endif // LM_THREAD_H

