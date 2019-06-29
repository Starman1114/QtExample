#include "gait.h"

void Gait::run(){

    while(1)
    {
        pause.lock();
        usLength = CollectUARTData(ulComNo,chrBuffer);
        if (usLength>0)
        {
            JY901.CopeSerialData(chrBuffer,usLength);
        }
        msleep(1000/Step_SampleRate);

        float acc[3];
        float Gzro[3];

        for(int k=0;k<3;k++){
            acc[k] = (float)JY901.stcAcc.a[k]/32768*16;
        }
        for(int k=0;k<3;k++){
            Gzro[k] = (float)JY901.stcGyro.w[k]/32768*2000;
        }




        if(startGait){
            short t4=JY901.stcGyro.w[0];
            if(t4>8192)
                t4=655;
            INT16S pbuf[6]={JY901.stcAcc.a[0],JY901.stcAcc.a[1],JY901.stcAcc.a[2],
                           t4,JY901.stcGyro.w[1],JY901.stcGyro.w[2]};
            Gaitanalyse(pbuf);

        //   if(showCount<(Step_SampleRate/timeSpace)){
        //       showCount++;
        //   }else{
                int count=0;
                float value;
                for(int i=0;i<ff_Gait.N;i++){
                    for(int j=0;j<ff_Gait.f[i].n;j++){
                        if(j==0)
                            value=temp;
                        else if(j==1)
                            value=valleythres;
                        else if(j==2)
                            value=peakthres;
                        C->changeData(&m_series_Gait,QString("%1").arg(value),ff_Gait.f[i],j,count);
                        axisX_Gait[i]->setRange(QDateTime::currentDateTime().addMSecs(-maxSize/timeSpace*1000),QDateTime::currentDateTime());
                        count++;
                    }
                }
         //       showCount=0;
          //  }
            //发射信号
            emit resultReady();
         }
     pause.unlock();
    }



}

/**************************************************************************
    * 步伐检测算法
    */
U8 Gait::GaitanalyseGetStepFrequence(void)
{
    return StepFrequence;
}


U8 Gait::GaitanalyseGetSwingPercent(void)
{
    return SwingPercent;
}

F32 Gait::GaitanalyseGetSpeed(void)
{
    return Speed;
}
F32 Gait::GaitanalyseGetswingSpeed(void)
{
    return SwingSpeed;
}
F32 Gait::GaitanalyseGetStrideLength(void)
{
    return StrideLength;
}


F32 Gait::GaitanalyseGetVerticalLength(void)
{
    return VerticalLength;
}



F32 Gait::GaitanalyseGetYaw(void)
{
    return Yaw1;
}

F32 Gait::GaitanalyseGetRoll(void)
{
    return Roll1;
}

F32 Gait::GaitanalyseGetheelYaw(void)
{
    return heelYaw;
}
F32 Gait::GaitanalyseGettoeYaw(void)
{
    return toeYaw;
}
F32 Gait::GaitanalyseGetheelRoll(void)
{
    return heelRoll;
}
F32 Gait::GaitanalyseGettoeRoll(void)
{
    return toeRoll;
}
void Gait::GaitanalyseClearData(void)
{
    StepFrequence = 0;    //步频
    StancePercent = 0;  //支撑相占的百分比
    SwingPercent = 0; //摆动相占的百分比；
    SwingSpeed = 0;//摆动速度，一步中前向的最大速度
    Speed = 0;
    StrideLength = 0; //步幅
    VerticalLength = 0;  //离地高度
    //q = 0;
    //p = 0;
    //hispos = 0;
//滤波变量清零
    tempos = 0;
    mean_8X = 0;
    mean_8Y = 0;
    mean_8Z = 0;
    Xsum_for8 = 0;
    Ysum_for8 = 0;
    Zsum_for8 = 0;

    mean_Gx = 0;
    mean_Gz = 0;
    mean_Gz = 0;
    Gxsum_for8 = 0;
    Gzsum_for8 = 0;
    Gzsum_for8 = 0;

    //求峰值变量
    xyzvalleytmp = 0;
    pre1_Gz = 0;
    pre2_Gz = 0;
    pre1_peak = 0;         //存的是点数
    pre2_peak = 0;
    //存三个y轴角速度的值
    pos = 0;
    //存的是峰值对应的点数
    peakpos = 0;
    xyzpeaktmp = 0;
    //处理的点数
    datanum = 0;
    //积分得到角度 ，速度，位移的变量

    flag = 0;
    flag_2 = 0;
    flag_3 = 0;
    flag_4 = 0;
    flag_5 = 0;
    flag_6 = 0;
    flag_7 = 0;
    //存数据的变量
    j = 0;
    index = 0;
    saveflag = 0;

    temp=0;
}


void Gait::Gaitanalyse(INT16S *pbuf)
{
    F32  temp1, temp2, temp3, temp4, temp5, temp6 = 0;
    datanum = datanum + 1;
    Xsum_for8 -= tempX[tempos];//minus the oldest data
    Ysum_for8 -= tempY[tempos];
    Zsum_for8 -= tempZ[tempos];
    Gxsum_for8 -= tempGx[tempos];//minus the oldest data
    Gysum_for8 -= tempGy[tempos];
    Gzsum_for8 -= tempGz[tempos];


    tempX[tempos] = *pbuf++;	 //fill in the new data
    tempY[tempos] = *pbuf++;
    tempZ[tempos] = *pbuf++;
    tempGx[tempos] = *pbuf++;	 //fill in the new data
    tempGy[tempos] = *pbuf++;
    tempGz[tempos] = *pbuf++;


    Xsum_for8 += tempX[tempos];//sum
    Ysum_for8 += tempY[tempos];
    Zsum_for8 += tempZ[tempos];
    Gxsum_for8 += tempGx[tempos];//sum
    Gysum_for8 += tempGy[tempos];
    Gzsum_for8 += tempGz[tempos];

    tempos = tempos + 1;//refresh the index
    if (tempos >= 4)
    {
        tempos = 0;
    }

    temp1 = Xsum_for8 / MoveAveLen;//smooth filter 4 data
    temp2 = Ysum_for8 / MoveAveLen;
    temp3 = Zsum_for8 / MoveAveLen;
    temp4 = Gxsum_for8 / MoveAveLen;
    temp5 = Gzsum_for8 / MoveAveLen;
    temp6 = Gzsum_for8 / MoveAveLen;

    //单位换算
    temp1 = temp1 /32768*16 * 9.81;  //米每秒
    temp2 = temp2 /32768*16 * 9.81;
    temp3 = temp3 /32768*16 * 9.81;
    temp4 = temp4 /32768*2000;  // rad/s
    temp5 = temp5 /32768*2000;
    temp6 = temp6 /32768*2000;

    if (saveflag == 1)
       {
           if (index >= 100)      //一个大概的值，与上一个heel strike 之间的时间过长，放弃掉中间的数据，重新开始算积分的起始时间；
           {
               index = 0;
               j = 0;
               startend[0] = 0;
               startend[1] = 0;
               startend[2] = 0;
           }
           else
           {
               hisAz[index] = temp3;
               hisAy[index] = temp2;
               hisGz[index] = temp6;
               hisGx[index] = temp4;
               //把积分放在这里，可以先实时一个不怎么准确的角度
               if (flag_6 == 0)  //不用积分直接赋值
               {
                   Yaw1 = 0;
                   Roll1 = 0;
                   hisYaw[index] = 0;
                   hisRoll[index] = 0;
               }
               else  //flag_6=1;
               {
                   Yaw1 = Yaw1 + (hisGz[index - 1] + hisGz[index]) / 2 * T;
                   Roll1 = Roll1 + (hisGx[index - 1] + hisGx[index]) / 2 * T;
                   hisYaw[index] = Yaw1;
                   hisRoll[index] = Roll1;
               }

               index = index + 1;
           }

       }

      // temp = sqrt(temp4*temp4 + temp5 * temp5 + temp6 * temp6);//角速度平方和开方
       temp=temp4;
       Gzpos[pos] = temp;//pos会递增 这里取y轴，因为y轴变化最明显
           pre1_Gz = Gzpos[(pos + 3 - 1) % 3];
           pre2_Gz = Gzpos[(pos + 3 - 2) % 3];

           //峰值检测
           if (pre1_Gz <= temp && pre1_Gz<pre2_Gz) //是极小值
           {
               xyzvalleytmp = pre1_Gz;
               if (xyzvalleytmp<valleythres && xyzvalleytmp<valleymin)
               {
                   valleymin = xyzvalleytmp;
                   flag_5 = 1;
               }
           }

           if (pre1_Gz >= temp && pre1_Gz>pre2_Gz)  //是极大值
           {
               xyzpeaktmp = pre1_Gz;
               if (xyzpeaktmp>peakthres)
               {
                 //  Gzpeak[peakpos] = datanum - 1;//datanum在每一次的开头就+1
                   //证明前面已经遇到一个谷值了
                   if (valleymin != valleymindef)   //谷值后面的峰值为备选的heel strike 的点
                   {
                       valleymin = valleymindef;
                       flag = 1;
                       if (flag_4==1)  //从加速度那里没有得到heelstrike 以y轴加速度的值做个近似
                       {
                           preheelnum = heelnum;
                           heelnum = datanum;
                           flag_4 = 0;
                           flag_5 = 0;
                           //计算各时相占比
                           if (preheelnum!=0)
                           {
                               StepT = (heelnum - preheelnum)*T;
                               StepFrequence = 1 / StepT*60;  //步频
                               StancePercent = (toenum-preheelnum)*T / StepT * 100;  //支撑相占的百分比
                           }
                       }
                   }else
                       flag_7 = 1;
               }
           }
           if (flag == 1)  //startend[0]-startend[1]为积分的阶段，这段时间的y轴的角速度和x轴和Z轴的加速度需要保存起来；
           {
               if (temp<isStatic)  //静止的开始时刻
               {
                   saveflag = 1;
                   flag_6 = 0;
                   index = 0;  //开始存数据
                   if (j != 0)
                   {
                       if (startend[j]==0)
                       {
                           startend[2] = datanum;
                           j = 2;
                       }
                       else
                       {
                           startend[0] = startend[2];
                           startend[2] = datanum;
                       }

                       //可以开始积分；or 进行误差补偿；
                       //对角度误差补偿 ，误差补偿从
                       INT32U k = 0;
                       INT32U k0 = startend[0];
                       INT32U k1 = startend[1];
                       INT32U k2 = startend[2];

                       for (k = k1 - k0; k <k2 - k0 ; k++)
                       {
                           hisYaw[k] = hisYaw[k] - (F32)(k - k1 + k0) / (F32)(k2 - k1-1)* (hisYaw[k2 - k0-1] - 0);
                           hisRoll[k] = hisRoll[k] - (F32)(k - k1 + k0) / (F32)(k2 - k1 - 1)* (hisRoll[k2 - k0 - 1] - 0);
                       }

                       //加速度
                       for (k = 0; k<k1 - k0; k++)
                       {
                           AZ1[k] = 0;
                           AY1[k] = 0;
                       }
                       for (k = k1 - k0; k <k2 - k0 ; k++)
                       {
                           AZ1[k] = hisAz[k] * cos(hisYaw[k]) + hisAy[k] * sin(hisYaw[k]);
                           AY1[k] = -hisAz[k] * (sin(hisYaw[k])) + hisAy[k] * (cos(hisYaw[k])) - 9.81;
                       }

                       //加速度补偿
                       for (k = k1 - k0; k <k2 - k0 + 1; k++)
                       {
                           AZ1[k] = AZ1[k] - (F32)(k - k1 + k0) / (F32)(k2 - k1-1)* (AZ1[k2 - k0-1] - 0);
                           AY1[k] = AY1[k] - (F32)(k - k1 + k0) / (F32)(k2 - k1-1)* (AY1[k2 - k0-1] - 0);
                       }
                       //速度
                       for (k = 0; k<k1 - k0; k++)
                       {
                           hisVelocityZ[k] = 0;
                           hisVelocityY[k] = 0;
                       }
                       for (k = k1 - k0; k <k2 - k0 ; k++)
                       {
                           hisVelocityZ[k] = hisVelocityZ[k - 1] + (AZ1[k - 1] + AZ1[k])/2*T;
                           hisVelocityY[k] = hisVelocityY[k - 1] + (AY1[k - 1] + AY1[k])/2*T;
                       }
                       //速度补偿
                       for (k = k1 - k0; k <k2 - k0; k++)
                       {
                           hisVelocityZ[k] = hisVelocityZ[k] - (F32)(k - k1 + k0) / (F32)(k2 - k1-1)* (hisVelocityZ[k2 - k0-1] - 0);
                           hisVelocityY[k] = hisVelocityY[k] - (F32)(k - k1 + k0) / (F32)(k2 - k1-1)* (hisVelocityY[k2 - k0-1] - 0);
                       }
                       //位移
                       for (k = 0; k<k1 - k0; k++)
                       {
                           hisLength[k] = 0;
                           hisVerLength[k] = 0;
                       }
                       for (k = k1 - k0; k <k2 - k0; k++)
                       {
                           hisLength[k] = hisLength[k - 1] + (hisVelocityZ[k - 1] + hisVelocityZ[k])/2*T;
                           hisVerLength[k] = hisVerLength[k - 1] + (hisVelocityY[k - 1] + hisVelocityY[k])/2*T;
                       }
                       //位移补偿
                       for (k = k1 - k0; k <k2 - k0; k++)
                       {
                           //hisLength[k] = hisLength[k] - (k - k1 + k0) / (k2 - k1-1)* (hisLength[k2 - k0-1] - 0);
                           hisVerLength[k] = hisVerLength[k] - (F32)(k - k1 + k0) / (F32)(k2 - k1-1)* (hisVerLength[k2 - k0-1] - 0);
                       }
                       //对前向速度求一个最大值为摆动速度
                       F32 mAZ_ = hisVelocityZ[0];
                       for (k = 1; k < k2 - k0 ; k++)
                       {
                           if (hisVelocityZ[k] > mAZ_)
                           {
                               mAZ_ = hisVelocityZ[k];
                           }

                       }
                       SwingSpeed = mAZ_;
                       //步幅
                       StrideLength = hisLength[k2 - k0-1];
                       //对离地高度求一个最大值
                       mAZ_ = hisVerLength[0];
                       for (k = 1; k < k2 - k0; k++)
                       {
                           if (hisVerLength[k] > mAZ_)
                           {
                               mAZ_ = hisVerLength[k];
                           }
                       }
                       VerticalLength = mAZ_*100;
                       toeYaw=hisYaw[toenum-k0-1]*57.3;
                       toeRoll=hisRoll[toenum-k0-1]*57.3;
                       heelYaw=hisYaw[heelnum-k0-1]*57.3;
                       heelRoll=hisRoll[heelnum-k0-1]*57.3;
                       Speed=StrideLength/((k2-k0)*T)*60;
                       //printf("%f,%f ，%f ,%f,%f,%f,%f %f\n", VerticalLength, StrideLength, SwingSpeed,toeYaw,toeRoll,heelYaw,heelRoll,Speed);
                   }
                   else
                   {
                       startend[0] = datanum;
                       j = 2;
                   }
                   flag_2 = 1;
                   flag = 0;
               }
           }
           if (flag_2 == 1)   //静止的结束时刻
           {
               if (temp>isStatic)
               {
                   startend[1] = datanum;
                   flag_2 = 0;
                   flag_3 = 1;
                   flag_6 = 1;
               }
           }

           if (flag_3 == 1&& flag_7 == 1) //过零点，即toe off
           {
               //判断条件
               if (hisGx[index-2]>0 && hisGx[index-1]<0)
               {
                   toenum = datanum;
                   flag_3 = 0;
                   flag_4 = 1;
                   flag_7 = 0;
               }

           }

           pos = pos + 1;
              if (pos == 3)
                  pos = 0;


}





