#ifndef SCANNERPORT_H
#define SCANNERPORT_H

#include <QObject>
#include <QThread>
#include <QStringList>

#include "net.h"

class cScannerPort : public QThread
{
    Q_OBJECT
protected:
    void run() Q_DECL_OVERRIDE;

public:
    explicit cScannerPort(QObject *parent = 0);
    explicit cScannerPort(PSTRUCTSCANNER io,QObject *parent = 0);
    bool GetState()const;
    void SetState(bool flag);

private:
    PSTRUCTSCANNER sIO;
    bool isRun;
    QStringList list;
signals:
    void on_run();
    void on_progress(qint8 progress,const QString *ip,int port,bool state);
    void on_result(PSTRUCTSCANNER io);

};

#endif // SCANNERPORT_H
