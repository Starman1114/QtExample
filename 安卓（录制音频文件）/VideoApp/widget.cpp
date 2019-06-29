#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Init_Monitor();
    //QAudioInput 生成的音频文件未经过处理，即文件保存的数据全部为音频数据，没有文件头，播放器识别不了
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onTimeOut()
{
    // 获取系统当前时间
    //QString dataTime = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    count_Number++;
    countTime =countTime.addMSecs(1000);
    QString dataTime = countTime.toString("mm:ss");
    // 显示的内容
    m_pLCD->display(dataTime);

    if(count_Number>=time_Length){
        pTimer->stop();
        File_Gain();
        File_Start();
        pTimer->start();
    }

}

//文件生成处理
void Widget::File_Gain()
{
    input_Monitor->stop();
    file_Monitor->close();

    // 将生成的.raw文件转成.wav格式文件;
    MonitorName.append(route+"/video"+QString::number(count++));
    addWavHeader(MonitorName.back()+".raw", MonitorName.back()+".wav");

    int List_count = model->stringList().length();
    model->insertRows(List_count, 1);
    QModelIndex index = model->index(List_count); //图表下标
    QString dataTime = countTime.toString("mm:ss");
    // 显示的内容
    model->setData(index, QString("video%1  %2").arg(count-1).arg(dataTime));

    countTime.setTime(QTime(0, 0, 0, 0));
    count_Number=0;

}

void Widget::File_Start()
{
    //重新开始录制
    file_Monitor = new QFile();
    file_Monitor->setFileName(route+"/video"+QString::number(count)+".raw");
    bool isOpen = file_Monitor->open(QIODevice::WriteOnly | QIODevice::Truncate);
    if(!isOpen)
    {
        qDebug() << "打开文件失败";
        return;
    }
    input_Monitor->start(file_Monitor);
}

void Widget::on_recordButton_clicked()
{
    // 启动定时器
    if(pTimer->isActive()){
        pTimer->stop();
    }


    if(flag_Monitor == MONITOR_START)
    {
        message->showMessage("录制中......");
        flag_Monitor = MONITOR_FINISH;
        ui->recordButton->setText("停止录制");

        File_Start();
        pTimer->start();

     }else if(flag_Monitor == MONITOR_FINISH){
         message->showMessage("停止录制");
         flag_Monitor = MONITOR_START;
         ui->recordButton->setText("录制");

         pTimer->stop();
         File_Gain();
     }
}





void Widget::Init_Monitor()
{
    //状态栏
    message = new QStatusBar();
    this->layout()->addWidget(message);

    //计时表
    m_pLCD = new QLCDNumber(this);
    m_pLCD->setDigitCount(5); // 设置能显示的位数
    m_pLCD->setMode(QLCDNumber::Dec); // 设置显示的模式为十进制
    m_pLCD->setSegmentStyle(QLCDNumber::Flat); // 设置显示外观
    m_pLCD->setStyleSheet("border: 1px solid blue; color: white; background: black;");// 设置样式
    m_pLCD->display("00:00");
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(m_pLCD);
    ui->timeWidget->setLayout(vbox);
    countTime = QDateTime::currentDateTime();
    countTime.setTime(QTime(0, 0, 0, 0));

    //定时器设置
    pTimer = new QTimer(this);
    // 设置定时间隔
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));



    //APP图像用jpg格式就好
    //route =qApp->applicationDirPath()+"/VideoAPP"; //PC端测试
    //初始路径
    QAndroidJniObject path =QAndroidJniObject::callStaticObjectMethod<jstring>(
            "org/qtproject/example/MainActivity", "path");
    route = path.toString()+"/VideoAPP";

    QDir *temp = new QDir;
    bool exist = temp->exists(route);
    if(!exist){
       temp->mkdir(route);
    }else{
        temp->rmdir(route);
        temp->mkdir(route);
    }

    ui->lineEdit->setText(QString("文件存储路径: %1").arg(route));
    ui->lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit->setDisabled(true);//设置不可编辑
    //生成文件的列表
    model = new QStringListModel(this);
    ui->fileList->setModel(model);
    ui->fileList->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑

    QDir dir(route);
    QFileInfoList fileList;
    QFileInfo curFile;
    if(!dir.exists())  {return;}//文件不存，则返回false
    fileList=dir.entryInfoList(QDir::Dirs|QDir::Files
                               |QDir::Readable|QDir::Writable
                               |QDir::Hidden|QDir::NoDotAndDotDot
                               ,QDir::Name);
    if(fileList.size()>0){
         int infoNum=fileList.size();
         for(int i=0;i<infoNum;i++){
             curFile=fileList[i];
             if(curFile.isFile())
             {
                 QStringList sections = curFile.fileName().split(QRegExp("[.]"));
                 if(sections[1]=="wav"){
                     model->insertRows(count-1, 1);
                     QModelIndex index = model->index(count-1); //图表下标
                     model->setData(index, QString("%1").arg(sections[0]));
                     count++;
                 }
             }
         }
     }




    // 设置音频文件格式; 8888
    format_Monitor.setSampleRate(SampleRate);// 设置采样频率;
    format_Monitor.setChannelCount(ChannelCount);// 设置通道数;
    format_Monitor.setSampleSize(SampleSize);// 设置每次采样得到的样本数据位值;
    format_Monitor.setCodec("audio/pcm");// 设置编码方法;
    format_Monitor.setByteOrder(QAudioFormat::LittleEndian);// 设置采样字节存储顺序;
    format_Monitor.setSampleType(QAudioFormat::UnSignedInt);// 设置采样类型;

    // 判断本地设备是否支持该格式
    QAudioDeviceInfo infoIn(QAudioDeviceInfo::defaultInputDevice());
    if (!infoIn.isFormatSupported(format_Monitor))
    {
        //Default format not supported - trying to use nearest
        format_Monitor = infoIn.nearestFormat(format_Monitor);
    }

    QAudioDeviceInfo infoOut(QAudioDeviceInfo::defaultOutputDevice());
    if (!infoOut.isFormatSupported(format_Monitor))
    {
        //Default format not supported - trying to use nearest
        format_Monitor = infoOut.nearestFormat(format_Monitor);
    }


    QAudioDeviceInfo inputDevice(QAudioDeviceInfo::defaultInputDevice());
    input_Monitor = new QAudioInput(inputDevice, format_Monitor, this);
    QAudioDeviceInfo outputDevice(QAudioDeviceInfo::defaultOutputDevice());
    output_Monitor = new QAudioOutput(outputDevice, format_Monitor, this);
}


// 将生成的.raw文件转成.wav格式文件;
qint64 Widget::addWavHeader(QString catheFileName , QString wavFileName)
{
    // 开始准备WAV的文件头
    // 这里具体的数据代表什么含义请看上一篇文章（Qt之WAV文件解析）中对wav文件头的介绍
    WAVFILEHEADER WavFileHeader;
    qstrcpy(WavFileHeader.RiffName, "RIFF");
    qstrcpy(WavFileHeader.WavName, "WAVE");
    qstrcpy(WavFileHeader.FmtName, "fmt ");//要加一个空格以满足4个字节

    WavFileHeader.nFmtLength = 16;  //  表示 FMT 的长度
    WavFileHeader.nAudioFormat = 1; //这个表示 PCM 编码;

    qstrcpy(WavFileHeader.DATANAME, "data");

    WavFileHeader.nBitsPerSample =SampleSize;
    WavFileHeader.nBytesPerSample = ChannelCount*SampleSize/8; // 通道数×每次采样得到的样本数据位值／8
    WavFileHeader.nSampleRate = SampleRate;
    WavFileHeader.nBytesPerSecond = SampleRate*ChannelCount*SampleSize/8; //采样频率 × 音频通道数 × 每次采样得到的样本位数 / 8
    WavFileHeader.nChannleNumber = ChannelCount;

    QFile cacheFile(catheFileName);
    QFile wavFile(wavFileName);

    if (!cacheFile.open(QIODevice::ReadWrite))
    {
        return -1;
    }
    if (!wavFile.open(QIODevice::WriteOnly))
    {
        return -2;
    }

    int nSize = sizeof(WavFileHeader);
    qint64 nFileLen = cacheFile.bytesAvailable();

    WavFileHeader.nRiffLength = nFileLen - 8 + nSize;
    WavFileHeader.nDataLength = nFileLen;

    // 先将wav文件头信息写入，再将音频数据写入;
    wavFile.write((char *)&WavFileHeader, nSize);
    wavFile.write(cacheFile.readAll());

    cacheFile.close();
    wavFile.close();

    return nFileLen;
}



void Widget::on_timeBox_valueChanged(int arg1)
{
    time_Length = arg1;
}

void Widget::on_clearButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "音频处理", "确认清空?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QDir dir(route);
        QFileInfoList fileList;
        QFileInfo curFile;
        if(!dir.exists())  {return;}//文件不存，则返回false
        fileList=dir.entryInfoList(QDir::Dirs|QDir::Files
                                   |QDir::Readable|QDir::Writable
                                   |QDir::Hidden|QDir::NoDotAndDotDot
                                   ,QDir::Name);
        while(fileList.size()>0)
        {
            int infoNum=fileList.size();
            for(int i=infoNum-1;i>=0;i--){
                curFile=fileList[i];
                if(curFile.isFile())//如果是文件，删除文件
                {
                    QFile fileTemp(curFile.filePath());
                    fileTemp.remove();
                    fileList.removeAt(i);
                }
            }
        }
        for(int i=model->stringList().length()-1;i>=0;i--){
            model->removeRows(i, 1);
        }
        message->showMessage("文件已清空");
        count=1;
    }
    else{

    }
}
