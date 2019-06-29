#ifndef FUNCTION_H
#define FUNCTION_H

#include <QDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QKeyEvent>
#include <QCheckBox>
#include "functiondata.h"
#include "datalist.h"
#include "mathw.h"
#include "iconhelper.h"

namespace Ui {
class Function;
}

class Function : public QDialog
{
    Q_OBJECT

public:
    explicit Function(QWidget *parent = 0);
    ~Function();
    void Clear(); //清楚数据
    void ShowAction(QTextStream *in);//根据文件修改图像数据
    void startChartShow();
/**************************************************************************
    * 界面窗口操作
    */
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_addButton_clicked();  //添加图表

    void on_deleteButton_clicked(); //删除图表

    void functionShow();  //显示文本数据

    void functionRecord(); //记录文本数据

    void on_SaveButton_clicked();  //保存文本

    void on_openButton_clicked();  //打开文本

    void on_variaButton_clicked(); //添加变量

    void on_dele_variaButton_clicked();  //删除变量

    void colorChange(int index);

    void chartName(const QModelIndex &index);

    void keyReleaseEvent(QKeyEvent  *);

    void variaName(const QModelIndex &);

    void mathChange(const QModelIndex &);

    void ChangeMath(QStringList formula); //将数列转化为string

    void function_Widget_Add(QTabWidget *tab, FunctionD fun,int row);

    void onStateChanged(int state);//选中

    int whoChange_state();//确定选中框中谁的状态改变

    void on_ChartShowButton_clicked();

    void changeShow(const QModelIndex &);//点击图表列表，页面随之切换

    void maxChange(const QModelIndex &);

    void minChange(const QModelIndex &);

    void unitsChange(const QModelIndex &);

    void on_clearButton_clicked();

    void on_clearVButton_clicked();

    void StartShow();//软件开启的初始启动

    void on_chooseChartBox_clicked();

    void InitStyle();

/**************************************************************************
    * 界面窗口操作
    */
    void on_btnMenu_Close_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Min_clicked();

signals:
    void ChartShowSend(FunctionD fun_send);

private:
    Ui::Function *ui;
    FunctionData *F;
    FunctionD  fun;
    QStringListModel *model;
    QList<QListView*> fl; //名称
    QList<QListView*> fls; //公式
    QList<QListView*> flmax; //最大值
    QList<QListView*> flmin; //最小值
    QList<QListView*> flunits; //单位
    QList<QListView*> flc; //颜色

    QList<QStringListModel *> flm;
    QList<QStringListModel *> flsm;
    QList<QStringListModel *> flmaxm;
    QList<QStringListModel *> flminm;
    QList<QStringListModel *> flunitsm;
    QList<QStringListModel *> flcm;
    MathW *m;
    QList<bool> send_Signal;
    QList<QCheckBox*> CheckList;
    QList<QComboBox*> ColorList;
    QList<ColorIndex> ColorNum;
    FunctionD  fun_Send;

    bool ifchoose=true;

    QPoint mousePoint;
    bool mousePressed;
    bool max;
    QRect location;

};

#endif // FUNCTION_H
