#include "datachange.h"

void dataChange::run(){
    while(1)
    {
        pause.lock();
        usLength = CollectUARTData(ulComNo,chrBuffer);
        if (usLength>0)
        {
            JY901.CopeSerialData(chrBuffer,usLength);
        }

        msleep(1000/SampleRate);
        Result.clear();
        float acc[3];
        float gyro[3];
        float mag[3];
        float angle[3];

        for(int k=0;k<3;k++){
            acc[k] = (float)JY901.stcAcc.a[k]/32768*16;
        }
        for(int k=0;k<3;k++){
            gyro[k] = (float)JY901.stcGyro.w[k]/32768*2000;
        }
        for(int k=0;k<3;k++){
            mag[k] = (float)JY901.stcMag.h[k];
        }
        for(int k=0;k<3;k++){
            angle[k] = (float)JY901.stcAngle.Angle[k]/32768*180;
        }
        int count=0;
        for(int i=0;i<f_Recive.N;i++){
            for(int j=0;j<f_Recive.f[i].n;j++){
                QStringList l =m->mid_to_back(f_Recive.f[i].s[j].split(QRegExp("[|]")));
                float value =m->getResult(l,acc,gyro,mag,angle);
                Result.append(QString("%1").arg(value));
                count++;
            }
        }
        if(record){
            record1->recordData(&dataStore1,QDateTime::currentDateTime(),Result);
        }

     pause.unlock();
    }
}
