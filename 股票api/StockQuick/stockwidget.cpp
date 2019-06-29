#include "stockwidget.h"
#include "ui_stockwidget.h"

StockWidget::StockWidget(QWidget *parent,QStringList number,QStringList name,QStringList head,QString urlpre) :
    QWidget(parent),
    Number(number),
    Name(name),
    Head(head),
    urlPre(urlpre),
    ui(new Ui::StockWidget)
{
    ui->setupUi(this);
    QDateTime time = QDateTime::currentDateTime();
    //Time[0]->setText(time.toString("yyyy-MM-dd hh:mm:ss dddd")); //年-月-日 时-分-秒 星期
    ui->label->setText(time.toString("yyyy-MM-dd hh:mm:ss"));

    for(int i =0;i<Number.length();i++){
        onlyNumber.append(Number[i].mid(2,6));
    }

    Initialization();

    VisitTime=Number.length()/oneNumber+1;
    urltext = Number.join(",");
    getDataFromWeb();

}

StockWidget::~StockWidget()
{
    delete ui;
}

void StockWidget::Initialization()
{
    ui->tableWidget->setColumnCount(3);//只设置列数，行数动态中增加
    ui->tableWidget->setHorizontalHeaderLabels(Head);
    // connect(widget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(mathChange(int, int)));
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑


    int RowCont=0;
    for(int i=0;i<Number.length();i++){
        ui->tableWidget->insertRow(RowCont);//增加一行
        QTableWidgetItem *itemName = new QTableWidgetItem(Name[i]);
        ui->tableWidget->setItem(RowCont,0,itemName);
        QTableWidgetItem *itemNumber = new QTableWidgetItem(Number[i].right(Number[i].length()-2));
        ui->tableWidget->setItem(RowCont,1,itemNumber);
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem());
        RowCont++;
    }
}

//检索
void StockWidget::Search_Show(const QString &arg1)
{
    int len = ui->tableWidget->rowCount();
    if ("" == arg1)//判断输入是否为空
    {
        for (int i = 0; i < len; i++)
        {
            ui->tableWidget->setRowHidden(i, false);//显示所有行
        }
    }
    else
    {
        //获取符合条件的cell索引
        QList <QTableWidgetItem *> item = ui->tableWidget->findItems(arg1, Qt::MatchContains);

        for (int i = 0; i < len; i++)
        {
            ui->tableWidget->setRowHidden(i, true);//隐藏所有行
        }

        if (!item.isEmpty())//不为空
        {
            for (int i = 0; i < item.count(); i++)
            {
                ui->tableWidget->setRowHidden(item.at(i)->row(),false);//item.at(i).row()输出行号
            }
        }
    }
}

void StockWidget::sortData(int column)
{

}

void StockWidget::getDataFromWeb()
{
     if(CurrentTime<VisitTime){
         VisitNumber=oneNumber;
     }else if(CurrentTime==VisitTime){
         qDebug()<<"剩下："<<Number.length()%oneNumber;
         VisitNumber=Number.length()%oneNumber;
     }
     CurrentTime++;

     QString url = urlPre+urltext.mid((CurrentTime-2)*oneNumber*9,9*VisitNumber-1);
     //子线程
     thread = new WorkerThread(this,url);
     connect(thread,SIGNAL(resultReady(QStringList)),this,SLOT(GainData(QStringList)));
     thread->start();
}

void StockWidget::GainData(QStringList data)
{
    emit GainProcess(ReadIndex);
    if(ReadIndex==0)
        LastData.clear();
    LastData.append(data);

    if(CurrentTime<=VisitTime){
   // if(CurrentTime<=1){
        getDataFromWeb();
    }else{
        ReadIndex=0;

        for(int i=0;i<LastData.length();i++){
            ui->tableWidget->item(i,2)->setData(Qt::DisplayRole,LastData[i].toDouble());
            Delay_MSec(1);
        }
        //排序 数据完全加入再排序
        QHeaderView *headerGoods = ui->tableWidget->horizontalHeader();
        headerGoods->setSortIndicator(2, Qt::AscendingOrder);//初始哪一项不重要
        headerGoods->setSortIndicatorShown(true);
        connect(headerGoods, SIGNAL(sectionClicked(int)), ui->tableWidget, SLOT (sortByColumn(int)));
        headerGoods->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        headerGoods->setSectionResizeMode(1, QHeaderView::ResizeToContents);
        headerGoods->setSectionResizeMode(2, QHeaderView::ResizeToContents);


    }
}

void StockWidget::Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

