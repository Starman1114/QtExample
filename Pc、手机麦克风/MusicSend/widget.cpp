#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    wt = new WorkerThread();
    wt->start();
    wt->pause.lock();
    mon = new Monitor();
    mon->start();
    mon->pause.lock();

    Init_Monitor();

    ui->textEdit->setText("communication");

    t[0]=0.000022675736961;
    for(int k=1;k<882;k++){
        t[k]=t[k-1]+0.000022675736961;
    }
    Downchirp(19500, 22000, t, 0.02,Down_chirp);
    Upchirp(19500, 22000,t, 0.02,Up_chirp);

    ui->horizontalSlider->setDisabled(true);

    //QAudioInput 生成的音频文件未经过处理，即文件保存的数据全部为音频数据，没有文件头，播放器识别不了
}

Widget::~Widget()
{
    delete ui;
}



void Widget::Init_Monitor()
{
    //初始路径
    QAndroidJniObject path =QAndroidJniObject::callStaticObjectMethod<jstring>(
            "org/qtproject/example/MainActivity", "path");
    route = path.toString()+"/MusicSend";
    QDir *temp = new QDir;
    bool exist = temp->exists(route);
    if(!exist){
       temp->mkdir(route);
    }else{
        temp->rmdir(route);
        temp->mkdir(route);
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





//void Widget::playBtnResponded()
//{
//    file->open(QIODevice::ReadOnly);
//    output->start(file);
//}

void Widget::on_monitorButton_clicked()
{
    if(flag_Monitor == MONITOR_START)
    {
        flag_Monitor = MONITOR_FINISH;
        wt->pause.unlock();
        mon->pause.unlock();
        ui->monitorButton->setText("停止监听");
    }else if(flag_Monitor == MONITOR_FINISH){
        flag_Monitor = MONITOR_START;
        wt->pause.lock();
        mon->pause.lock();
        ui->monitorButton->setText("监听");
    }
}

void Widget::on_sendBtn_clicked()
{
    txt=ui->textEdit->toPlainText();
    QByteArray  a = txt.toLatin1();
    binary = hexTobinary(a.toHex());
    ui->textBrowser->setText(binary);


    send_Data = new double[binary.length()*882];
    QString n;
    for(int k=0;k<binary.length();k++){
        n=binary.at(k);
        if(n==49){//1
            for(int j=0;j<882;j++){
               send_Data[k*882+j]=Up_chirp[j];
            }
        }else if(n==48){//0
            for(int j=0;j<882;j++){
               send_Data[k*882+j]=Down_chirp[j];
            }
        }
    }

   array.resize(binary.length()*882*sizeof(double));
   memcpy(array.data(),send_Data,binary.length()*882*sizeof(double));

   QFile *file2 = new QFile();
   file2->setFileName(route+"/monitor233.raw");
   bool exist = file2->exists();
   if(exist){
       file2->remove();
       QFile *file2 = new QFile();
       file2->setFileName(route+"/monitor233.raw");
   }
   file2->open(QIODevice::ReadWrite);
   QDataStream in(file2);
   in.setVersion(QDataStream::Qt_5_10);
   //in<<ba;
   in.writeRawData(array.data(),array.count()); //new
   file2->close();

   wt->addWavHeader(route+"/monitor233.raw" , route+"/monitor233.wav");

   QFile *file = new QFile();
   file->setFileName(route+"/monitor233.wav");
   file->open(QIODevice::ReadWrite);
   output_Monitor->start(file);

   ui->lineEdit->setText(QString::number(array.length())+" "+QString::number(array.length()/882/8/8));
   ui->horizontalSlider->setMaximum(array.length()-1);
   ui->horizontalSlider->setEnabled(true);




}

QString Widget::hexTobinary(QString tem)
{
    QString t;
    for(int k=0;k<tem.length();k++){
        QString n=tem.at(k);
        int num = n.toInt();
        if(n==97)
            num=10;
        else if(n==98)
            num=11;
        else if(n==99)
            num=12;
        else if(n==100)
            num=13;
        else if(n==101)
            num=14;
        else if(n==102)
            num=15;

        if(num>7){
            t.append("1");
            num=num-8;
        }else
            t.append("0");

        if(num>3){
            t.append("1");
            num=num-4;
        }else
            t.append("0");

        if(num>1){
            t.append("1");
            num=num-2;
        }else
            t.append("0");

        if(num==1){
            t.append("1");
        }else
            t.append("0");
    }
    return t;
}

QString Widget::binaryToString(QString binary)
{
    QString tem;
    QString result;
    QString n;
    int num1=0;
    for(int k=0;k<binary.length();k++){
        n=binary.at(k);
        switch(k%4){
        case 0:
            if(n==49) //1
                num1=num1+8;
            break;
        case 1:
            if(n==49) //1
                num1=num1+4;
            break;
        case 2:
            if(n==49) //1
                num1=num1+2;
            break;
        case 3:
            if(n==49) //1
                num1=num1+1;
            QString t;
            tem.append(t.setNum(num1,16));
            num1=0;
            break;
        }
    }
    int num2=0;
    for(int k=0;k<tem.length();k++){
        n=tem.at(k);
        switch(k%2){
        case 0:
            if(n==97)
                num2+=(10*16);
            else if(n==98)
                num2+=(11*16);
            else if(n==99)
                num2+=(12*16);
            else if(n==100)
                num2+=(13*16);
            else if(n==101)
                num2+=(14*16);
            else if(n==102)
                num2+=(15*16);
            else{
                num2+=n.toInt()*16;
            }
            break;
        case 1:
            if(n==97)
                num2+=10;
            else if(n==98)
                num2+=11;
            else if(n==99)
                num2+=12;
            else if(n==100)
                num2+=13;
            else if(n==101)
                num2+=14;
            else if(n==102)
                num2+=15;
            else{
                num2+=n.toInt();
            }
            result.append(num2);
            num2=0;
            break;
        }
    }
    return result;


}

void Widget::on_receiveButton_clicked()
{
   // txt=ui->textEdit->toPlainText();
   // QByteArray  a = txt.toLatin1();
   // QString tem =a.toHex();
   // ui->textBrowser->setText(hexTotwo(tem));
   //
   // binary.toLatin1()

    ui->textBrowser->append("\n"+binaryToString(binary));
}



void Widget::on_horizontalSlider_valueChanged(int value)
{
    ui->doubleSpinBox->setValue(array[value]);
}
