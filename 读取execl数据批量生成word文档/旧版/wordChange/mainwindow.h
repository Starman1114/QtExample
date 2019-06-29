#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datalist.h"
#include "workerthread.h"
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
    void on_wordButton_clicked();
    void on_execlButton_clicked();
    void getExecl();
    void changeList(int i);
    void getWord();

private:
    Ui::MainWindow *ui;
    WorkerThread *wt;

    QStringListModel *model;
};

#endif // MAINWINDOW_H
