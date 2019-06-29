#ifndef DATALIST_H
#define DATALIST_H
#include <QList>
#include <QFileDialog>
#include "record.h"
#include "iconhelper.h"
#include <QChartView>
#include <QLineSeries>
#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>
#include <QLegendMarker>
#include <QComboBox>
#include <QDateTimeAxis>
#include <QMenuBar>
#include <QDesktopWidget>
using namespace QtCharts;


#define graph_width 745 //图示chart的长宽
#define graph_height 300
extern int maxSize; //chart最大显示数
extern unsigned long ulComNo;
extern unsigned long ulBaund;
extern bool running;
extern int timeSpace;//单位为毫秒
extern double SampleRate;//单位为毫秒
extern bool record;//开始记录
extern dataStore dataStore1;//记录
extern bool step_Count;//开始计步
extern unsigned long STEPS;//记录当前累积步数
extern unsigned long ENERGS;  //能量消耗
extern signed short aOrg;
extern signed short xyzpeakthresdef;//峰值阈值
extern QList<QLineSeries  *> m_series;
extern QList<QDateTimeAxis *> axisX;
extern QList<QValueAxis *> axisY;
extern QList<QLabel*> dataListShow; //数据
extern QString Path;
//修改名称
extern int type;//修改类型 图标1 变量2 公式3
extern QModelIndex ind;//修改量下标


extern QStringList cc;

struct func
{
    int n=0;
    QStringList variaName;//变量名称
    QStringList s;//公式
    QStringList ymax; //Y轴最大值
    QStringList ymin; //Y轴最小值
    QStringList units; //单位
    QStringList c;//颜色
};

struct FunctionD
{
    int N=0;
    QStringList name; //功能名
    QList<func> f;
};

extern struct FunctionD f_Recive;

class dataList
{
public:
    dataList();
};

#endif // DATALIST_H
