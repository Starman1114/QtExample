#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datalist.h"
#include "workerthread.h"
#include "choosendialog.h"
#include "setpath.h"

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
    void addCheckbox(QListWidget *widget,QString name,bool checked);


private slots:
    void on_wordButton_clicked();
    void on_execlButton_clicked();
    void getExecl();
    void changeList(int i,QString name);
    void getWord();

    void on_readButton_clicked();

    void on_createButton_clicked();

    void on_SetButton_clicked();

    void change_Check_State(int state);

    void delete_Excel();

    void check_State_Excel(QStandardItem *item);

    void OpenWord(const QModelIndex &index);

    void on_RouteButton_clicked();

    void on_RouteEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    WorkerThread *wt;

    QStringListModel *model;

    bool execl_Read = false;
    bool word_Read = false;


    QList<QCheckBox*> CheckList;
    QStandardItemModel *excelModel;
    QList<int> execlState;
    int preCheck_Index=-1;

};

#endif // MAINWINDOW_H
