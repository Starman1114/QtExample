#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  connect(this,SIGNAL(close()),qApp,SLOT(quit()));//关闭窗口则退出程序
    InitStyle();

    menus = new QMenuBar();
    ui->menusLayout->setMenuBar(menus);

    C = new Chart();
    record1 = new Record();

    menuSetUp();  //菜单栏初始化
    dataSetUp();  //数据显示初始化
    ui->openButton->setDisabled(true);
    ui->stopButton->setDisabled(true);
    ui->recordButton->setDisabled(true);

    //子线程
    workerThread = new WorkerThread(this);
    dC = new dataChange(this);

    //系统时间更新
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    //图表增加
    f = new Function();
    connect(f, SIGNAL(ChartShowSend(FunctionD)), this, SLOT(ChartChangeShow(FunctionD)));
    fd = new FunctionData();
    //数据显示
    databox = new QGroupBox();
    databox->setTitle("数据显示");
    m = new MathW();

    ui->horizontalSlider->setDisabled(true);
    C->becomeOrigin(f_Recive,&m_series);
    f->startChartShow();

    initStyle();//加载样式表
    ui->timeSpaceBox->setToolTip("播放频率(ms)");
    ui->sampleRateBox->setToolTip("采样率(Hz)");
    ui->showCountBox->setToolTip("样本点显示数");

    setP = new SetPath();

    //计步
    cs=new CountStep();
   // connect(cs,SIGNAL(hide()),this,SLOT(csHide()));
}

MainWindow::~MainWindow()
{
    CloseCOMDevice();
    delete ui;
}

void MainWindow::menuSetUp()
{
    //菜单栏部分
    menu1=menus->addMenu("串口选择(&P)");
    QList<QAction*> port;
    //查找可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
       {
           QSerialPort serial;
           serial.setPort(info);
           if(serial.open(QIODevice::ReadWrite))
           {
               QAction *port1=new QAction(serial.portName(), this);
               port1->setCheckable(true);
               port.append(port1);
               serial.close();
           }
       }
    QAction *port11=new QAction("串口刷新", this);
    QObject::connect(port11, SIGNAL(triggered(bool)), this, SLOT(portFalsh(bool)));
    port.append(port11);
    menu1->addActions(port);
    QObject::connect(menu1, SIGNAL(triggered(QAction *)), this, SLOT(port_chooseport(QAction *)));

    QList<QAction*> baud;
    menu2=menus->addMenu("波特频率(&B)");
    for(int k=0;k<10;k++){
        long Baud=(k+1)*2400;
        QAction *port2=new QAction(QString::number(Baud, 10), this);
        port2->setCheckable(true);
        baud.append(port2);
    }
    menu2->addActions(baud);
    QObject::connect(menu2, SIGNAL(triggered(QAction *)), this, SLOT(port_choosebaud(QAction *)));

    menu3=menus->addMenu("设置(&S)");
    QList<QAction*> set;
    QAction *port31=new QAction("图表设置", this);
    QAction *port32=new QAction("打开文件目录", this);
    QAction *port33=new QAction("修改文件目录", this);
    QObject::connect(port31, SIGNAL(triggered(bool)), this, SLOT(ChartChange(bool)));
    QObject::connect(port32, SIGNAL(triggered(bool)), this, SLOT(OpenDir(bool)));
    QObject::connect(port33, SIGNAL(triggered(bool)), this, SLOT(SetDir(bool)));
    set.append(port31);
    set.append(port32);
    set.append(port33);
    menu3->addActions(set);

    menu4=menus->addMenu("功能扩展");
    QList<QAction*> count;
    QAction *port41=new QAction("计步", this);
    port41->setCheckable(true);
    QAction *port42=new QAction("步态检测", this);
    port42->setCheckable(true);

    QObject::connect(port41, SIGNAL(triggered(bool)), this, SLOT(countStepShow(bool)));
   // QObject::connect(port42, SIGNAL(triggered(bool)), this, SLOT(OpenDir(bool)));
    count.append(port41);
    count.append(port42);
    menu4->addActions(count);


}

void MainWindow::dataSetUp()
{
    //端口信息
    QHBoxLayout *vbox1 = new QHBoxLayout;
    QLabel *p1=new QLabel("Port: "+choosenport);
    Com.append(p1);
    QLabel *b1=new QLabel("Baud: "+choosenbaud);
    Com.append(b1);
    vbox1->addWidget(Com[0]);
    vbox1->addWidget(Com[1]);
    ui->portBox->setLayout(vbox1);

    //系统时间更新
    QLabel *systime=new QLabel("System Time:");
    Time.append(systime);
   // QLabel *boardtime=new QLabel("Board Time:");
   // Time.append(boardtime);
    QLabel *boardtime=new QLabel("Record Time:");
    Time.append(boardtime);
    QLabel *timesp=new QLabel("SampleRate: ");
    Time.append(timesp);
    QHBoxLayout *vbox2 = new QHBoxLayout;
    vbox2->addWidget(Time[0]);
    vbox2->addWidget(Time[1]);
    vbox2->addWidget(Time[2]);
    ui->timeBox->setLayout(vbox2);

}



//刷新串口
void MainWindow::portFalsh(bool ok)
{
    if(!ok){
        menu1->clear();
        QList<QAction*> port;
        //查找可用的串口
        foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
           {
               QSerialPort serial;
               serial.setPort(info);
               if(serial.open(QIODevice::ReadWrite))
               {
                   QAction *port1=new QAction(serial.portName(), this);
                   port1->setCheckable(true);
                   port.append(port1);
                   serial.close();
               }
           }
        QAction *port11=new QAction("串口刷新", this);
        QObject::connect(port11, SIGNAL(triggered(bool)), this, SLOT(portFalsh(bool)));
        port.append(port11);
        menu1->addActions(port);
    }

}


//串口选择
void MainWindow::port_chooseport(QAction *action)
{
    for(int k =0;k<menu1->actions().length();k++){
        if(menu1->actions()[k]->isChecked())
            menu1->actions()[k]->setChecked(false);
    }
    action->setChecked(true);
    choosenport= action->text();
    Com[0]->setText("Port: "+choosenport);

}
//波特率选择
void MainWindow::port_choosebaud(QAction *action)
{
    for(int k =0;k<menu2->actions().length();k++){
        if(menu2->actions()[k]->isChecked())
            menu2->actions()[k]->setChecked(false);
    }
    action->setChecked(true);

    choosenbaud= action->text();
    Com[1]->setText("Baud: "+choosenbaud);
    if(!show1)
        ui->openButton->setEnabled(true);
    ui->stopButton->setEnabled(true);
}

void MainWindow::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    //Time[0]->setText(time.toString("yyyy-MM-dd hh:mm:ss dddd")); //年-月-日 时-分-秒 星期
    Time[0]->setText("System Time: "+time.toString("yyyy-MM-dd hh:mm:ss"));

}

void MainWindow::on_openButton_clicked()
{

    QString c=choosenport.remove(0,3);
    ulComNo=c.toLong();
    ulBaund=choosenbaud.toLong();

    OpenCOMDevice(ulComNo,ulBaund);

    //线程结束后，自动销毁
   // connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));

    workerThread->start();
    dC->start();
    dC->pause.lock();
    ui->openButton->setDisabled(true);
    ui->recordButton->setEnabled(true);
    running =true;
    record1->clear(&dataStore1);

    //C->becomeOrigin(&m_series);

    originData();
}

void MainWindow::on_cleanButton_clicked()
{
    record1->clear(&dataStore1);
    C->becomeOrigin(f_Recive,&m_series);
    originData();
}

void MainWindow::on_stopButton_clicked()
{
    if(running){
        // 请求终止
        workerThread->pause.lock();
        ui->stopButton->setText("继续");
        running = false;
        ifstop=true;
    }else{
        workerThread->pause.unlock();
        ui->stopButton->setText("暂停");
        running = true;
        ifstop=false;
    }

}

void MainWindow::on_recordButton_clicked()
{
    if(!record){
       record=true;
       if(ifstop){
           ui->stopButton->clicked(true);
       }
       record1->clear(&dataStore1);
       dC->pause.unlock();
       ui->recordButton->setText("停止记录");
       ui->cleanButton->setDisabled(true);
       ui->stopButton->setDisabled(true);
       menu3->actions()[0]->setDisabled(true);
       ui->showButton->setDisabled(true);
       ui->sampleRateBox->setDisabled(true);

    }else{
        if(running){
            dC->pause.lock();
            workerThread->pause.lock();
            running = false;
            change =true;
        }
       QString file_name = QFileDialog::getSaveFileName(NULL,"记录文件保存",Path,"*.txt");
       QFile file(file_name);
       if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
           record=false;
           ui->recordButton->setText("记录");
           ui->cleanButton->setEnabled(true);
           ui->stopButton->setEnabled(true);
           menu3->actions()[0]->setEnabled(true);
           ui->showButton->setEnabled(true);
           ui->sampleRateBox->setEnabled(true);
           if(change){
               workerThread->pause.unlock();//继续
               change=false;
               running =true;
           }
           return;
         }
       dataStore1.SampleRate=SampleRate;
       QTextStream out(&file);
       out << "chartNumber;"<< QString::number(f_Recive.N) << ";"
           << "\n";
       for(int i=0;i<f_Recive.N;i++){
           out << f_Recive.name[i] << ";"
               << f_Recive.f[i].n << ";"
               << "\n";
           for(int j=0;j<f_Recive.f[i].n;j++){
               out << f_Recive.f[i].variaName[j] << ";"
                   << f_Recive.f[i].s[j] << ";"
                   << f_Recive.f[i].ymax[j] << ";"
                   << f_Recive.f[i].ymin[j] << ";"
                   << f_Recive.f[i].units[j] << ";"
                   << f_Recive.f[i].c[j] << ";"
                   << "\n";
           }
       }
       out << "length;"<< dataStore1.length << ";\t"
           << "SampleRate;" << QString::number(dataStore1.SampleRate)<< ";\t"
           << ";\n";
       for(int k=0;k<dataStore1.length;k++){
           out << dataStore1.sysTime[k] << ";";
           int count=0;
           for(int i=0;i<f_Recive.N;i++){
               for(int j=0;j<f_Recive.f[i].n;j++){
                   out << dataStore1.dataRecord[k].at(count) << ";";
                   count++;
               }
           }
           out << "\n";
       }
       file.close();
       record1->clear(&dataStore1);
       record=false;
       ui->recordButton->setText("记录");
       ui->cleanButton->setEnabled(true);
       ui->stopButton->setEnabled(true);
       menu3->actions()[0]->setEnabled(true);
       ui->showButton->setEnabled(true);
       ui->sampleRateBox->setEnabled(true);
       if(change){
           workerThread->pause.unlock();//继续
           change=false;
           running =true;
       }
    }
}


void MainWindow::on_showButton_clicked()
{
    if(!show1){
        if(running){
            workerThread->pause.lock();//先暂停
            running = false;
            forshow =true;
           }
        ui->cleanButton->setDisabled(true);
        ui->stopButton->setDisabled(true);
        ui->recordButton->setDisabled(true);
        menu3->actions()[0]->setDisabled(true);
        QString file_name = QFileDialog::getOpenFileName(NULL,"打开录制文件",Path,"*.txt"); //文件绝对路径
        //第一个参数parent，用于指定父组件。注意，很多Qt组件的构造函数都会有这么一个parent参数，并提供一个默认值0；
        //第二个参数caption，是对话框的标题；
        //第三个参数dir，是对话框显示时默认打开的目录，"." 代表程序运行目录，"/" 代表当前盘符的根目录(Windows，Linux下/就是根目录了)，也可以是平台相关的，比如"C:\\"等；
        //第四个参数filter，是对话框的后缀名过滤器；
        //多个文件使用空格分隔：比如我们使用"Image Files(*.jpg *.png)"就让它只能显示后缀名是jpg或者png的文件。
        //多个过滤使用两个分号分隔：如果需要使用多个过滤器，使用";;"分割，比如"JPEG Files(*.jpg);;PNG Files(*.png)"；
        //第五个参数selectedFilter，是默认选择的过滤器；
        //第六个参数options，是对话框的一些参数设定，比如只显示文件夹等等，它的取值是enum QFileDialog::Option，每个选项可以使用 | 运算组合起来。

        QFile file(file_name);
         if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
             ui->cleanButton->setEnabled(true);
             ui->stopButton->setEnabled(true);
             ui->recordButton->setEnabled(true);
             menu3->actions()[0]->setEnabled(true);
             if(forshow){
                 workerThread->pause.unlock();//继续
                 running =true;
                 forshow=false;
             }
             return;
         }

        QTextStream in(&file);
        fd->readData(&f_Tem,&in);
        //清除数据显示
        clearChartDataShow();
        //添加数据显示
        dataChartSetUp(f_Tem);
        //清除图表
        clearChart();
        for(int i=0;i<f_Tem.N;i++){
            //添加图表
            C->graphShowSetup(ui->tabWidget,f_Tem.name[i],&axisX,&axisY);
            C->setUp(chartView,chart,ui->tabWidget->widget(i),f_Tem.f[i],&m_series,&axisX,&axisY,i);
        }
        if(ui->tabWidget->count()>0)
            ui->tabWidget->setCurrentIndex(0);

        if(in.atEnd())
            return;
        QString line = in.readLine();
        QStringList data =  line.split(QRegExp("[;]"));
        QString l1 = data[1]; //长度
        QString s1 = data[3]; //SampleRate
        dataStore1.length=l1.toInt();
        dataStore1.SampleRate=s1.toInt();
        ui->timelabel->setText("SampleRate:"+s1);
        ui->maxlabel->setText("Length: "+l1);
        ui->horizontalSlider->setMaximum(dataStore1.length);  //这么写，release才不会报错。。。
        ui->horizontalSlider->setEnabled(true);
        runSlider=true;
        double st=dataStore1.length/dataStore1.SampleRate;
        ui->stimelabel->setText("sumTime:"+QString("%1").arg(st)+"s");

        while (!in.atEnd()) {
            line = in.readLine();
            data =  line.split(QRegExp("[;]"));//一个20，第一个为时间，最后一个为空
            data.pop_back();//最后一位为空
            record1->recordData_write(&dataStore1,data);
        }
        file.close();
        C->becomeOrigin(f_Tem,&m_series);
        QDateTime tt=QDateTime::fromString(dataStore1.sysTime[0], "yyyy-MM-dd hh:mm:ss.zzz");
        for(int k=0;k<axisX.length();k++){
             axisX[k]->setRange( tt.addMSecs(-maxSize/dataStore1.SampleRate*1000),tt);
        }
        show1=true;
        ui->showButton->setText("实时");
    }else{
        ui->cleanButton->setEnabled(true);
        ui->stopButton->setEnabled(true);
        ui->recordButton->setEnabled(true);
        menu3->actions()[0]->setEnabled(true);
        show1=false;
        runSlider=false;
        ui->showButton->setText("演示");
        record1->clear(&dataStore1);
        fd->clear(&f_Tem);
        //清除数据显示
        clearChartDataShow();
        //添加数据显示
        dataChartSetUp(f_Recive);
        //清除图表
        clearChart();
        for(int i=0;i<f_Recive.N;i++){
            //添加图表
            C->graphShowSetup(ui->tabWidget,f_Recive.name[i],&axisX,&axisY);
            C->setUp(chartView,chart,ui->tabWidget->widget(i),f_Recive.f[i],&m_series,&axisX,&axisY,i);
        }
        if(ui->tabWidget->count()>0)
            ui->tabWidget->setCurrentIndex(0);

        C->becomeOrigin(f_Recive,&m_series);
        ui->horizontalSlider->setDisabled(true);
        ui->horizontalSlider->setRange(1,99);//滚轴长度设置
        ui->maxlabel->setText("Length: ");
        ui->timelabel->setText("SampleRate: ");
        ui->stimelabel->setText("sumTime:");
        ui->horizontalSlider->setValue(1);//滚轴初始值设置
        if(forshow){
            workerThread->pause.unlock();//继续
            running =true;
            forshow=false;
        }
        originData();
    }
}

void MainWindow::originData()
{
    Time[1]->setText("Recorded Time: ");
    Time[2]->setText("SampleRate: ");
}

void MainWindow::dataSlider(dataStore dataStore1,int value)
{

    Time[1]->setText("Recorded Time: "+dataStore1.sysTime[value-1]);
    Time[2]->setText("SampleRate: "+QString::number(dataStore1.SampleRate));
    int count=0;
    for(int i=0;i<f_Tem.N;i++){
        for(int j=0;j<f_Tem.f[i].n;j++){
            dataListShow[count]->setText(f_Tem.f[i].variaName[j]+": "+dataStore1.dataRecord[value-1].at(count)+f_Tem.f[i].units[j]);
            count++;
        }
    }

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->lineEdit->setText(QString::number(value));
    if(runSlider){
        C->SliderData(&m_series,value,dataStore1,&axisX,f_Tem);
        dataSlider(dataStore1,value);
    }
   // m_pLabelSliderNum->setText(QString::number(value));
   // m_pLabelSliderNum->show();
   // int nSliderWidth = ui->horizontalSlider->width();//这里需要比较刻度条的实际长度，不然会出现问题
   // m_pLabelSliderNum->move(ui->horizontalSlider->x() + ui->horizontalSlider->sliderPosition()*nSliderWidth/ui->horizontalSlider->maximum() - m_pLabelSliderNum->width()/4*3,
   //                          ui->horizontalSlider->y() + ui->horizontalSlider->height());

}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->horizontalSlider->setValue(arg1.toInt());
}


void MainWindow::on_timeSpaceBox_editingFinished()
{
    if(running){
        workerThread->pause.lock();//先暂停
        timeSpace=ui->timeSpaceBox->value();
        workerThread->pause.unlock();//先暂停

    }else{
        timeSpace=ui->timeSpaceBox->value();
    }
    C->becomeOrigin(f_Recive,&m_series);
}

void MainWindow::on_timeSpaceBox_valueChanged(int arg1)
{
    if(arg1<100)
        arg1=100;
    if(arg1>1000)
        arg1=1000;
    int arg=arg1-arg1%100;
    if(running){
        workerThread->pause.lock();//先暂停
        timeSpace=arg;
        workerThread->pause.unlock();//先暂停
    }else{
        timeSpace=arg;
    }
    C->becomeOrigin(f_Recive,&m_series);
    ui->timeSpaceBox->setValue(arg);
}



void MainWindow::on_sampleRateBox_editingFinished()
{
    SampleRate=ui->sampleRateBox->value();
}

void MainWindow::on_sampleRateBox_valueChanged(int arg1)
{
    SampleRate=ui->sampleRateBox->value();
}

void MainWindow::on_showCountBox_editingFinished()
{
    if(running){
        workerThread->pause.lock();//先暂停
        maxSize=ui->showCountBox->value();
        //清除图表
        clearChart();
        for(int i=0;i<f_Recive.N;i++){
            //添加图表
            C->graphShowSetup(ui->tabWidget,f_Recive.name[i],&axisX,&axisY);
            C->setUp(chartView,chart,ui->tabWidget->widget(i),f_Recive.f[i],&m_series,&axisX,&axisY,i);
        }
        C->becomeOrigin(f_Recive,&m_series);
        workerThread->pause.unlock();//先暂停

    }else{
        maxSize=ui->showCountBox->value();
        //清除图表
        clearChart();
        for(int i=0;i<f_Recive.N;i++){
            //添加图表
            C->graphShowSetup(ui->tabWidget,f_Recive.name[i],&axisX,&axisY);
            C->setUp(chartView,chart,ui->tabWidget->widget(i),f_Recive.f[i],&m_series,&axisX,&axisY,i);
        }
        C->becomeOrigin(f_Recive,&m_series);
    }
}

void MainWindow::on_showCountBox_valueChanged(int arg1)
{
    if(running){
        workerThread->pause.lock();//先暂停
        maxSize=arg1;
        //清除图表
        clearChart();
        for(int i=0;i<f_Recive.N;i++){
            //添加图表
            C->graphShowSetup(ui->tabWidget,f_Recive.name[i],&axisX,&axisY);
            C->setUp(chartView,chart,ui->tabWidget->widget(i),f_Recive.f[i],&m_series,&axisX,&axisY,i);
        }
        C->becomeOrigin(f_Recive,&m_series);
        ui->showCountBox->setValue(arg1);

        workerThread->pause.unlock();//先暂停
    }else{
        maxSize=arg1;
        //清除图表
        clearChart();
        for(int i=0;i<f_Recive.N;i++){
            //添加图表
            C->graphShowSetup(ui->tabWidget,f_Recive.name[i],&axisX,&axisY);
            C->setUp(chartView,chart,ui->tabWidget->widget(i),f_Recive.f[i],&m_series,&axisX,&axisY,i);
        }
        C->becomeOrigin(f_Recive,&m_series);
        ui->showCountBox->setValue(arg1);
    }
}




void MainWindow::ChartChangeShow(FunctionD f_Send)
{
    if(running){
        workerThread->pause.lock();
        running = false;
        change =true;
    }
    f_Recive=f_Send;
    //清除数据显示
    clearChartDataShow();
    //添加数据显示
    dataChartSetUp(f_Recive);
    //清除图表
    clearChart();
    for(int i=0;i<f_Recive.N;i++){
        //添加图表
        C->graphShowSetup(ui->tabWidget,f_Recive.name[i],&axisX,&axisY);
        C->setUp(chartView,chart,ui->tabWidget->widget(i),f_Recive.f[i],&m_series,&axisX,&axisY,i);
    }
    C->becomeOrigin(f_Recive,&m_series);

    if(ui->tabWidget->count()>0)
        ui->tabWidget->setCurrentIndex(0);

    if(change){
        workerThread->pause.unlock();//继续
        change=false;
        running =true;
    }
}

void MainWindow::dataChartSetUp(FunctionD f)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    for(int i=0;i<f.N;i++){
        QHBoxLayout *vbox1 = new QHBoxLayout;
        for(int j=0;j<f.f[i].n;j++){
            QLabel *l=new QLabel(f.f[i].variaName[j]+":");
            dataListShow.append(l);
            vbox1->addWidget(dataListShow[Lable_count]);
            Lable_count++;
        }
        vbox->addLayout(vbox1);
    }
    databox->setLayout(vbox);
}


void MainWindow::clearChart()
{
    ui->tabWidget->clear();
    axisX.clear();
    axisY.clear();
    m_series.clear();
}

void MainWindow::clearChartDataShow()
{
    delete databox;
    //数据显示
    databox = new QGroupBox();
    databox->setTitle("数据显示");
    dataListShow.clear();
    Lable_count=0;
}

void MainWindow::on_dataButton_clicked()
{
    databox->show();
}


void MainWindow::initStyle()
{
    //加载样式表
    QFile file(":/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void MainWindow::initTranslator()
{
    //加载鼠标右键菜单翻译文件
    QTranslator *translator1 = new QTranslator(qApp);
    translator1->load(":/image/qt_zh_CN.qm");
    qApp->installTranslator(translator1);

    //加载富文本框鼠标右键菜单翻译文件
    QTranslator *translator2 = new QTranslator(qApp);
    translator2->load(":/image/widgets.qm");
    qApp->installTranslator(translator2);
}

void MainWindow::ChartChange(bool ok)
{
    if(!ok)
      f->show();

}

void MainWindow::OpenDir(bool ok)
{
    if(!ok){
        QDesktopServices::openUrl(QUrl(Path));
    }
}

void MainWindow::SetDir(bool ok)
{
    if(!ok){
        setP->show();
    }
}

void MainWindow::countStepShow(bool ok)
{
    if(ok){
        csRun=true;
        cs->show();
    }else{
        csRun=false;
        cs->hide();
    }
}

void MainWindow::csHide()
{
    csRun=false;
    menu4->actions()[0]->setChecked(false);
}


void MainWindow::InitStyle()
{
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    location = this->geometry();
    max = false;
    mousePressed = false;

   //安装事件监听器,让标题栏识别鼠标双击
   ui->lab_Title->installEventFilter(this);

   IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
   IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);
   IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
   IconHelper::Instance()->SetIcon(ui->btnMenu, QChar(0xf0c9), 10);
   IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015), 12);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        this->on_btnMenu_Max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton) && !max) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void MainWindow::on_btnMenu_Close_clicked()
{
    qApp->exit();
}

void MainWindow::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
        IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);
        ui->btnMenu_Max->setToolTip("最大化");
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf079), 10);
        ui->btnMenu_Max->setToolTip("还原");
    }
    max = !max;
}

void MainWindow::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}
