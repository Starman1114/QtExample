#include "record.h"

Record::Record()
{

}

QStringList Record::returnAbs(QStringList Acc1,QStringList Gyro1,QStringList Angle1,QStringList Mag1)
{
    double abs[4];
    QStringList list;
    for(int i = 0 ;i<3;i++){
        list.clear();
        list.append(Acc1[i]);
        list.append(Gyro1[i]);
        list.append(Mag1[i]);
        list.append(Angle1[i]);
        for(int k = 0 ;k<4;k++){
            QString l=list[k];
            abs[k] += qPow(l.toDouble(),2);
        }
    }
    QStringList data;
    for(int k = 0 ;k<4;k++){
        abs[k] = qSqrt(abs[k]);
        data.append(QString("%1").arg((float)abs[k]));
    }

    return data;
}

void Record::recordData(dataStore *dataStore1, QDateTime sysTime1,QStringList Result)
{
    dataStore1->sysTime.append(sysTime1.toString("yyyy-MM-dd hh:mm:ss.zzz"));
    dataStore1->dataRecord.append(Result);
    (dataStore1->length)++;

}

void Record::recordData_write(dataStore *dataStore1, QStringList Result)
{
    dataStore1->sysTime.append(Result[0]);
    Result.pop_front();
    dataStore1->dataRecord.append(Result);
}

void Record::clear(dataStore *dataStore1)
{
    dataStore1->sysTime.clear();
    dataStore1->dataRecord.clear();
    dataStore1->length=0;
}

