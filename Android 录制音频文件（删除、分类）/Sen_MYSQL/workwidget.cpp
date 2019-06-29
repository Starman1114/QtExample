#include "workwidget.h"
#include "ui_workwidget.h"

WorkWidget::WorkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkWidget)
{
    ui->setupUi(this);
    InitStyle();
}

WorkWidget::~WorkWidget()
{
    delete ui;
}


void WorkWidget::InitStyle(){

    height = 30;
    weight =50;
    SetIcon(ui->recordButton, QString("5s录音"), "Microsoft YaHei", height,weight);
    SetIcon(ui->trashButton, QChar(0xf014), "Microsoft YaHei", height,weight);

    //语句框设置
    QFont font2("Microsoft YaHei", 20, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗
    ui->textBrowser->setFont(font2);
    ui->textBrowser->setText("按录音记录5秒的演讲，大数据中心的服务器会给出一个初步分析，也希望您给出一个反馈。");
    ui->textBrowser->setDisabled(true);//设置不可编辑

    QFont font3("Microsoft YaHei", 20, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗
    ui->fieldWidget->setFont(font3);

    //生成文件的列表
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
                 qDebug()<<curFile.fileName()<<endl;
                 QStringList sections = curFile.fileName().split(QRegExp("[.]"));
                 if(sections[1]=="wav"){
                     FileName.append(curFile.fileName());
                     QListWidgetItem *item = new QListWidgetItem (curFile.fileName());
                     ui->fieldWidget->addItem(item);

                 //   QListWidgetItem * item1 = new QListWidgetItem ();
                 //   QCheckBox * box = new QCheckBox (name);
                 //   box->setCheckable ( true);
                 //   CheckList.append(box);
                 //   connect(CheckList.back(), SIGNAL(stateChanged(int)), this, SLOT(change_Check_State(int)));
                 //   widget->addItem( item );
                 //   widget->setItemWidget( item,box );
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

void WorkWidget::SetIcon(QPushButton* btn, QString c, QString family,int size, int weight)
{
    QFont font1(family, size, weight);
    btn->setFont(font1);
    btn->setText(c);
}

/**************************************************************************
    * 文件处理
    */
//文件生成处理
void WorkWidget::File_Gain()
{
    input_Monitor->stop();
    file_Monitor->close();

    // 将生成的.raw文件转成.wav格式文件;
    QStringList name =  file_Monitor->fileName().split(QRegExp("[.]"));
    addWavHeader(name[0]+".raw", name[0]+".wav");

    QStringList nameList =  name[0].split(QRegExp("[/]"));
    ChoosenSen dialog(this);
    if (dialog.exec() != QDialog::Accepted){ //如果不是accepted，则返回
        QFile fileRaw(name[0]+".raw");
        if (fileRaw.exists())
        {
            fileRaw.remove();
        }
        QFile fileWav(name[0]+".wav");
        if (fileWav.exists())
        {
            fileWav.remove();
        }
        return;
    }else{
        QFile file1(name[0]+".wav");
        QString nn =QString("%1%2").arg(PreEmotion).arg(nameList[nameList.length()-1]);
        FileName.append(nn+".wav");
        bool ok = file1.rename(QString("%1/%2.wav").arg(route).arg(nn));

        QFile file2(name[0]+".raw");
        bool ok2 = file2.rename(QString("%1/%2.raw").arg(route).arg(nn));

    }
    QListWidgetItem * item = new QListWidgetItem (FileName.back());
    ui->fieldWidget->addItem(item);

}

void WorkWidget::on_fieldWidget_itemDoubleClicked(QListWidgetItem *item)
{
    file_Monitor = new QFile();
    file_Monitor->setFileName(QString("%1/%2").arg(route).arg(item->text()));
    bool isOpen = file_Monitor->open(QIODevice::ReadOnly);
    if(!isOpen)
    {
        QMessageBox::about(NULL, "About", "打开文件失败");
        return;
    }
    output_Monitor->start(file_Monitor);
    CountShow dialog(this);
    dialog.exec();
}


void WorkWidget::File_Start()
{
    //重新开始录制
    file_Monitor = new QFile();
    QString dataTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    file_Monitor->setFileName(QString("%1/%2.raw").arg(route).arg(dataTime));
    bool isOpen = file_Monitor->open(QIODevice::WriteOnly | QIODevice::Truncate);
    if(!isOpen)
    {
        QMessageBox::about(NULL, "About", "打开文件失败");
        return;
    }
    input_Monitor->start(file_Monitor);

}

void WorkWidget::on_recordButton_clicked()
{
    File_Start();

    CountShow dialog(this);
    if (dialog.exec() == QDialog::Accepted) //如果不是accepted，则返回
        File_Gain();
}


// 将生成的.raw文件转成.wav格式文件;
qint64 WorkWidget::addWavHeader(QString catheFileName , QString wavFileName)
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


void WorkWidget::on_trashButton_clicked()
{
    TrashDialog dialog(this);
    dialog.resize(ui->fieldWidget->width()/10*8,ui->fieldWidget->height()*2);
    if (dialog.exec() == QDialog::Accepted){//如果不是accepted，则返回
        FrenshList();
    }


}

void WorkWidget::FrenshList()
{
    ui->fieldWidget->clear();
    for(int i =0 ;i<FileName.length();i++){
        QListWidgetItem * item = new QListWidgetItem (FileName.at(i));
        ui->fieldWidget->addItem(item);
    }
}
