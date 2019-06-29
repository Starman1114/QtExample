#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QtNetwork>
#include "datalist.h"

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent = 0,QString url="") : QThread(parent),Url(url){
        qDebug() << "Worker Thread : " << QThread::currentThreadId();
    }

    QMutex pause;
    ~WorkerThread()
       {
        // 请求终止
           requestInterruption();
           quit();
           wait();
       }

protected:
    virtual void run() Q_DECL_OVERRIDE ;

signals:
    void resultReady(QStringList data);


private slots:
    void slot_requestFinished();//处理接受的数据

    void upLoadError(QNetworkReply::NetworkError code);//报错信息

    void uploadProcess(qint64 bytesReceived, qint64 bytesTotal);//接受信息

private:
    void getDataFromWeb();

private:
    QString Url;
    QNetworkReply *reply;
    QStringList RiseFall;


};

#endif // WORKERTHREAD_H
