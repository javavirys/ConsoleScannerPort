#include "net.h"

cNet::cNet(QObject *parent) :
    QObject(parent)
{

}

QStringList *cNet::getHostsIP(QStringList *list)
{
    foreach(const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            (*list) <<  address.toString();
    }
    (*list) << "127.0.0.1";
    return list;
}

bool cNet::scan_port(QObject *parent,QString ip,qint16 port)
{
    bool ret=false;
    QTcpSocket *socket = new QTcpSocket(parent);
    socket->disconnectFromHost();
    socket->connectToHost(ip,port);
    if (socket->waitForConnected(10))
        ret=true;
    socket->close();
    delete socket;

    return ret;
}

PSTATEPORT cNet::scan_port(PSTATEPORT ret, QObject *parent)
{
    QTcpSocket *socket = new QTcpSocket(parent);

    socket->connectToHost(*(ret->ip),ret->port);
    if (socket->waitForConnected(10))
    {
        ret->portisopen=true;
        ret->sockstate=socket->state();
    }else
        ret->portisopen=false;

    socket->disconnectFromHost();
    socket->close();
    delete socket;

    return ret;
}
