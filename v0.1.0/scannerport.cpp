#include "scannerport.h"

void cScannerPort::run()
{
    emit on_run();
    sIO->outList->clear();

    for(int i=sIO->startport;i<sIO->endport && isRun;i++)
    {
          bool res=cNet::scan_port(0,*(sIO->ip),i);
          emit on_progress(0,sIO->ip,i,res);
    }
    emit on_result(sIO);
}

cScannerPort::cScannerPort(QObject *parent)
{
    sIO=NULL;
}

cScannerPort::cScannerPort(PSTRUCTSCANNER io, QObject *parent)
{
    sIO=io;
}

bool cScannerPort::GetState() const
{
    return isRun;
}

void cScannerPort::SetState(bool flag)
{
    isRun=flag;
}
