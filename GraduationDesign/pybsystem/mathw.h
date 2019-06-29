#ifndef MATHW_H
#define MATHW_H

#include <QWidget>
#include <QStringList>
#include "datalist.h"
#include <qmath.h>
#include <QDebug>

namespace Ui {
class MathW;
}

class MathW : public QWidget
{
    Q_OBJECT

public:
    explicit MathW(QWidget *parent = 0);
    ~MathW();
    void show_MATH(QStringList fo);//双击公式时编辑框显示出所双击的公式
    QStringList mid_to_back(QStringList f);//中序转化为后序
    float getResult(QStringList last,float *Acc1,float *Gyro1,float *Mag1,float *Angle1);
/**************************************************************************
    * 界面窗口操作
    */
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void InitStyle();

protected:


private slots:
    void on_accX_clicked();
    void on_accY_clicked();
    void on_accZ_clicked();
    void on_gyroX_clicked();
    void on_gyroY_clicked();
    void on_gyroZ_clicked();
    void on_magX_clicked();
    void on_magY_clicked();
    void on_magZ_clicked();
    void on_angleX_clicked();
    void on_angleY_clicked();
    void on_angleZ_clicked();

    void on_Acc_clicked();
    void on_Gyro_clicked();
    void on_Mag_clicked();
    void on_Angle_clicked();

    void on_add_clicked();
    void on_sub_clicked();
    void on_mul_clicked();
    void on_div_clicked();

    void on_left_clicked();
    void on_right_clicked();

    void on_copy_clicked();
    void on_paste_clicked();
    void on_back_clicked();
    void on_clear_clicked();
    void on_enter_clicked();

    void on_zero_clicked();
    void on_one_clicked();
    void on_two_clicked();
    void on_three_clicked();
    void on_four_clicked();
    void on_five_clicked();
    void on_six_clicked();
    void on_seven_clicked();
    void on_eight_clicked();
    void on_nine_clicked();

    void updataShow(); //更新公式
    void rightShow();//更正公式
    void rightShow_Symbol();//更正公式(符号)
    void rightShow_Number(QString text);//更正公式(数字)
    int findSymbol(QString line);//符号识别
    float getValue(QString a1, QString a2, QString sym,float *Acc1, float *Gyro1, float *Mag1, float *Angle1);
    float getP(QString a1,float *Acc1, float *Gyro1, float *Mag1, float *Angle1);
    int findP(QString line);
    float* returnAbs(float *Acc1,float *Gyro1,float *Mag1,float *Angle1);//算总绝对值
/**************************************************************************
    * 界面窗口操作
    */
    void on_btnMenu_Close_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Min_clicked();

signals:
    void resultReady(QStringList formula);

private:
    Ui::MathW *ui;
    QStringList formula;
    QStringList tem;
    QStringList last;

    QPoint mousePoint;
    bool mousePressed;
    bool max;
    QRect location;
};

#endif // MATHW_H
