/*
 ******************************Заголовочный файл************************************
 *******************Здесь нвходится главный класс приложения************************
*/
#ifndef APP_H
#define APP_H

#include <QObject>
#include <QCoreApplication>
#include <QTextStream>
#include <QStringList>

#include <QFile>

#include "scanthread.h"

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QStringList &_arglist,QObject *parent = 0);
    ~App();
    void StartApp();//Запуск приложения
    void DestroyApp();//Остановка приложения
private:
    void ScanIP(const QStringList& IPList,int startport=0,int endport=65536,//метод сканирует
                bool _runwiththread=false,bool addclosedport=false);//IP с настройками

    QStringList arglist;

signals:

public slots:

};

#endif // APP_H
