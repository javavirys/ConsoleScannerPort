#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#include "jthread.h"
//#include <QObject>
#include <QString>
#include <QStringList>

namespace threads {

typedef void (*THREADCALLBACKSTART)     (const jv::JThread& _thread);
typedef void (*THREADCALLBACKPROGRESS)  (const jv::JThread& _thread,
                                         int progress);
typedef void (*THREADCALLBACKRESULT)    (const jv::JThread& _thread,
                                         const QStringList* _list);

typedef void (*THREADCALLBACKERROR)     (const jv::JThread& _thread,
                                         const QString &error,int code);
}

class cScanThread:public jv::JThread
{
public:
    cScanThread();
    cScanThread(const QString &_ip,int _startport=0,int _endport=65536,
               bool _addclosedport=false,bool _reporttofile=false);
    ~cScanThread();
    void SetCallback(threads::THREADCALLBACKSTART _callback);
    void SetCallback(threads::THREADCALLBACKPROGRESS _callback);
    void SetCallback(threads::THREADCALLBACKRESULT _callback);
    void SetCallback(threads::THREADCALLBACKERROR _callback);

    void SetName(const QString &_name);
    const QString& GetName()const;
protected:
    QString name;

    QString ip;
    int startport;
    int endport;
    bool addclosedport;
    bool reporttofile;

    QStringList *list;

    threads::THREADCALLBACKSTART     startThread;
    threads::THREADCALLBACKPROGRESS  progressThread;
    threads::THREADCALLBACKRESULT    resultThread;
    threads::THREADCALLBACKERROR     errorThread;

    void Execute();

};

#endif // SCANTHREAD_H
