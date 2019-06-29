#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QDebug>
#include <QTimer>

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
    void closeWidget();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QStringList datalist;
    QList<int> data;
};

#endif // MAINWINDOW_H
