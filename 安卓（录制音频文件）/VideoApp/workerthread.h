#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QtCore/qmath.h>
#include <QList>
#include <QQueue>
#include <QLabel>
#include "datalist.h"
#include <QMutex>

struct WAVFILEHEADER
{
    // RIFF 头
    char RiffName[4];
    unsigned long nRiffLength;

    // 数据类型标识符
    char WavName[4];

    // 格式块中的块头
    char FmtName[4];
    unsigned long nFmtLength;

    // 格式块中的块数据
    unsigned short nAudioFormat;
    unsigned short nChannleNumber;
    unsigned long nSampleRate;
    unsigned long nBytesPerSecond;
    unsigned short nBytesPerSample;
    unsigned short nBitsPerSample;

    // 数据块中的块头
    char    DATANAME[4];
    unsigned long   nDataLength;
};


class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent = 0) : QThread(parent){
        qDebug() << "Worker Thread : " << QThread::currentThreadId();
        m_pTimer = new QTimer();
        m_pTimer->setInterval(1000);
        connect(m_pTimer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));
       // m_pTimer->start();

    }

    QMutex pause;
    ~WorkerThread()
       {
        // 请求终止
           requestInterruption();
           quit();
           wait();
       }
    qint64 addWavHeader(QString catheFileName , QString wavFileName);

protected:
    virtual void run() Q_DECL_OVERRIDE ;

signals:
    void resultReady();

public slots:
    void timeoutSlot();

private:
    int count=1;
    int precount=1;
    QTimer *m_pTimer;
    bool isRecord=false;
};

#endif // WORKERTHREAD_H
