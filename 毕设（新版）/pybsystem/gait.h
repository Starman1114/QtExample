#ifndef GAIT_H
#define GAIT_H
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include "datalist.h"
#include "JY901.h"
#include "Com.h"
#include "function.h"
#include "chart.h"

//定义通用的标准数据类型.
typedef char                CHAR;

typedef unsigned char       INT8U;
typedef signed   char       INT8S;

typedef unsigned short      INT16U;
typedef signed   short      INT16S;

typedef unsigned long       INT32U;
typedef signed   long       INT32S;

typedef unsigned long long  INT64U;
typedef signed   long long  INT64S;

typedef float               F32;
typedef double              F64;

typedef unsigned char       U8;
typedef signed   char       S8;

typedef unsigned short      U16;
typedef signed   short      S16;

typedef unsigned long       U32;
typedef signed   long       S32;

class Gait: public QThread
{
    Q_OBJECT
public:
    explicit Gait(QObject *parent = 0) : QThread(parent){
        qDebug() << "Gait Thread : " << QThread::currentThreadId();
    }
    QMutex pause;
    ~Gait()
       {
        // 请求终止
           requestInterruption();
           quit();
           wait();
       }
    /**************************************************************************
        * 步伐检测算法
        */
    /***************************************************************************************************
    函数:   获取步频   步/min
    输入:

    返回:   步频
    ***************************************************************************************************/
    U8 GaitanalyseGetStepFrequence(void);


    /***************************************************************************************************
    函数:   获取步幅  单位m
    输入:

    返回:   步幅
    ***************************************************************************************************/
    F32 GaitanalyseGetStrideLength(void);

    /***************************************************************************************************
    函数:   获取步速  m/min
    输入:

    返回:   步速
    ***************************************************************************************************/
    F32 GaitanalyseGetSpeed(void);


    /***************************************************************************************************
    函数:   获取摆速  m/s
    输入:

    返回:   摆速
    ***************************************************************************************************/
    F32 GaitanalyseGetswingSpeed(void);

    U8 GaitanalyseGetSwingPercent(void);

    /***************************************************************************************************
    函数:   获取支撑相占比
    输入:

    返回:   支撑相占比
    ***************************************************************************************************/
    U8 GaitanalyseGetStancePercent(void);




    /***************************************************************************************************
    函数:   获取离地高度 m
    输入:

    返回:   离地高度
    ***************************************************************************************************/
    F32 GaitanalyseGetVerticalLength(void);

    /***************************************************************************************************
    函数:   获取Yaw   deg
    输入:

    返回:   Yaw
    ***************************************************************************************************/
    F32 GaitanalyseGetYaw(void);

    /***************************************************************************************************
    函数:   获取roll   deg
    输入:

    返回:   roll
    ***************************************************************************************************/
    F32 GaitanalyseGetRoll(void);

    /***************************************************************************************************
    函数:   获取脚跟着地的Yaw  deg
    输入:

    返回:   脚跟着地的Yaw
    ***************************************************************************************************/
    F32 GaitanalyseGetheelYaw(void);

    /***************************************************************************************************
    函数:   获取脚跟着地的Roll   deg
    输入:

    返回:   脚跟着地的Roll
    ***************************************************************************************************/
    F32 GaitanalyseGetheelRoll(void);


    /***************************************************************************************************
    函数:   获取脚尖着地的Yaw  deg
    输入:

    返回:   脚尖着地的Yaw
    ***************************************************************************************************/
    F32 GaitanalyseGettoeYaw(void);


    /***************************************************************************************************
    函数:   获取脚尖离地的Roll
    输入:

    返回:   脚尖离地的Roll
    ***************************************************************************************************/
    F32 GaitanalyseGettoeRoll(void);

    /***************************************************************************************************
    函数:   清除数据---
    输入:

    返回:
    ***************************************************************************************************/
    void GaitanalyseClearData(void);


    /***************************************************************************************************
    函数:   处理加速度新数据.
    输入:   piNewAcc        六轴新数据.每组6字节.
            uNum            新数据组数.
    返回:   无.
    ***************************************************************************************************/
    void Gaitanalyse(INT16S *pbuf);

signals:
    void resultReady();


protected:
    virtual void run() Q_DECL_OVERRIDE ;
    unsigned short usLength=0,usCnt=0;
    char chrBuffer[2000];
    /**************************************************************************
        * 步伐检测算法
        */
    F32 T = 0.04;//1/25
    //***************************************************************



    //需要实时更新的
    F32  Yaw1 = 0;  //绕Z轴的角度
    F32  Roll1 = 0;  //绕X轴的角度


    //关键角度，一步一更新
    F32  toeYaw = 0;
    F32  toeRoll = 0;
    F32  heelYaw = 0;
    F32  heelRoll = 0;

    F32  StepT = 0; //步行周期

                     //求峰值变量
    F32 xyzvalleytmp = 0;

    F32 valleymin = 1;
    F32 valleymindef = 1;

    F32 valleyindextmp = 0;
    F32 pre1_Gz = 0;
    F32 pre2_Gz = 0;
    INT32U pre1_peak = 0;         //存的是点数
    INT32U pre2_peak = 0;


    F32  Gzpos[3] = { 0 };  //存三个值
    U8 pos = 0;

    INT32U Gzpeak[5] = { 0 }; //存的是峰值对应的点数
     U8 peakpos = 0;

    F32  xyzpeaktmp = 0;


    //处理的点数
    INT32U datanum = 0;

    //积分得到角度 ，速度，位移的变量
    U8 flag = 0;
    U8 flag_2 = 0;
    U8 flag_3 = 0;
    U8 flag_4 = 0;
    U8 flag_5 = 0;
    U8 flag_6 = 0;
    U8 flag_7 = 0;

    F32 hisGz[150] = { 0 };  //数组大小定义成一步之间最多的点数4*FS，即规定一步最慢用4秒
    F32 hisGx[150] = { 0 };

    F32 hisAz[150] = { 0 };
    F32 hisAy[150] = { 0 };

    F32 hisYaw[150] = { 0 }; //存角度
    F32 hisRoll[150] = { 0 }; //存角度
    F32 hisVelocityZ[150] = { 0 }; //存速度
    F32 hisVelocityY[150] = { 0 };
    F32 hisLength[150] = { 0 }; //存位移 S
    F32 hisVerLength[150] = { 0 };//存离地位移

    F32 AZ1[150] = { 0 };
    F32 AY1[150] = { 0 };

    INT32U startend[3] = { 0 }; //积分的时间点

                                //存数据的变量
    U8 j = 0;
    U8 index = 0;
    U8 saveflag = 0;


    INT32U heelnum = 0;  //存脚跟着地的点数
    INT32U preheelnum = 0;  //存前一步脚跟离地的点数
    INT32U toenum = 0;  //存脚尖离地的点数
    INT32U valleyminindex = 0;


    //滤波变量
    U8 tempos = 0;
    U8 MoveAveLen = 4;
    INT16S mean_8X = 0;
    INT16S mean_8Y = 0;
    INT16S mean_8Z = 0;
    INT32S Xsum_for8 = 0;
    INT32S Ysum_for8 = 0;
    INT32S Zsum_for8 = 0;
    INT16S tempX[4] = { 0 };
    INT16S tempY[4] = { 0 };
    INT16S tempZ[4] = { 0 };

    INT16S mean_Gx = 0;
    INT16S mean_Gy = 0;
    INT16S mean_Gz = 0;
    INT32S Gxsum_for8 = 0;
    INT32S Gysum_for8 = 0;
    INT32S Gzsum_for8 = 0;
    INT16S tempGx[4] = { 0 };
    INT16S tempGy[4] = { 0 };
    INT16S tempGz[4] = { 0 };



    int showCount=0;
    Chart *C = new Chart();
    int stepCount=0;
};

#endif // GAIT_H
