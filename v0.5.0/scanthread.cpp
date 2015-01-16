#include "scanthread.h"
#include "net.h"
#include "utils.h"

cScanThread::cScanThread()

{

}


cScanThread::cScanThread(const QString &_ip, int _startport, int _endport,
                         bool _addclosedport, bool _reporttofile)

{
    ip=_ip;
    startport=_startport;
    endport=_endport;
    addclosedport=_addclosedport;
    reporttofile=_reporttofile;

    startThread=0;
    progressThread=0;
    resultThread=0;
    errorThread=0;

    list=new QStringList();
}

cScanThread::~cScanThread()
{
    if(list)
    {
        delete list;
        list=0;
    }
    startThread=0;
    progressThread=0;
    resultThread=0;
    errorThread=0;
}

void cScanThread::SetCallback(threads::THREADCALLBACKSTART _callback)
{
    startThread=_callback;
}

void cScanThread::SetCallback(threads::THREADCALLBACKPROGRESS _callback)
{
    progressThread=_callback;
}

void cScanThread::SetCallback(threads::THREADCALLBACKRESULT _callback)
{
    resultThread=_callback;
}

void cScanThread::SetCallback(threads::THREADCALLBACKERROR _callback)
{
    errorThread=_callback;
}

void cScanThread::SetName(const QString &_name)
{
    name=_name;
}

const QString &cScanThread::GetName() const
{
    return  name;
}

void cScanThread::Execute()
{
    if(startThread)
        startThread(*this);
    STATEPORT port;
    if(!isIPAddress(ip))
    {
        if(errorThread)
            errorThread(*this,"invalid ip address",-1);
        return;
    }
    int len=endport-startport;
    port.ip=new QString(ip);
    for(int j=startport;j<endport;j++)
    {
        port.port=j;
        if(progressThread)
            progressThread(*this,(int)((100*(j-startport)/len)+1));
        cNet::scan_port(&port);
        if(port.portisopen)
        {
            QString state;
                switch(port.sockstate)
                {
                case QAbstractSocket::ClosingState:
                    state="Closing";
                    break;
                case QAbstractSocket::UnconnectedState:
                    state="Unconnected";
                    break;
                case QAbstractSocket::HostLookupState:
                    state="HostLookup";
                    break;
                case QAbstractSocket::ConnectingState:
                    state="Connecting";
                    break;
                case QAbstractSocket::ConnectedState:
                    state="Connected";
                    break;
                case QAbstractSocket::BoundState:
                    state="Bound";
                    break;
                case QAbstractSocket::ListeningState:
                    state="Listening";
                    break;
                }

                list->append(*(port.ip)+QString(":%1:").arg(port.port)+state);
        }else
        {
                if(addclosedport)
                {
                    list->append(*(port.ip)+QString(":%1:Closed").arg(port.port));
                }
        }
    }
    delete port.ip;

    if(resultThread)
        resultThread(*this,list);
}

