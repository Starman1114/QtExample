#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QDesktopWidget> //界面放大放小
#include <QtGui>  //鼠标控制
#include <QMenuBar>  //菜单栏
#include <QtSerialPort/QSerialPort> //串口
#include <QtSerialPort/QSerialPortInfo>
#include <QVBoxLayout>
#include <QGroupBox>

#include "workerthread.h"
#include "datalist.h"
#include "function.h"
#include "setpath.h"
#include "countstep.h"
#include "datachange.h"
#include "chart.h"
#include "gaitcount.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
/**************************************************************************
    * 界面窗口操作
    */
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
/**************************************************************************
    * 界面初始化
    */
    void InitStyle();//窗口栏设置
    void SetStyle(const QString &styleName);//样式表
    void menuSetUp();//菜单栏设置
    void dataSetUp();
    void timerUpdate();//系统时间更新

/**************************************************************************
    * 图表显示设置
    */
    void ChartChangeShow(FunctionD f_Send);//图表信息改变
    void clearChartDataShow();
    void dataChartSetUp(FunctionD f);
    void clearChart();

/**************************************************************************
    * 界面窗口操作
    */
    void on_btnMenu_Close_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Min_clicked();

/**************************************************************************
    * 连接、暂停、置零按钮
    */
    void on_openButton_clicked();
    void on_cleanButton_clicked();
    void on_stopButton_clicked();

/**************************************************************************
    * 图表设置
    */
    void ChartChange(bool ok);

/**************************************************************************
    * 数据显示设置
    */
    void on_dataButton_clicked();

/**************************************************************************
    * 文件演示
    */
    void on_showButton_clicked();
    void originData();
    void dataSlider(dataStore dataStore1,int value);
    void on_horizontalSlider_valueChanged(int value);
    void on_lineEdit_textChanged(const QString &arg1);

/**************************************************************************
    * 实时播放
    */
  void on_timeSpaceBox_editingFinished();
  void on_showCountBox_editingFinished();
  void on_showCountBox_valueChanged(int arg1);

/**************************************************************************
    * 记录数据
    */
  void on_sampleRateBox_editingFinished();
  void on_sampleRateBox_valueChanged(int arg1);
  void on_recordButton_clicked();

/**************************************************************************
    * 文件下载目录设置
    */
    void OpenDir(bool ok);
    void SetDir(bool ok);

/**************************************************************************
    * 功能扩展
    */
    void countStepShow(bool ok);
    void GaitCountShow(bool ok);
    void StepClose();
    void GaitClose();

/**************************************************************************
    * 串口波特率选择
    */
    void port_chooseport(QAction *action); //选择串口
    void port_choosebaud(QAction *action);  //选择波特率
    void portFalsh(bool ok); //串口信息更新



    void on_portButton_clicked();

private:
    Ui::Dialog *ui;
    QPoint mousePoint;
    bool mousePressed;
    bool max;
    QRect location;

    QMenuBar *menus;
    QMenu *menu1;//菜单-串口
    QMenu *menu2;//串口
    QMenu *menu3;//设置
    QMenu *menu4;//功能

    QString choosenport;//选中的串口
    QString choosenbaud;//选中的波特率
    QList<QLabel*> Com; //选中端口信息更新
    QList<QLabel*> Time; //时间

    WorkerThread *workerThread;//显示速率控制
    dataChange *dC; //样本率控制

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
    QChart *chart;
    QChartView *chartView;

    QGroupBox *databox;
    int Lable_count=0;

    //图表增加
    Function *f;
    FunctionData *fd;
    FunctionD f_Tem;
    MathW *m;

    SetPath *setP;

    //记录
    bool change=false;
    Record *record1;
    bool ifstop=false;

    //播放
    bool show1=false;
    bool forshow=false;
    bool runSlider;//开始连接滚轴
    bool runAndstop;

    //计步
    CountStep *cs;
    bool csRun=false;

    //步态检测
    GaitCount *gc;
    bool gcRun=false;
};

#endif // DIALOG_H
