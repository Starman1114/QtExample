#ifndef MONITOR_H
#define MONITOR_H
#include <QObject>
#include <QThread>
#include <QDebug>
#include <QtCore/qmath.h>
#include <QList>
#include <QQueue>
#include <QLabel>
#include "datalist.h"
#include <QMutex>

class Monitor : public QThread
{
    Q_OBJECT
public:
    explicit Monitor(QObject *parent = 0) : QThread(parent){
        qDebug() << "Worker Thread : " << QThread::currentThreadId();
    }

    QMutex pause;
    ~Monitor()
       {
        // 请求终止
           requestInterruption();
           quit();
           wait();
       }

protected:
    virtual void run() Q_DECL_OVERRIDE ;

signals:
    void resultReady();

private:

};

#endif // MONITOR_H
