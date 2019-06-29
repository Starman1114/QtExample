#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMenu>
#include <QKeyEvent>
#include "cssdatawidget.h"
#include "aboutcss.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void InitStyle();
    QString IntToHex(int number);

private slots:
    void on_runSetButton_clicked();
  //  void BackGround_ColorChange();

    //背景颜色设置
    void on_RspinBox_valueChanged(int arg1);

    void on_GspinBox_valueChanged(int arg1);

    void on_BspinBox_valueChanged(int arg1);

    void on_HEXEdit_textChanged(const QString &arg1);

    void ShowAboutCss(bool ok);//展现CSS相关文本

    void on_runTextButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

protected:
    void keyPressEvent(QKeyEvent *);

private:
    Ui::MainWindow *ui;
    CssDataWidget *widget_Font;
    CssDataWidget *widget_Backgroup;
    CssDataWidget *widget_Border;
    QMenu *menu1;
};

#endif // MAINWINDOW_H
