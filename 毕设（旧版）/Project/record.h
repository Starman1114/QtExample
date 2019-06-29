#ifndef RECORD_H
#define RECORD_H
#include <QList>
#include <QLabel>
#include <QDateTime>
#include <qmath.h>
#include <QDebug>
struct dataStore
{
    int length=0;
    double SampleRate =25;
    QStringList sysTime; //系统时间
    QList<QStringList> dataRecord;
};

class Record
{
public:
    Record();
    void recordData(dataStore *dataStore1,
                    QDateTime sysTime,
                    QStringList Result);
    void recordData_write(dataStore *dataStore1,
                    QStringList Result);
    void clear(dataStore *dataStore1);

    QStringList returnAbs(QStringList Acc1,QStringList Gyro1,QStringList Angle1,QStringList Mag1);
};

#endif // RECORD_H
