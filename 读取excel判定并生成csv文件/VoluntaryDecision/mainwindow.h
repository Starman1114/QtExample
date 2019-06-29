#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAxObject>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    struct Class //初始数据类型
    {
        int CS102 =0;
        int CS201 =0;
        int CS202 =0;
        int CS203 =0;
        int CS207 =0;
        int MA212 =0;

        int GE105 =0;
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_CSVButton_clicked();

private:
    void execl_StudentNumber();
    void execl_Decision();
    void ClassChange(Class *c,int index,int value);
    QString Conclude(Class *c);

private:
    Ui::MainWindow *ui;
    QStringList numberList;
    QStringList nameList;

    QList<Class> studentClass;
    QStringList className={"计算机编程基础",
                           "离散数学",
                           "计算机组成原理",
                           "数据结构与算法分析",
                           "数字逻辑",
                           "概率论与数理统计",
                           "计算机程序设计基础"
                           };
    QStringList classNumber={"CS102",
                             "CS201",
                             "CS202",
                             "CS203",
                             "CS207",
                             "MA212",
                             "GE105"
                           };
};

#endif // MAINWINDOW_H
