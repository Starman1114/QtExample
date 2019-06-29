#include "workerthread.h"



void WorkerThread::run()
{
        while(1)
        {
            pause.lock();
            usLength = CollectUARTData(ulComNo,chrBuffer);
            if (usLength>0)
            {
                JY901.CopeSerialData(chrBuffer,usLength);
            }
            msleep(timeSpace);

            float acc[3];
            float gyro[3];
            float mag[3];
            float angle[3];

            for(int k=0;k<3;k++){
                //去除误差，有时加速度的值超出正常范围
             //  short aa =(JY901.stcAcc.a[k]/32768*16)%2;
             //  acc[k] = (float)aa;
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
                    dataListShow[count]->setText(f_Recive.f[i].variaName[j]+": "+QString("%1").arg(value)+f_Recive.f[i].units[j]);
                    C->changeData(&m_series,QString("%1").arg(value),f_Recive.f[i],j,count);
                    axisX[i]->setRange(QDateTime::currentDateTime().addMSecs(-timeSpace*maxSize),QDateTime::currentDateTime());
                    count++;

                }
            }
         pause.unlock();
        }
}

