#include "app.h"

#include <QDate>

#include "net.h"

#include "utils.h"

#include "console_utils.h"

void on_ThreadError(const jv::JThread& _thread,const QString& error,
                    int code);
void on_ThreadStart(const jv::JThread& _thread);

void on_ThreadProgress(const jv::JThread& _thread,int _progress);

void on_ThreadResult(const jv::JThread& _thread,const QStringList *_list);

static QStringList mlist;//главный список в который копируются списки каждого потока
static QFile *reportfile;

static int runthreadscount;//К-во запущенных потоков
static bool synchflag;//флаг служит для синхронизации функции прогресса
static int progress;//общий прогресс по всем потокам
static bool reporttofile;//сохранение в файл

QTextStream qcout(stdout);
QTextStream qcin(stdin);

App::App(QStringList &_arglist, QObject *parent) :
    QObject(parent),
    arglist(_arglist)
{
    runthreadscount=0;
    synchflag=false;
    reporttofile=false;
}

App::~App()
{

}

void App::StartApp()
{
    QStringList iplist;//иницилизация списка входных параметров
    bool runwiththread;//обьявление флага многопоточности

    runwiththread=false;
    qCout("\t\t\t\tQNetScan v0.5.0\n",LightGreen);
    qCout("\t\tVendor:\t\t\t\t javavirys\n",Green);
    //arglist.append("-s");
    if(arglist.size()>1)
    {
        if(arglist[1]=="-h"||arglist[1]=="/?"){
            qcout<<"-s(scan): [IP:Port]\tEXAMPLE:\t -s 123.0.0.0:1234"<<endl;
            qcout<<"-a(scan all ip)"<<endl;
            qcout<<"-i(get all ip)"<<endl;

        }else if(arglist[1]=="-s")
        {
            for(int i=arglist.size()-1;i>=0;i--)
            {
                if(arglist[i]=="-t")
                {
                    runwiththread=true;
                    arglist.removeAt(i);
                }else if(arglist[i]=="-r"){
                    reporttofile=true;
                    arglist.removeAt(i);
                }
            }

            for(qint16 i=2;i<arglist.size();i++)//Заходим в цикл, если есть входные данные
            {
                QString buffer=arglist[i];
                QStringList splitlist=buffer.split(':',QString::SkipEmptyParts);
                if(splitlist.size()==1)
                {
                    iplist.append(splitlist[0]);
                    ScanIP(iplist,0,65536,runwiththread);
                }else if(splitlist.size()>1)
                {
                    for(qint16 j=1;j<splitlist.size();j++)
                    {
                        int port=0;
                        port=splitlist[j].toInt();
                        iplist.append(splitlist[0]);
                        ScanIP(iplist,port,port+1,false,true);
                    }
                }

            }
        }else if(arglist[1]=="-i"){
            cNet::getHostsIP(&iplist);
            for(int i=0;i<iplist.size();i++){
                qcout<<"ip: "<<iplist[i]<<endl;
            }
        }else if(arglist[1]=="-a")
        {
            for(int i=2;i<arglist.size();i++)
            {
               if(arglist[i]=="-r")
                  reporttofile=true;
               if(arglist[i]=="-t")
                   runwiththread=true;
            }

            cNet::getHostsIP(&iplist);
            ScanIP(iplist,0,65536,runwiththread);

        }
    }else{
        //qcout<<""<<endl;

        qcout<<"Execute with -h for help"<<endl;
    }
}

void App::DestroyApp()
{

}

void App::ScanIP(const QStringList& IPList,int startport,int endport,
            bool _runwiththread,bool addclosedport)
{
    int len=0;
    int threadscount=0; //иницилизация счетчика потоков
    int threadcount=0;  //иницилизация счетчика портов на поток
    len=endport-startport;
    if(_runwiththread){
        qcout<<"With Multithreads"<<endl;
        threadcount=4096;
        threadscount=((int)(len/threadcount))+mod(len,threadcount);//1;
    }else
    {
        threadcount=len;
        threadscount=((int)(len/threadcount))+mod(len,threadcount);//1;
    }
    if(reporttofile)
        qcout<<"With Report to file"<<endl;
    qcout<<"Length: "<<len<<endl;
    qcout<<"Threads Count:"<<threadscount<<endl;

    cScanThread *threads[IPList.size()][threadscount];

    QString fileName=QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss")+".txt";
    if(reporttofile)
    {
        reportfile=new QFile(fileName);
        if(!reportfile->open(QIODevice::WriteOnly | QIODevice::Text))
        {
           reporttofile=false;
           qcout<<"Can't open file: "<<fileName<<endl;
           delete reportfile;
        }else
        {

        }
    }

    for(int i=0;i<IPList.size();i++)
    {
        qcout<<"---==="<<IPList[i]<<"===---"<<endl;
        int count=0;
        int startpos=startport;
        int endpos=startpos;
        int index=0;
        progress=0;
        for(int j=startport; j<endport; j++)
        {
            count++;
            if( count==threadcount || count+endpos==endport)
            {
                endpos+=count;
                threads[i][index]=new cScanThread(IPList[i],startpos,endpos,addclosedport);
                threads[i][index]->SetName(IPList[i]);
                threads[i][index]->SetCallback((threads::THREADCALLBACKSTART)on_ThreadStart);
                threads[i][index]->SetCallback((threads::THREADCALLBACKPROGRESS)on_ThreadProgress);
                threads[i][index]->SetCallback((threads::THREADCALLBACKRESULT)on_ThreadResult);
                threads[i][index]->Start();
                index++;
                count=0;

                startpos=endpos+1;
            }
        }

       for(int j=0;j<threadscount;j++)
       {
            threads[i][j]->Join();//ждать, пока все потоки не отработают
            delete threads[i][j];//потом удаляем все потоки
       }
    }

    if(reporttofile)
    {
        reportfile->close();
        delete reportfile;
    }

}

void on_ThreadError(const jv::JThread& _thread,const QString& error,
                    int code)
{
    qcout<<error<<endl;
}

void on_ThreadStart(const jv::JThread& _thread)
{
    runthreadscount++;
    //qcout<<"on_ThreadStart :"<<runthreadscount<<endl;
}

void on_ThreadProgress(const jv::JThread& _thread,int _progress)
{
        if(!synchflag)
        {
            synchflag=true;
    //Здесь надо сделать синхронизацию иначе возможна ошибка
            if(progress<_progress)
            {
                progress=_progress;
                qcout<<"Scanning: "<<progress<<"%\t\r";
                qcout.flush();
            }
            synchflag=false;
        }
}

void on_ThreadResult(const jv::JThread& _thread,const QStringList *_list)
{
    mlist+=*_list;
    runthreadscount--;
    if(runthreadscount==0)
    {
        for(int i=0;i<mlist.size();i++)
        {
            qcout<<mlist[i]<<endl;

        }
        qcout<<"Elements: "<<mlist.size()<<"\t"<<endl;
        if(reporttofile)
        {
            for(int i=0;i<mlist.size();i++)
            {
                reportfile->write(mlist[i].toLocal8Bit()+(char)'\n');
            }

        }
        mlist.clear();
    }
}

