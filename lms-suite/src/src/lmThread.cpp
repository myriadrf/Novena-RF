#include "lmThread.h"

int lmThread_create( lmThread &thread, void* (*func)(void*), void* param)
{
#ifndef __unix__
    thread.m_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, param, 0, &thread.m_threadID);
    if(thread.m_thread == NULL)
        return -1;
    else
        return 0;
#else
    return pthread_create( &thread.m_thread, NULL, func, (void*) param);
#endif // __UNIX__
}

/** @return on success returns 0, otherwise error number
*/
int lmThread_join( lmThread &thread)
{
#ifndef __unix__
    return WaitForSingleObject(thread.m_thread, INFINITE);
#else
    return pthread_join(thread.m_thread, NULL);
#endif

}
