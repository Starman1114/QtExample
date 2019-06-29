#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitStyle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitStyle()
{
    setWindowTitle("股票数据采集");
    ReadData(":/src/OriginSet.txt");
    SetStyle();

    for(int i=0;i<urlName.length();i++){
        QTableWidget *widget = new QTableWidget;
        widget->setColumnCount(Data_Head[i].length());//只设置列数，行数动态中增加
        widget->setHorizontalHeaderLabels(Data_Head[i]);
        // connect(widget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(mathChange(int, int)));
        widget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑

        //排序
        QHeaderView *headerGoods = widget->horizontalHeader();
        headerGoods->setSortIndicator(0, Qt::AscendingOrder);//初始哪一项不重要
        headerGoods->setSortIndicatorShown(true);
        connect(headerGoods, SIGNAL(sectionClicked(int)), widget, SLOT (sortByColumn(int)));
        tableList.append(widget);
        ui->tabWidget->addTab(widget,urlName[i]);

    }
    Current_url=url[0];
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

void MainWindow::AddItemWidget(QStringList data,int num){
    int RowCont=tableList[ui->tabWidget->currentIndex()]->rowCount();
    tableList[ui->tabWidget->currentIndex()]->insertRow(RowCont);//增加一行
    for(int i=0;i<num;i++){
        QTableWidgetItem *item = new QTableWidgetItem;
        if(i!=1)
            item->setData(Qt::DisplayRole,data[i]);
        else
            item->setText(data[i]);
        tableList[ui->tabWidget->currentIndex()]->setItem(RowCont,i,item);
    }
}

void MainWindow::ReadData(QString FireName)
{
    QFile file(FireName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
     }
    QTextStream in(&file);
    ChangeSet(&in);
}

void MainWindow::ChangeSet(QTextStream *in)
{
    QString line = in->readLine();
    QStringList head,rex;
    while (!line.isNull()){
        QStringList data =  line.split(QRegExp("[;]"));
        switch(data[0].toInt()){
        case URL:
            urlName.append(data[1]);
            url.append(data[2]);
            pageNumber.append(data[3]);
            Data_Head.append(head);
            Data_Rex.append(rex);
            break;
        case HEAD:
            for(int k=1;k<data.length()-1;k++)
                Data_Head.back().append(data[k]);
            break;
        case Rex:
            for(int k=1;k<data.length()-1;k++)
                Data_Rex.back().append(data[k]);
            break;
        case DECODE:
            Decode.append(data[1]);
            break;
        case USER:
            UserAgeny.append(data[1]+";");
            for(int k=2;k<data.length()-1;k++){
                UserAgeny.back().append(data[k]+";");
            }
            UserAgeny.back() = UserAgeny.back().left(UserAgeny.back().length()-1);
            break;
        }
        line = in->readLine();
    }
}


void MainWindow::on_SpiderButton_clicked()
{
    userN=0;
    ui->pageButton->setDisabled(true);
    if(staus==TOSTART){
        Run_num = ui->tabWidget->currentIndex();
        ui->statusBar->showMessage(QString("开始访问%1").arg(urlName[Run_num]));
        All_page=pageNumber[ui->tabWidget->currentIndex()].toInt();
        Current_page = 1;
        Current_Data_Number=0;
        for(int i=tableList[Run_num]->rowCount()-1;i>-1;i--){
            tableList[Run_num]->removeRow(i);
        }
        ui->pageWidget->clear();

        getDataFromWeb();

        ui->SpiderButton->setText("停止爬虫");
        staus=TOSTOP;
    }
    else if(staus==TOSTOP){
        Current_page = All_page;
        staus=TOSTART;
        ui->SpiderButton->setText("爬虫");
        disconnect(reply);
        userN++;
        if(userN>=UserAgeny.length())
            userN=0;
        ui->SpiderButton->setDisabled(true);
        Delay_MSec(2500);

    }

}

void MainWindow::Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    ui->SpiderButton->setEnabled(true);
    ui->pageButton->setEnabled(true);
}

void MainWindow::getDataFromWeb()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QString url = QString(Current_url).arg(Current_page);
    QNetworkRequest *request=new QNetworkRequest(QUrl(url));

    QString userAg = UserAgeny[userN++];
    if(userN>=UserAgeny.length())
        userN=0;
    request->setHeader(QNetworkRequest::ContentTypeHeader,userAg);
    reply = manager->get(*request);
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(upLoadError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(uploadProcess(qint64, qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(slot_requestFinished()));

   // m_pTimer = new QTimer(this);
   // connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
   // m_pTimer->start(1000);

}



void MainWindow::upLoadError(QNetworkReply::NetworkError code)
{
    qDebug() << "错误： "<<code;
}

void MainWindow::uploadProcess(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << bytesReceived << bytesTotal;
}

void MainWindow::slot_requestFinished()
{
    ui->statusBar->showMessage(QString("访问%1成功").arg(urlName[Run_num]));
    QByteArray resultContent = reply->readAll();
    QTextCodec* pCodec = QTextCodec::codecForName(Decode[Run_num].toLatin1().data());
    QString strResult = pCodec->toUnicode(resultContent);
    int nHttpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
    qDebug()<<"状态码： "<<nHttpCode<<endl;
   // ui->SpiderButton->setEnabled(true);

    if(nHttpCode==200){
        QString data_Whole;//股票数据主体
        //正则表达式


        //先取数据主体
        QString pattern = Data_Rex[Run_num][0];
        QRegularExpression regularExpression(pattern);
        int index = 0;
        QRegularExpressionMatch match;
        match = regularExpression.match(strResult, index);
        if(match.hasMatch()) {
           index = match.capturedEnd();
           data_Whole = match.captured(0);
           qDebug()<<"("<<match.capturedStart() <<","<<index<<") ";
        }


        //再分段取数据 初始数据（包含空格）
        QStringList InitialData;
        pattern = Data_Rex[Run_num][1];
        regularExpression.setPattern(pattern);
        index = 0;
        do {
            match = regularExpression.match(data_Whole, index);
            if(match.hasMatch()) {
               index = match.capturedEnd();
               InitialData.append(match.captured(0));
            }
            else
               break;
        } while(index < strResult.length());

        QStringList LastData; //最终数据流
        for(int l=0;l<InitialData.length();l++){
            if(InitialData[l]!=tr("><")){
                LastData.append(InitialData[l].mid(1,InitialData[l].length()-2));
            }
        }

        QList<QStringList> StockList;//股票数据 12项数据
        int ind=0;
        for(int t=0;t<LastData.length()/12;t++){
            QStringList stock;
            for(int k=0;k<12;k++){
                stock.append(LastData[ind++]);
            }
            StockList.append(stock);
        }
        Current_Data_Number+=StockList.length();

        ui->statusBar->showMessage(QString("获取%1 第%2页").arg(urlName[Run_num]).arg(QString::number(Current_page)));
        for(int i=0;i<StockList.length();i++){
            AddItemWidget(StockList[i],Data_Head[Run_num].length());
        }

        if(StockList.length()>0){
            QListWidgetItem * item = new QListWidgetItem (QString("第 %1 页: %2股").arg(QString::number(Current_page)).arg(QString::number(StockList.length())));
            item->setTextColor(QColor(Qt::blue));
            ui->pageWidget->addItem(item);
        }else{
            QListWidgetItem * item = new QListWidgetItem (QString("第 %1 页: 不存在").arg(QString::number(Current_page)));
            item->setTextColor(QColor(Qt::red));
            ui->pageWidget->addItem(item);
        }


    }else{
        userN++;
        if(userN>=UserAgeny.length())
            userN=0;
        getDataFromWeb();
        return;
    }



    if(Current_page<All_page){
        Current_page++;
        getDataFromWeb();
    }else{
        staus=TOSTART;
        ui->SpiderButton->setText("爬虫");
        ui->statusBar->showMessage(QString("股票数据生成结束：%1(%2股）").arg(urlName[Run_num]).arg(QString::number(Current_Data_Number)));
        QListWidgetItem *item = new QListWidgetItem (QString("共 %1 股").arg(QString::number(Current_Data_Number)));
        ui->pageWidget->addItem(item);
        ui->SpiderButton->setEnabled(true);
        ui->pageButton->setEnabled(true);
    }


}



void MainWindow::on_tabWidget_currentChanged(int index)
{
    Current_url=url[index];
}



void MainWindow::on_FileOnlyButton_clicked()
{
    int index = ui->tabWidget->currentIndex();
    int row = tableList[index]->rowCount();
    int column = Data_Head[index].length();


    QString file_name = QFileDialog::getSaveFileName(NULL,"文件保存",".","*.csv");
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
      }
    QTextStream out(&file);
    out <<Data_Head[index].join(",")<<"\r";

    QStringList list;
    for (int i=0;i<row;i++){
        list.clear();
        for (int j=0;j<column;j++){
            list<<tableList[index]->item(i,j)->text();
        }
        out <<list.join(",")<<"\r";
    }
    file.close();
}

void MainWindow::on_FileWholeButton_clicked()
{
    int N = ui->tabWidget->count();
    QString file_name = QFileDialog::getSaveFileName(NULL,"文件保存",".","*.csv");
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
      }
    QTextStream out(&file);
    out <<Data_Head[0].join(",")<<"\r";

    for(int n=0;n<N;n++){
        int row = tableList[n]->rowCount();
        int column = Data_Head[n].length();

        QStringList list;
        for (int i=0;i<row;i++){
            list.clear();
            for (int j=0;j<column;j++){
                list<<tableList[n]->item(i,j)->text();
            }
            out <<list.join(",")<<"\r";
        }
    }
    file.close();
}

//检索
void MainWindow::on_SearchEdit_textEdited(const QString &arg1)
{
    int index = ui->tabWidget->currentIndex();
    int rC = tableList[index]->rowCount();
    if ("" == arg1)//判断输入是否为空
    {
        for (int i = 0; i < rC; i++)
        {
            tableList[index]->setRowHidden(i, false);//显示所有行
        }
    }
    else
    {
        //获取符合条件的cell索引
        QList <QTableWidgetItem *> item = tableList[index]->findItems(arg1, Qt::MatchContains);

        for (int i = 0; i < rC; i++)
        {
            tableList[index]->setRowHidden(i, true);//隐藏所有行
        }

        if (!item.isEmpty())//不为空
        {
            for (int i = 0; i < item.count(); i++)
            {
                tableList[index]->setRowHidden(item.at(i)->row(),false);//item.at(i).row()输出行号
            }
        }
    }
}

void MainWindow::on_pageButton_clicked()
{
    PageDialog Dialog(this,pageNumber);
    connect(&Dialog,SIGNAL(changePageNumber(QStringList)),this,SLOT(changePageNum(QStringList)));
    Dialog.exec();
}

void MainWindow::changePageNum(QStringList pn)
{
    pageNumber.clear();
    pageNumber.append(pn);
}


