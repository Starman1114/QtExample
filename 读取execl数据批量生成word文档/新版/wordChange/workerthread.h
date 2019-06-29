#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include "datalist.h"
#include "windows.h"

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
    void execl_Data();
    void word_Gain();

protected:
    virtual void run() Q_DECL_OVERRIDE ;


signals:
    void resultReady(int i,QString name);
    void OK_execl();
    void OK_word();

private:
    QList<QStringList> Cell_Data;
    QStringList Cell_Name;
    QStringList Bookmarks_Data;
};

#endif // WORKERTHREAD_H
