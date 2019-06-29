#ifndef COUNT_H
#define COUNT_H
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


class Count: public QThread
{
    Q_OBJECT
public:
    explicit Count(QObject *parent = 0) : QThread(parent){
        qDebug() << "Step Thread : " << QThread::currentThreadId();
    }
    QMutex pause;
    ~Count()
       {
        // 请求终止
           requestInterruption();
           quit();
           wait();
       }

    /**************************************************************************
        * 计步算法
        */
        /***************************************************************************************************
        函数:   设置体重  单位：kg
        ***************************************************************************************************/
        void SetWeight(INT8U uW);
        INT8U GetWeight(void);
        /***************************************************************************************************
        函数:   设置身高 单位：cm
        ***************************************************************************************************/
        void SetHeight(INT8U uH);
        INT8U GetHeight(void);
        /***************************************************************************************************
        函数:   获取步数
        ***************************************************************************************************/
        INT32U GetStepNum(void);
        /***************************************************************************************************
        函数:   获取卡路里
        ***************************************************************************************************/
        INT32U GetEnergy(void);
        /***************************************************************************************************
        函数:   清除数据---步数、卡路里
        ***************************************************************************************************/
        void ClearData(void);

        /***************************************************************************************************
        函数:   处理加速度新数据.
        输入:   piNewAcc        三轴新数据.每组6字节.
                uNum            新数据组数.
        返回:   无.
        ***************************************************************************************************/
        void ArithProcessNewAccData(short * piNewAcc);

        void StepArithmatic(short * piNewAcc);//计步函数

        void EnergyArithmatic(void);//能量消耗



signals:
    void resultReady();

protected:
    virtual void run() Q_DECL_OVERRIDE ;
    unsigned short usLength=0,usCnt=0;
    char chrBuffer[2000];


    /**************************************************************************
        * 计步算法
        */
    U8 samplefz=Step_SampleRate;//样本频率
    //#define SAMPLEFZ 25//SAMPLE FREQUENCY
    S16 tempX[4]={0};// 4点平滑滤波
    S16 tempY[4]={0};
    S16 tempZ[4]={0};

    U16  mean_XYZ=0;//手腕计步变量

    U32 tempXYZ;//X^2+Y^2+Z^2
    U32 XYZ_history[Step_SampleRate]={0};
    S16 xyz_debaseline[5]={0};//DATA REMOVED BASE LINE
    S16 pre1xyz_debaseline=0;
    S16 pre2xyz_debaseline=0;
    S16 xyzpeaktmp=0;
    S16 xyzvalleytmp=0;
    S16 xyzpeakmaxdef=-32767;//低谷判断值 如果最大峰值改变，即已经遇到过低谷
    S16 xyzvalleymin=-32767;
    S16 xyzpeakmax=32767;//最大峰值存储器（一直更新）
    S16 xyzvalleythresdef=-62;
    U16 xyzpeak=0;
    U16 peak_history[4]={0};
    U16 sum_peak_his=0;
    U16 mean_peak_his=0;

    U32 datanum=0;//已经处理的三轴数据点数

    //#define MOVE_AVE_LEN 4
    U8 MoveAveLen=8*samplefz/50;//
    S16 mean_8X=0;	 //MoveAveLen个点的平滑滤波
    S16 mean_8Y=0;
    S16 mean_8Z=0;
    S32 Xsum_for8=0;
    S32 Ysum_for8=0;
    S32 Zsum_for8=0;
    U32 XYZsum_for1s=0;

    U32 xyzpeakindex=0;
    U32 xyzpeakindextmp=0;

    U8 stepflag=0;

    U32 peaknum=0;
    U8 restudy=1; //restudy=1处于临时计步阶段
    U32 STEPStartTmp=0;

    U8 tempos=0;
    U8 peakhispos=0;
    U8 basepos=0;
    U8 XYZhispos=0;

    U32 xyzpeaknum=0;
    U32 xyzvalleynum=0;

    U32 lastRestartnum=0;
    U32 prexyzstepind=0;

    //补检测变量
    U8 xyzpeakinterval[4]={0};   //补检
    U8 premean_peakinterval=0;
    U8 xyzpeakintervaladd=0;
    U8 mean_peakinterval=0;
    U8 xyzpeakintervaltmp=0;
    U32 maxflagindex=0;
    U32 premaxflagindex=0;
    U8 xyzpeakintervalStart[4]={0};
    U32 xyzintervalnum=0;
    U16 prestepmeanpeak=0;
    U8 peakintervalpos=0;
    U8 Startpeakintervalpos=0;
    U32 STEPSadd=0;

    //简单能量算法变量
    U16 timeCounter=0;	//计时器

    U16 energycoef[7]={1000,775,650,625,650,713,775};  //
    U32 CAL30STMP=0;
    U16 CAL30S1=0;
    U16 CAL30S2=0;
    U8 STEP30S=0;
    U8 STEP2S=0;
    U32 STEPbef30S=0;
    U16 ENERGY60S=0;
    U32 STEPbef60S=0;
    U8 PEAK_AVERAGE_THRESHHOLD=200;//峰值平滑线阈值

    int showCount=0;
    Chart *C = new Chart();
    int stepCount=0;
};


#endif // COUNT_H
