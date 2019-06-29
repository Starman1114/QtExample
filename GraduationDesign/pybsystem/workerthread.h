#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QtCore/qmath.h>
#include <QList>
#include <QQueue>
#include <QLabel>
#include "JY901.h"
#include "Com.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "datalist.h"
#include <QMutex>
#include "chart.h"
#include "function.h"

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent = 0) : QThread(parent){
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
    void stepCount(short a[3],int count);
    void changeChart();

signals:
    void resultReady(short *acc,short *gyro,short *mag,short *angle);

private:
    char chrBuffer[2000];
    unsigned short usLength=0,usCnt=0;
    signed char cResult= 1;
    Chart *C=new Chart();
    //图表数据
    Function *f= new Function();
    MathW *m= new MathW();

};

#endif // WORKERTHREAD_H
