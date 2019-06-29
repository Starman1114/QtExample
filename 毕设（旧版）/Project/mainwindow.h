#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QFileDialog>
#include<QDesktopServices>

#include <QChartView>
#include <QLineSeries>
#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>
#include <QLegendMarker>
#include <QComboBox>
#include <QDateTimeAxis>
#include <QGroupBox>
using namespace QtCharts;

#include "Com.h"
#include "time.h"
#include "stdio.h"
#include "JY901.h"
#include "workerthread.h"
#include "datalist.h"
#include "chart.h"
#include "record.h"
#include "datachange.h"
#include "function.h"
#include "setpath.h"
#include "countstep.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:

    void on_openButton_clicked();

    void on_cleanButton_clicked();

    void port_chooseport(QAction *action); //选择串口

    void port_choosebaud(QAction *action);  //选择波特率

    void timerUpdate();//系统时间更新

    void on_stopButton_clicked();

    void dataSetUp(); //数据列表初始化

    void dataChartSetUp(FunctionD f);

    void menuSetUp();  //菜单初始化

    void portFalsh(bool ok); //串口信息更新
    //void on_chooseBox_currentIndexChanged(int index);

    void on_recordButton_clicked();

    void on_showButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_timeSpaceBox_editingFinished();

    void on_timeSpaceBox_valueChanged(int arg1);

    void originData();

    void dataSlider(dataStore dataStore1,int value);

   // void on_horizontalSlider_sliderReleased();

    void ChartChangeShow(FunctionD  f_Send); //根据图表设置数据显示图表

    void clearChart();//清除图表

    void clearChartDataShow();//清除数据显示

    void on_dataButton_clicked();


    void on_sampleRateBox_editingFinished();

    void on_sampleRateBox_valueChanged(int arg1);

    void on_showCountBox_valueChanged(int arg1);

    void on_showCountBox_editingFinished();

    void initStyle();//加载样式表

    void initTranslator();

    void ChartChange(bool ok);

    void OpenDir(bool ok);

    void SetDir(bool ok);


    void countStepShow(bool ok);
    void csHide();

    void InitStyle();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_btnMenu_Close_clicked();

    void on_btnMenu_Max_clicked();

    void on_btnMenu_Min_clicked();

signals:


private:
    Ui::MainWindow *ui;
    QMenuBar *menus;
    QMenu *menu1;//菜单-串口
    QMenu *menu2;//串口
    QMenu *menu3;//设置
    QMenu *menu4;//功能
    QString choosenport;//选中的串口
    QString choosenbaud;//选中的波特率
    QList<QLabel*> Com; //选中端口信息更新
    QList<QLabel*> Time; //时间
    int Lable_count=0;
    QGroupBox *databox;


    WorkerThread *workerThread;//显示速率控制

    QStringList *data_Accx;
    QStringList *data_Gyrox;
    QStringList *data_Anglex;
    QStringList *data_Magx;

    QStringList *data_Accy;
    QStringList *data_Gyroy;
    QStringList *data_Angley;
    QStringList *data_Magy;

    QStringList *data_Accz;
    QStringList *data_Gyroz;
    QStringList *data_Anglez;
    QStringList *data_Magz;

    Chart *C;
   // QList<QLineSeries *> m_series;
   // QLineSeries *series0;  //折线
   // QLineSeries *series1;//平滑曲线
    QList<QScatterSeries *> m_scatseries;
   // QScatterSeries * scatseries0; //点
    QChart *chart;
    QChartView *chartView;


    //记录
  //  bool record;
    bool change=false;
    Record *record1;
    //dataStore dataStore1;//记录
    bool ifstop=false;

    //播放
    bool show1=false;
    bool forshow=false;
    bool runSlider;//开始连接滚轴
    bool runAndstop;
  //  QLabel* m_pLabelSliderNum;

    dataChange *dC; //样本率控制

    //图表增加
    Function *f;
    FunctionData *fd;
    FunctionD f_Tem;
    MathW *m;

    SetPath *setP;

    //计步
    CountStep *cs;
    bool csRun=false;

    //窗口栏
    QPoint mousePoint;
    bool mousePressed;
    bool max;
    QRect location;


};

#endif // MAINWINDOW_H
