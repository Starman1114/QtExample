#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wt = new WorkerThread(this);
    connect(wt,SIGNAL(OK_execl()),this,SLOT(getExecl()));
    connect(wt,SIGNAL(resultReady(int)),this,SLOT(changeList(int)));
    connect(wt,SIGNAL(OK_word()),this,SLOT(getWord()));
    model = new QStringListModel(this);
    ui->fileList->setModel(model);
    ui->wordButton->setDisabled(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeList(int i){
    int count = model->stringList().length();
    model->insertRows(count, 1);
    QModelIndex index = model->index(count); //图表下标
    model->setData(index, Name_Class[i]+"--"+QString::number(i+1));
}

void MainWindow::getWord()
{
    ui->statusBar->showMessage("运行完毕");
}

void MainWindow::on_wordButton_clicked()
{
    //清空前面留下的数据
    int i=model->stringList().length();
    for(;i>0;i--){
        model->removeRows(i-1, 1);
    }
    ui->statusBar->showMessage("正在生成word文件......");
    current_STATE=WORD_START;
    wt->start();
}

void MainWindow::on_execlButton_clicked()
{
    ui->statusBar->showMessage("正在获取列表信息......");
    current_STATE=EXECL_START;
    wt->start();

}

void MainWindow::getExecl()
{
    ui->wordButton->setEnabled(true);
    ui->statusBar->showMessage("成功获取列表信息");
    ui->lineEdit->setText(QString("总行数：%1").arg(QString::number(intRow)));

}
