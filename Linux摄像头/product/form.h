#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QProcess>
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_spinBox_4_valueChanged(int arg1);

    void on_horizontalSlider_4_valueChanged(int value);

    void on_spinBox_5_valueChanged(int arg1);

    void on_horizontalSlider_5_valueChanged(int value);

    void on_spinBox_6_valueChanged(int arg1);

    void on_horizontalSlider_6_valueChanged(int value);

    void on_spinBox_7_valueChanged(int arg1);

    void on_horizontalSlider_7_valueChanged(int value);

    void on_spinBox_8_valueChanged(int arg1);

    void on_horizontalSlider_8_valueChanged(int value);

    void on_spinBox_9_valueChanged(int arg1);

    void on_horizontalSlider_9_valueChanged(int value);

    void on_spinBox_10_valueChanged(int arg1);

    void on_horizontalSlider_10_valueChanged(int value);

    void on_spinBox_11_valueChanged(int arg1);

    void on_horizontalSlider_11_valueChanged(int value);

    void on_spinBox_12_valueChanged(int arg1);

    void on_horizontalSlider_12_valueChanged(int value);

    void on_spinBox_13_valueChanged(int arg1);

    void on_horizontalSlider_13_valueChanged(int value);

    void on_spinBox_14_valueChanged(int arg1);

    void on_horizontalSlider_14_valueChanged(int value);

    void on_pushButton_clicked();
    void showResult();
    void showState(QProcess::ProcessState);
    void showError();
    void showFinished(int,QProcess::ExitStatus);

    void run();
    void run1();
    void sleep(unsigned int msec);
    void on_pushButton_2_clicked();



    void on_Location_Push_clicked();

public slots:
    void pic(QString a);

private:
    Ui::Form *ui;
    QProcess myProcess;
    QByteArray procOutput;
    QString set;
    int num;
    int math;
};

#endif // FORM_H
