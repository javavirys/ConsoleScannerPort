#include "jthread.h"

namespace jv
{
static void ThreadCallback(JThread * who)
{
#ifndef WIN32
 int old_thread_type;
 pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,&old_thread_type);
#endif
 who->Execute();
}

#ifdef WIN32

JThread::JThread()
{

}

JThread::~JThread()
{
    CloseHandle(_handle);
}

void JThread::Start()
{
    _handle=CreateThread(0,0,
                         reinterpret_cast<LPTHREAD_START_ROUTINE>(ThreadCallback),
                         this,0,0);
}

void JThread::Join()
{
    WaitForSingleObject(_handle,INFINITE);
}

void JThread::Kill()
{
    TerminateThread(_handle,0);
}
#else
JThread::JThread()
{

}

JThread::~JThread()
{

}

extern "C"
typedef void*(*pthread_callback)(void *);

void JThread::Start()
{
    pthread_create(&_handle,0,
                   reinterpret_cast<pthread_callback>(ThreadCallback),this);
}

void JThread::Join()
{
    pthread_join(_handle,0);
}

void JThread::Kill()
{
    pthread_cancel(_handle);
}
#endif
}
