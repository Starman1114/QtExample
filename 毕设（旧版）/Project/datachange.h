#ifndef DATACHANGE_H
#define DATACHANGE_H
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include "datalist.h"
#include "record.h"
#include "JY901.h"
#include "Com.h"
#include "function.h"
class dataChange: public QThread
{
    Q_OBJECT
public:
    explicit dataChange(QObject *parent = 0) : QThread(parent){
        qDebug() << "Step Thread : " << QThread::currentThreadId();
    }
    QMutex pause;
    ~dataChange()
       {
        // 请求终止
           requestInterruption();
           quit();
           wait();
       }


protected:
    virtual void run() Q_DECL_OVERRIDE ;
    Record *record1 = new Record();
    unsigned short usLength=0,usCnt=0;
    char chrBuffer[2000];

    QStringList Result;
    MathW *m= new MathW();
};

#endif // DATACHANGE_H
