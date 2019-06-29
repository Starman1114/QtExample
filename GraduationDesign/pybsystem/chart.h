#ifndef CHART_H
#define CHART_H

#include <QMainWindow>
#include <QtCore>
#include <windows.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QList>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QChartView>
#include <QLineSeries>
#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>
#include <QLegendMarker>
#include <QComboBox>
#include <QDateTimeAxis>
#include <QObject>
#include "datalist.h"
#include "functiondata.h"
using namespace QtCharts;

class Chart: public QMainWindow
{
public:
    Chart();
    void setUp(QChartView *chartView,
               QChart *chart,
               QWidget *graph,
               func f,
               QList<QLineSeries *> *m_series,
               QList<QDateTimeAxis *> *axisX,
               QList<QValueAxis *> *axisY,
               int type);  //图示初始化
    void graphShowSetup(QTabWidget *tabWidget,
                        QString name,
                        QList<QDateTimeAxis *> *axisX,
                        QList<QValueAxis *> *axisY);//图示显示初始化
    //加折线
    void addSeries(QChart *chart,
                   QList<QLineSeries *> *m_series,
                   func f,
                   unsigned int lineWidth,
                   int type); //加折线

    void changeData(QList<QLineSeries *> *m_series,QString value,func f,int index,int count);//图示动态数据替换
    void becomeOrigin(FunctionD ff,QList<QLineSeries *> *m_series);//曲线值都取0
    void becomeOrigin_one(QList<QLineSeries *> *m_series,func f,int index,int count);
    void becomeOrigin_Count(FunctionD ff,QList<QLineSeries *> *m_series);//曲线值都取0
    void becomeOrigin_one_Count(QList<QLineSeries *> *m_series,func f,int index,int count,int value);
    void becomeOrigin_Gait(FunctionD ff,QList<QLineSeries *> *m_series);//曲线值都取0
    void becomeOrigin_one_Gait(QList<QLineSeries *> *m_series,func f,int index,int count,int value);

    void SliderData(QList<QLineSeries *> *m_series, int value,dataStore dataStore1,QList<QDateTimeAxis *> *axisX,FunctionD fun); //根据滚轴的值而改变
    void SliderData_one(QList<QLineSeries *> *m_series,func f,int index,int count,QList<QStringList> list,int value); //根据滚轴的值而改变
    void connectMarkers(QChart *chart);
    void disconnectMarkers(QChart *chart);
    void handleMarkerClicked();

    FunctionData *fd=new FunctionData();

};

#endif // CHART_H
