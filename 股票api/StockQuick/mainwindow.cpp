#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("股票涨跌幅采集");
    SetStyle();
    ReadCsvFile(":/src/sh.csv",&SHNumber,&SHName,"sh");
    ReadCsvFile(":/src/sz.csv",&SZNumber,&SZName,"sz");
    Number.append(SHNumber);
    Number.append(SZNumber);
    Name.append(SHName);
    Name.append(SZName);
    vbox1 = new QHBoxLayout;
    ui->FirstWidget->setLayout(vbox1);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(CreatWidget()));

    this->showMaximized();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//设置皮肤样式
void MainWindow::SetStyle()
{
    QString paletteColor = "#F0F0FF";
    qApp->setPalette(QPalette(QColor(paletteColor)));
    qApp->setStyleSheet("QPushButton{"
                        "font-family: 微软雅黑;"
                        "font-weight: 450;"
                        "font-size: 16px;"
                        "color: #008080;"
                        "background-color: #FFFFFF;"
                        "border-radius: 5px;"
                        "}"
                        "QLabel{"
                        "font-family: 微软雅黑;"
                        "font-weight: 450;"
                        "font-size: 16px;"
                        "color: #008B8B;"
                        "background-color: #FFFFFF;"
                        "border-radius: 5px;"
                        "}"
                        "QPushButton:hover{"
                        "background-color: #FAF0FF;"
                        "}"
                        "QStatusBar{"
                        "background-color: #FFFFFF;"
                        "color: #008080;"
                        "}"
                        "QTabWidget,QListWidget,QTableWidget{"
                        "border-radius: 4px;"
                        "border-style: solid;"
                        "border-color: #008080;"
                        "border-width: 1px;"
                        "gridline-color:#008080;"
                        "}"
                        "QTableWidget::item:selected{"
                        "background:#B0E0E6;"
                        "}"
                        );
}

void MainWindow::CreatWidget()
{
    StockWidget *dialog1 = new StockWidget(this,Number,Name,OriginHead,urlPre);
    connect(dialog1,SIGNAL(GainProcess(int)),this,SLOT(ShowGainProcess(int)));
    connect(ui->SearchEdit,SIGNAL(textEdited(const QString &)),dialog1,SLOT(Search_Show(const QString &)));
    WidgetList.append(dialog1);
    ui->horizontalLayout_4->addWidget(dialog1,0);

}

void MainWindow::on_SpiderButton_clicked()
{
    if(!SpiderRun){
        timer->start(ui->TimeBox->value()*60*1000);

        if(WidgetIndex==0){
            dialog1 = new StockWidget(this,Number,Name,OriginHead,urlPre);
            connect(dialog1,SIGNAL(GainProcess(int)),this,SLOT(ShowGainProcess(int)));
            connect(ui->SearchEdit,SIGNAL(textEdited(const QString &)),dialog1,SLOT(Search_Show(const QString &)));
            vbox1->addWidget(dialog1);
            WidgetIndex++;
        }


        ui->SpiderButton->setText("停止爬取");
        SpiderRun=true;
    }else{
        ui->SpiderButton->setText("爬取");
        timer->stop();
        ReadIndex=0;
        SpiderRun=false;
    }
}

void MainWindow::ReadCsvFile(QString FireName,QStringList *NumberList,QStringList *NameList,QString Pre)
{
    QFile file(FireName);
    if (!file.open(QIODevice::ReadOnly)){
        return;
     }

    QTextStream * out = new QTextStream(&file);

    QStringList tempOption = out->readAll().split("\n");//每行以\n区分

    for(int i = 0 ; i < tempOption.length()-1; i++)
    {
         NumberList->append(Pre+tempOption[i].mid(tempOption[i].length()-8,6)); //***/r
         NameList->append(tempOption[i].mid(0,tempOption[i].length()-9));
    }
    file.close();
}

void MainWindow::ShowGainProcess(int Rindix)
{
    ui->statusBar->showMessage(QString("获取第 %1 条数据").arg(Rindix));
}







