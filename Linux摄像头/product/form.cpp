#include "form.h"
#include "ui_form.h"
#include <QDebug>
#include <QTime>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
  //  setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
  //  hide();
   // this->setParent(parent);

    connect(&myProcess, SIGNAL(readyRead()), this, SLOT(showResult()));
    connect(&myProcess, SIGNAL(stateChanged(QProcess::ProcessState)),
        this, SLOT(showState(QProcess::ProcessState)));
    connect(&myProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(showError()));
    connect(&myProcess, SIGNAL(finished(int,QProcess::ExitStatus)),
        this, SLOT(showFinished(int, QProcess::ExitStatus)));




}

Form::~Form()
{
    delete ui;
}



void Form::on_spinBox_valueChanged(int arg1) //brightness
{
    ui->horizontalSlider->setValue(arg1);
    num=1;
    math=arg1;

}

void Form::on_horizontalSlider_valueChanged(int value)  //brightness
{
     ui->spinBox->setValue(value);
     num=1;
     math=value;
     run();
}

void Form::on_horizontalSlider_2_valueChanged(int value) //contrast
{
     ui->spinBox_2->setValue(value);
     num=2;
     math=value;
     run();
}

void Form::on_spinBox_2_valueChanged(int arg1)  //contrast
{
    ui->horizontalSlider_2->setValue(arg1);
    num=2;
    math=arg1;

}

void Form::on_spinBox_3_valueChanged(int arg1) //saturation
{
    ui->horizontalSlider_3->setValue(arg1);
    num=3;
    math=arg1;

}

void Form::on_horizontalSlider_3_valueChanged(int value) //saturation
{
    ui->spinBox_3->setValue(value);
    num=3;
    math=value;
    run();
}

void Form::on_spinBox_4_valueChanged(int arg1) //gain
{
    ui->horizontalSlider_4->setValue(arg1);
    num=4;
    math=arg1;

}

void Form::on_horizontalSlider_4_valueChanged(int value) //gain
{
   ui->spinBox_4->setValue(value);
   num=4;
   math=value;
   run();
}

void Form::on_spinBox_5_valueChanged(int arg1) //power_line_frequency
{
    ui->horizontalSlider_5->setValue(arg1);
    num=5;
    math=arg1;

}

void Form::on_horizontalSlider_5_valueChanged(int value) //power_line_frequency
{
    ui->spinBox_5->setValue(value);
    num=5;
    math=value;
    run();
}

void Form::on_spinBox_6_valueChanged(int arg1) //white_balance_temperature
{
     ui->horizontalSlider_6->setValue(arg1);
     num=6;
     math=arg1;

}

void Form::on_horizontalSlider_6_valueChanged(int value) //white_balance_temperature
{
    ui->spinBox_6->setValue(value);
    num=6;
    math=value;
    run();
}

void Form::on_spinBox_7_valueChanged(int arg1) //sharpness
{
    ui->horizontalSlider_7->setValue(arg1);
    num=7;
    math=arg1;

}

void Form::on_horizontalSlider_7_valueChanged(int value) //sharpness
{
    ui->spinBox_7->setValue(value);
    num=7;
    math=value;
    run();
}

void Form::on_spinBox_8_valueChanged(int arg1) //backlight_compensation
{
    ui->horizontalSlider_8->setValue(arg1);
    num=8;
    math=arg1;

}

void Form::on_horizontalSlider_8_valueChanged(int value) //backlight_compensation
{
    ui->spinBox_8->setValue(value);
    num=8;
    math=value;
    run();
}

void Form::on_spinBox_9_valueChanged(int arg1) //exposure_auto
{
    ui->horizontalSlider_9->setValue(arg1);
    num=9;
    math=arg1;

}

void Form::on_horizontalSlider_9_valueChanged(int value) //exposure_auto
{
    ui->spinBox_9->setValue(value);
    num=9;
    math=value;
    run();
}

void Form::on_spinBox_10_valueChanged(int arg1) //exposure_absolute
{
    ui->horizontalSlider_10->setValue(arg1);
    num=10;
    math=arg1;

}

void Form::on_horizontalSlider_10_valueChanged(int value) //exposure_absolute
{
    ui->spinBox_10->setValue(value);
    num=10;
    math=value;
    run();
}

void Form::on_spinBox_11_valueChanged(int arg1) //pan_absolute
{
    ui->horizontalSlider_11->setValue(arg1);
    num=11;
    math=arg1;

}

void Form::on_horizontalSlider_11_valueChanged(int value) //pan_absolute
{
    ui->spinBox_11->setValue(value);
    num=11;
    math=value;
    run();
}

void Form::on_spinBox_12_valueChanged(int arg1) //tilt_absolute
{
    ui->horizontalSlider_12->setValue(arg1);
    num=12;
    math=arg1;

}

void Form::on_horizontalSlider_12_valueChanged(int value) //tilt_absolute
{
    ui->spinBox_12->setValue(value);
    num=12;
    math=value;
    run();
}

void Form::on_spinBox_13_valueChanged(int arg1) //focus_absolute
{
    ui->horizontalSlider_13->setValue(arg1);
    num=13;
    math=arg1;

}

void Form::on_horizontalSlider_13_valueChanged(int value) //focus_absolute
{
     ui->spinBox_13->setValue(value);
     num=13;
     math=value;
     run();
}

void Form::on_spinBox_14_valueChanged(int arg1) //zoom_absolute
{
     ui->horizontalSlider_14->setValue(arg1);
     num=14;
     math=arg1;

}

void Form::on_horizontalSlider_14_valueChanged(int value) //zoom_absolute
{
    ui->spinBox_14->setValue(value);
    num=14;
    math=value;
    run();
}


void Form::on_pushButton_clicked()
{
#if 1
    QString cmd = ui->lineEdit->text();
    myProcess.start(cmd);
#else
    QString program="ls";
    QStringList arguments;
    arguments << "/home/linux/python";

    myProcess.start(program,arguments);
    //myProcess.startDetached() /* 启动外部程序不随主程序的退出而退出 */
#endif
    // 等待进程启动
    if (!myProcess.waitForStarted())
    {
        qDebug() << "启动失败\n";
        return;
    }
    myProcess.closeWriteChannel();


}

void Form::showResult()
{
    //qDebug() << "shiwResult:" << endl << QString(myProcess.readAll());
    procOutput = myProcess.readAll();
    ui->textBrowser_2->setText(procOutput);
}

void Form::showState(QProcess::ProcessState state)
{
    qDebug() << "showState:";

    if(state==QProcess::NotRunning){
        qDebug() << "Not Running";
    }else if(state==QProcess::Starting){
        qDebug() << "Starting";;
    }else{
        qDebug() << "Running";
    }
}

void Form::showError()
{
    qDebug() << "showError:" << endl <<myProcess.errorString();
}

void Form::showFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "showFinished:" << endl << exitCode << exitStatus;
    //procOutput = myProcess.readAll(); /* 读取标准输出数据 */
    // qDebug() << procOutput << endl;
}

void Form::run()
{
   run1();
   sleep(100);

}

void Form::run1()
{
    QString cmd = "v4l2-ctl --set-ctrl=";
    switch(num){
    case 1: set="brightness";
    break;
    case 2: set="contrast";
    break;
    case 3: set="saturation";
    break;
    case 4: set="gain";
    break;
    case 5: set="power_line_frequency";
    break;
    case 6: set="white_balance_temperature";
    break;
    case 7: set="sharpness";
    break;
    case 8: set="backlight_compensation";
    break;
    case 9: set="exposure_auto";
    break;
    case 10: set="exposure_absolute";
    break;
    case 11: set="pan_absolute";
    break;
    case 12: set="tilt_absolute";
    break;
    case 13: set="focus_absolute";
    break;
    case 14: set="zoom_absolute";
    break;
    }
    cmd.append(set);
    cmd.append(tr("="));
    QString m = QString::number(math,10);
    cmd.append(m);
    ui->textBrowser_3->setText(cmd);
    myProcess.start(cmd);
    myProcess.closeWriteChannel();
}



void Form::sleep(unsigned int msec)
{
QTime dieTime = QTime::currentTime().addMSecs(msec);
while( QTime::currentTime() < dieTime )
QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Form::on_pushButton_2_clicked()
{
    ui->spinBox->setValue(128);
    ui->horizontalSlider->setValue(128);
    ui->spinBox_2->setValue(128);
    ui->horizontalSlider_2->setValue(128);
    ui->spinBox_3->setValue(128);
    ui->horizontalSlider_3->setValue(128);
    ui->spinBox_4->setValue(0);
    ui->horizontalSlider_4->setValue(0);
    ui->spinBox_5->setValue(2);
    ui->horizontalSlider_5->setValue(2);
    ui->spinBox_6->setValue(4000);
    ui->horizontalSlider_6->setValue(4000);
    ui->spinBox_7->setValue(128);
    ui->horizontalSlider_7->setValue(128);
    ui->spinBox_8->setValue(0);
    ui->horizontalSlider_8->setValue(0);
    ui->spinBox_9->setValue(3);
    ui->horizontalSlider_9->setValue(3);
    ui->spinBox_10->setValue(250);
    ui->horizontalSlider_10->setValue(250);
    ui->spinBox_11->setValue(0);
    ui->horizontalSlider_11->setValue(0);
    ui->spinBox_12->setValue(0);
    ui->horizontalSlider_12->setValue(0);
    ui->spinBox_13->setValue(0);
    ui->horizontalSlider_13->setValue(0);
    ui->spinBox_14->setValue(100);
    ui->horizontalSlider_14->setValue(100);
     run();
}



void Form::on_Location_Push_clicked()
{
    ui->spinBox_9->setValue(1);
    ui->horizontalSlider_9->setValue(1);
    ui->spinBox_10->setValue(3);
    ui->horizontalSlider_10->setValue(3);
}

void Form::pic(QString a)
{
    QString cmd = "streamer -o ";
    cmd.append(a+".jpg");
    myProcess.start(cmd);
    myProcess.closeWriteChannel();
}
