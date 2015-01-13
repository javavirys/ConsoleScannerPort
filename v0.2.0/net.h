#ifndef NET_H
#define NET_H

#include <QObject>

#include <QAbstractSocket>

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>

#include <QStringList>
#include <QString>

#define OUT

#define IN

typedef struct _STRUCT_SCANNER
{
    QStringList *outList;
    QString *ip;
    qint16 startport;
    qint16 endport;
} STRUCTSCANNER,*PSTRUCTSCANNER;

typedef struct _STRUCT_STATE_PORT
{
    QString *ip;
    quint16 port;
    bool portisopen;
    QAbstractSocket::SocketState sockstate;
}STATEPORT, *PSTATEPORT;

class cNet : public QObject
{
    Q_OBJECT
public:
    explicit cNet(QObject *parent = 0);

   static QStringList *getHostsIP(QStringList *);
   static bool scan_port(QObject *parent,QString ip,qint16 port);

   static PSTATEPORT scan_port(PSTATEPORT,QObject *parent=0);
signals:

public slots:

};

#endif // NET_H
