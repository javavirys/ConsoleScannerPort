/*
 ******************************Заголовочный файл************************************
 *****************Здесь нвходится класс для работы с потоком************************
*/
#ifndef JTHREAD_H
#define JTHREAD_H

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <signal.h>
#endif

namespace jv
{

#ifdef WIN32
typedef HANDLE ThreadType;
#else
typedef pthread_t ThreadType;
#endif

class JThread
{
public:
    JThread();
    virtual ~JThread();

    void Start();

    virtual void Execute() = 0;

    void Join();

    void Kill();

private:
    ThreadType _handle;
    JThread(const JThread&);
    void operator=(const JThread&);

};

}
#endif // JTHREAD_H
