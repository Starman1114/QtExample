#include "count.h"

void Count::run(){
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
        for(int k=0;k<3;k++){
            acc[k] = (float)JY901.stcAcc.a[k]/32768*16;
        }

        if(step_Count){
            ArithProcessNewAccData(JY901.stcAcc.a);

          //  if(showCount<(Step_SampleRate/timeSpace)){
          //      showCount++;
          //  }else{
                int count=0;
                float value;
                for(int i=0;i<ff_Count.N;i++){
                    for(int j=0;j<ff_Count.f[i].n;j++){
                        if(j==0)
                            value=aOrg;
                        else if(j==1){
                            value=xyzpeakthresdef;
                        }
                        C->changeData(&m_series_Count,QString("%1").arg(value),ff_Count.f[i],j,count);
                        axisX_Count[i]->setRange(QDateTime::currentDateTime().addMSecs(-maxSize/timeSpace*1000),QDateTime::currentDateTime());
                        count++;
                    }
                }
            //    showCount=0;
          //  }
            //发射信号
            emit resultReady();
        }
     pause.unlock();
    }
}


/**************************************************************************
    * 计步算法
    */
//设置体重.
void Count::SetWeight(INT8U uW)
{
    weight1 = uW;
}
//得到体重.
INT8U Count::GetWeight(void)
{
    return weight1;
}
//设置身高.
void Count::SetHeight(INT8U uH)
{
    height1 = uH;
}
//得到身高.
INT8U Count::GetHeight(void)
{
    return height1;
}
//得到步数.
INT32U Count::GetStepNum(void)
{
    return STEPS;
}
//得到能量消耗.
INT32U Count::GetEnergy(void)
{
    return ENERGS;//unit:kcal
}
//清除数据.
void Count::ClearData(void)
{
    STEPS = 0;
    ENERGS = 0;
    mean_8X=0;
    mean_8Y=0;
    mean_8Z=0;
    Xsum_for8=0;
    Ysum_for8=0;
    Zsum_for8=0;
    XYZsum_for1s=0;
    mean_XYZ=0;
    tempos=0;
    xyzpeaknum=0;
    xyzvalleynum=0;
    tempXYZ = 0;
    basepos=0;
    XYZhispos=0;
    pre1xyz_debaseline=0;
    pre2xyz_debaseline=0;

    //tempX[4]={0};// 4点平滑滤波
    //tempY[4]={0};
    //tempZ[4]={0};
    //XYZ_history[25]={0};
    //xyz_debaseline[5]={0};
    xyzpeaktmp=0;
    xyzvalleytmp=0;
    xyzpeak=0;
    //peak_history[4]={0};
    sum_peak_his=0;
    mean_peak_his=0;
    datanum=0;
    xyzpeakindex=0;
    xyzpeakindextmp=0;
    stepflag=0;
    peaknum=0;
    restudy=1;
    STEPStartTmp=0;
    peakhispos=0;
    lastRestartnum=0;
    prexyzstepind=0;

     //xyzpeakinterval[4]={0};   //补检
 premean_peakinterval=0;
 xyzpeakintervaladd=0;
 mean_peakinterval=0;
 xyzpeakintervaltmp=0;
 maxflagindex=0;
 premaxflagindex=0;
// xyzpeakintervalStart[4]={0};
 xyzintervalnum=0;
 prestepmeanpeak=0;
 peakintervalpos=0;
 Startpeakintervalpos=0;
 STEPSadd=0;

 timeCounter=0;

  CAL30STMP=0;
CAL30S1=0;
 CAL30S2=0;
 STEP30S=0;
 STEP2S=0;
 STEPbef30S=0;
 ENERGY60S=0;
 STEPbef60S=0;

}

void Count::StepArithmatic(short * piNewAcc)
{
         //typedef unsigned long       U32;
         U32 Temp1=0;
         U32 Temp2=0;
         U32 Temp3=0;
         U8 iSTEPStartTmp=0;
         U8 jSTEPStartTmp=0;
         U8 jS=0;
//***************************************************************************************开始循环判断
         datanum=datanum+1;//已经处理的三轴数据点数
         Xsum_for8 -= tempX[tempos];//minus the oldest data  去掉原来位置上的值
         Ysum_for8 -= tempY[tempos];
         Zsum_for8 -= tempZ[tempos];

         //1/32768*16=0.0004
         tempX[tempos]=piNewAcc[0];	 //fill in the new data 取得新值
         tempY[tempos]=piNewAcc[1];
         tempZ[tempos]=piNewAcc[2];

//*****************************************数据预处理***************************************************/
            Xsum_for8 +=tempX[tempos];//sum  加上新值
            Ysum_for8 +=tempY[tempos];
            Zsum_for8 +=tempZ[tempos];

            tempos=tempos+1;//refresh the index
            if (tempos>= 4)
            {
                tempos=0;
            }
            //均值滤波
            mean_8X=Xsum_for8/MoveAveLen;//smooth filter 4 data	  每次都是将MoveAveLen值个数取平均
            mean_8Y=Ysum_for8/MoveAveLen;
            mean_8Z=Zsum_for8/MoveAveLen;

            Temp1=(U32)mean_8X*(U32)mean_8X;
            Temp2=(U32)mean_8Y*(U32)mean_8Y;
            Temp3=(U32)mean_8Z*(U32)mean_8Z;
            tempXYZ=Temp1+Temp2+Temp3; //暂时的一次的数据
            //tempXYZ=Temp1+Temp2;
            //tempXYZ=(mean_8X*mean_8X+mean_8Y*mean_8Y+mean_8Z*mean_8Z);	 //求总活动量 在8位51cpu,使用IAR编译器运行会出错！！！！！！！
            tempXYZ=tempXYZ>>6;  //这里把值右移了6位，就是乘以64
//			tempXYZ16=tempXYZ;

//get the base line 基线
            XYZ_history[XYZhispos]=tempXYZ;  //16;//历史数据记录
            XYZsum_for1s +=tempXYZ; //数据和
            if (datanum<Step_SampleRate)//已经处理的三轴数据点数未达到25个，//手腕计步变量清零
            {
                mean_XYZ=0;
            }
            else  //已经处理的三轴数据点数达到25个
            {
                mean_XYZ=XYZsum_for1s/samplefz;//get the base line
                if (XYZhispos <24)//历史数据记录未达到25时，减去后一位历史数据
                    XYZsum_for1s -= XYZ_history[XYZhispos+1];
                else//历史数据记录达到25时，减去第一位历史数据
                    XYZsum_for1s -= XYZ_history[0];
            }
            XYZhispos=XYZhispos+1;
            if (XYZhispos>=Step_SampleRate)//历史数据数达到25，则清零
            {
                XYZhispos=0;
            }

//***************************************************************峰值检测*****************************************************************/
            xyz_debaseline[basepos]=tempXYZ-mean_XYZ;//暂时的一次的数据减去手腕计步变量  长度为5 //当前值，即判断值的后一位值
            aOrg=xyz_debaseline[basepos];
            pre1xyz_debaseline=xyz_debaseline[(basepos+5-1)%5];  //判断值
            pre2xyz_debaseline=xyz_debaseline[(basepos+5-2)%5];  //判断值的前一位值

            if (pre1xyz_debaseline>pre2xyz_debaseline && pre1xyz_debaseline>=xyz_debaseline[basepos])	  //是极大值
            {
                //premaxflagindex 一个峰值的下标，但这个峰值不能算一步，用于后续判断拐点的存在
                premaxflagindex=maxflagindex; //前一位最大值下标取值最大值下标
                maxflagindex=datanum-1;//最大位下标取值（已处理数-1）

                xyzpeaktmp=pre1xyz_debaseline;//暂时峰值存储器
                 //峰值是取两个谷值之间最大的分值
                //当找到一个过零点的峰值，则开始保存前一个过零点的谷值和其发生的位置
                if (xyzpeaktmp>xyzpeakmax && xyzpeaktmp>xyzpeakthresdef)
                                                // 峰值需要满足峰值阈值条件
                {
                    xyzpeakmax=xyzpeaktmp;//
                    xyzpeakindextmp=datanum-1;//存储暂时峰值下标
                }

            }
            //若判断到谷值
            if (pre1xyz_debaseline<pre2xyz_debaseline && pre1xyz_debaseline<=xyz_debaseline[basepos])  //是极小值
            {
                xyzvalleytmp=pre1xyz_debaseline;

                if (xyzvalleytmp<0)
                {
                    if (xyzpeakmax!=xyzpeakmaxdef)//如果目前最大峰值不等于低谷判断值  也就是说前面已经遇到一个谷值了
                    {
//
                        xyzpeakindex=xyzpeakindextmp; //存储峰值坐标
                        xyzpeak=xyzpeakmax;  //保存当前峰值

                        xyzpeaknum=xyzpeaknum+1;

                        xyzpeakmax=xyzpeakmaxdef; //最大峰值重新赋值为阈值
                        stepflag=2; //满足判断条件
                        peaknum=peaknum+1; //峰值数
                    }
                }
            }
            basepos=basepos+1;
            if (basepos==5)
            {
                basepos=0;
            }

//***********************************************步伐检测约束条件*******************************************
            if (stepflag>0)
            {
                if (stepflag==2)
                {
                    //记录峰值的数列
                    peak_history[peakhispos]=xyzpeak;	  //若使用谷值来计步，需注意S32类型到U32队列的存储问题
                    sum_peak_his +=xyzpeak;
                    if (peaknum<4)//若峰值数小于数列长度
                    {
                        mean_peak_his=xyzpeak;
                    }
                    else
                    {
                        mean_peak_his=sum_peak_his/4;
                    }
                    sum_peak_his -= peak_history[(peakhispos+1)%4];
                    //判断这个峰是否可以视为一个步伐
                    if (mean_peak_his>PEAK_AVERAGE_THRESHHOLD)  //约束条件2：峰值平滑线阈值 200
                    {
                        if ((datanum-lastRestartnum)>Step_SampleRate*4)   //约束条件3：持续运动窗口 4s
                        {
                            //与上一步的时间差-->检验是否持续运动 //约束条件1：时间窗口 0.24s~1.2s
                            if ((xyzpeakindex-prexyzstepind)>Step_SampleRate*0.24 && (xyzpeakindex-prexyzstepind)<Step_SampleRate*1.2)
                            {
                                if (restudy==0)
                                {
                                    STEPS=STEPS+1;
                                    xyzintervalnum=xyzintervalnum+1;
                                }
                                else  //restudy=1则处于临时计步阶段
                                {
                                    STEPS=STEPS+STEPStartTmp+1;
                                    restudy=0;	//已经加上了临时计步数据

                                    xyzintervalnum=xyzintervalnum+STEPStartTmp+1;
                                    if (STEPStartTmp<4) //临时增加的步数小于4
                                        jS=STEPStartTmp;
                                    else
                                        jS=4;
                                    for (jSTEPStartTmp=0;jSTEPStartTmp<jS;jSTEPStartTmp++)
                                    {
                                        iSTEPStartTmp=(Startpeakintervalpos+4-jS+jSTEPStartTmp)%4;
                                        xyzpeakinterval[peakintervalpos]=xyzpeakintervalStart[iSTEPStartTmp];
                                        peakintervalpos=peakintervalpos+1;
                                        if (peakintervalpos==4)
                                        {
                                            peakintervalpos=0;
                                        }
                                    }

                                }
                                //补验，补加漏掉的步数
                            //////////////////////约束条件4：记步规则，补检////////////////////
                            xyzpeakintervaltmp=xyzpeakindex-prexyzstepind;//两步之间的时间差
                            xyzpeakinterval[peakintervalpos]=xyzpeakintervaltmp;
                            mean_peakinterval=(U8)(((U16)xyzpeakinterval[0]+(U16)xyzpeakinterval[1]+(U16)xyzpeakinterval[2]+(U16)xyzpeakinterval[3])>>2);
                            //补检条件一：当前记步间期约为前4个记步间期均值的2倍左右
                            if (xyzpeakintervaltmp>1.5*premean_peakinterval && xyzpeakintervaltmp<=3*premean_peakinterval
                                    && ((xyzpeakindextmp-prexyzstepind)>=Step_SampleRate*0.48 && (xyzpeakindextmp-prexyzstepind)<=Step_SampleRate*2.4))
                            {       //当前步与上一步的时间差大于0.48s，且小于2.4s
                                //补检条件二：当前记步峰与前一个记步峰之间有拐点（极大值）
                                //就是在两步之间，有个坐标小于等于现在这一步而且小于上一步的值-->拐点，一个不能算为一步的峰
                                if (premaxflagindex<=xyzpeakindextmp && premaxflagindex>prexyzstepind)
                                  {
                                    //补检条件三：当前峰均值与前一个峰均值差别不大，改变步态（如从跑到走）过程中不补检
                                    if (mean_peak_his>0.7*prestepmeanpeak && mean_peak_his<1.4*prestepmeanpeak)
                                       {
                                        STEPSadd=STEPSadd+1;
                                        xyzpeakintervaladd=xyzpeakintervaltmp/2;
                                        xyzpeakinterval[peakintervalpos]=xyzpeakintervaladd;
                                        xyzpeakinterval[(peakintervalpos+4-1)%4]=xyzpeakintervaladd;
                                        premean_peakinterval=(U8)(((U16)xyzpeakinterval[0]+(U16)xyzpeakinterval[1]+(U16)xyzpeakinterval[2]+(U16)xyzpeakinterval[3])/4);
                                    }else
                                        premean_peakinterval=mean_peakinterval;
                                }else
                                   premean_peakinterval=mean_peakinterval;
                            }else
                                premean_peakinterval=mean_peakinterval;

                                STEPS=STEPS+STEPSadd;//补充步数
                                STEPSadd=0;

                            prestepmeanpeak=mean_peak_his;//上一个均值
                            peakintervalpos=peakintervalpos+1;
                            if (peakintervalpos==4)
                            {
                                peakintervalpos=0;
                            }

                                 prexyzstepind=xyzpeakindex; //上一步下标更新

                            }  //与上一步时间超过1.2s
                            else if ((xyzpeakindex-prexyzstepind)>Step_SampleRate*1.2)
                            {
                                peak_history[0]=0;
                                peak_history[1]=0;
                                peak_history[2]=0;
                                peak_history[3]=0;
                                lastRestartnum=datanum;
                                peaknum=0;
                                restudy=1;		 //置重新学习标志位   //restudy=1则处于临时计步阶段
                                STEPStartTmp=0;
                                sum_peak_his=0;
                                prexyzstepind=xyzpeakindex;
                                xyzpeakinterval[0]=0;
                                xyzpeakinterval[1]=0;
                                xyzpeakinterval[2]=0;
                                xyzpeakinterval[3]=0;
                                xyzintervalnum=0;
                            }
                        }//运行小于4s
                        else if ((xyzpeakindex-prexyzstepind)>Step_SampleRate*0.24 && (xyzpeakindex-prexyzstepind)<Step_SampleRate*1.2)	  //0.24s~1.2s
                            {
                                STEPStartTmp=STEPStartTmp+1;

                                xyzpeakintervalStart[Startpeakintervalpos]=xyzpeakintervaltmp;
                                Startpeakintervalpos=Startpeakintervalpos+1;
                                if (Startpeakintervalpos==4)
                                {
                                    Startpeakintervalpos=0;
                                }

                                prexyzstepind=xyzpeakindex;
                            }
                     }
                     else//平均峰值小于阈值 --> 不能视为一步
                     {
                        peak_history[0]=0;
                        peak_history[1]=0;
                        peak_history[2]=0;
                        peak_history[3]=0;
                        lastRestartnum=datanum;
                        peaknum=0;
                        restudy=1;
                        STEPStartTmp=0;
                        sum_peak_his=0;
                        prexyzstepind=xyzpeakindex;
                        xyzpeakinterval[0]=0;
                        xyzpeakinterval[1]=0;
                        xyzpeakinterval[2]=0;
                        xyzpeakinterval[3]=0;
                        xyzintervalnum=0;
                     }
                     peakhispos=peakhispos+1;
                     if (peakhispos==4)
                     {
                        peakhispos=0;
                     }
                }


                stepflag=0;	//步伐检测归零

            }
}


void Count::EnergyArithmatic(void)
{
//************************************************能量计算***************************************************
        timeCounter=timeCounter+2;	 //每次读入5个点，25HZ采样下，相当于0.2s
        if (timeCounter==300)   //30s
        {
            STEP30S=(U8)(STEPS-STEPbef30S);
            if (STEP30S>5 && STEP30S<15)
                STEP2S=1;
            else if	(STEP30S>=105)
                STEP2S=7;
            else
                STEP2S=STEP30S/15;
            STEPbef30S=STEPS;
            if (STEP2S>0)
            {
                          CAL30STMP=(U32)STEP30S*(U32)height1*(U32)energycoef[STEP2S-1]*(U32)weight1;  //4.5*STEP30S*(height*steplen[STEP2S-1])/2*weight/1800;  //注意：对应8位mcu，公式中的强制转换（U32）是必须的，否则溢出
                        CAL30S1=(U16)(CAL30STMP/100000000);  //1kcal
            }
            else
                //CAL30S1=(U16)weight*70/1000;	  //weight*15/1800;		 0.1kcal
                          CAL30S1=0;

        }
        else if(timeCounter>=600)  //1分钟
        {
         STEP30S=(U8)(STEPS-STEPbef30S);
            if (STEP30S>5 && STEP30S<15)
                STEP2S=1;
            else if	(STEP30S>=105)
                STEP2S=7;
            else
                STEP2S=STEP30S/15;
            STEPbef30S=STEPS;
            if (STEP2S>0)
            {
                                CAL30STMP=(U32)STEP30S*(U32)height1*(U32)energycoef[STEP2S-1]*(U32)weight1;  //
                                CAL30S2=(U16)(CAL30STMP/100000000);  //1kcal
            }
            else
                //CAL30S2=(U16)weight*70/1000;	  //weight*15/1800;		 0.1kcal
                      CAL30S2=0;

           timeCounter = 0;
           ENERGY60S=CAL30S1+CAL30S2;
           ENERGS+=(U32)ENERGY60S;
           CAL30S1=0;
           CAL30S2=0;
           STEPbef60S=STEPS;
        }
}

/***************************************************************************************************
函数:   处理加速度新数据.
输入:   piNewAcc        三轴新数据.每组6字节.
        uNum            新数据组数.
返回:   无.
***************************************************************************************************/
//typedef unsigned char       INT8U;  typedef signed   short      INT16S;
void Count::ArithProcessNewAccData(short * piNewAcc)
{
    StepArithmatic(piNewAcc);
    stepCount++;
    if(stepCount==5){
        EnergyArithmatic();
        stepCount=0;
    }

}


