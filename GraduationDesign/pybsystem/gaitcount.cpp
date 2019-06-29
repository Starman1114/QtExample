#include "gaitcount.h"
#include "ui_gaitcount.h"

GaitCount::GaitCount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaitCount)
{
    ui->setupUi(this);
    setWindowTitle("步态检测");
    InitStyle();

    C = new Chart();
    F = new FunctionData();
    ChartShow();

    GT = new Gait();
    GT->start();
    GT->pause.lock();

    connect(GT, SIGNAL(resultReady()), this, SLOT(changeData()));
    C->becomeOrigin_Gait(ff_Gait,&m_series_Gait);
}

GaitCount::~GaitCount()
{
    delete ui;
}

void GaitCount::ChartShow()
{
    StartShow();
    for(int i=0;i<ff_Gait.N;i++){
        //添加图表
        C->graphShowSetup(ui->tabWidget,ff_Gait.name[i],&axisX_Gait,&axisY_Gait);
        C->setUp(chartView,chart,ui->tabWidget->widget(i),ff_Gait.f[i],&m_series_Gait,&axisX_Gait,&axisY_Gait,i);
    }
}



void GaitCount::StartShow()
{
    QString file_name =":/qss/Gait.txt"; //文件绝对路径
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    F->readData(&ff_Gait,&in);
    file.close();
}






void GaitCount::InitStyle()  //窗口栏设置
{
   //设置窗体标题栏隐藏
   this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
   location = this->geometry();
   max = false;
   mousePressed = false;
   //安装事件监听器,让标题栏识别鼠标双击
   ui->lab_Title->installEventFilter(this);

   IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);//QChar决定图案
   IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);
   IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
   IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0x26F9), 12);

//   ui->heightEdit->setText(height1);
//   ui->weightEdit->setText(weight1);

   //widget_title的界面黑色是专门在qss文件里写的
}


/**************************************************************************
    * 界面窗口操作
    */
bool GaitCount::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        this->on_btnMenu_Max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void GaitCount::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton) && !max) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void GaitCount::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void GaitCount::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void GaitCount::on_btnMenu_Close_clicked()
{
    //qApp->exit();
    hide();
    emit beClose();
}

void GaitCount::on_btnMenu_Max_clicked()
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

void GaitCount::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}




void GaitCount::on_runButton_clicked()
{
    if(!startGait){
        startGait=true;
        GT->pause.unlock();
        ui->runButton->setText("暂停");
    }else{
        startGait=false;
        GT->pause.lock();
        ui->runButton->setText("运行");
   }

}

void GaitCount::changeData()
{
     if(StepFrequence!=ui->StepFrequenceEdit->text().toFloat())
       ui->StepFrequenceEdit->setText(QString::number(StepFrequence));
     if(StancePercent!=ui->StancePercentEdit->text().toFloat())
       ui->StancePercentEdit->setText(QString::number(StancePercent));
     if(Speed!=ui->SpeedEdit->text().toFloat())
       ui->SpeedEdit->setText(QString::number(Speed));
     if(SwingSpeed!=ui->SwingSpeedEdit->text().toFloat())
       ui->SwingSpeedEdit->setText(QString::number(SwingSpeed));
     if(StrideLength!=ui->StrideLengthEdit->text().toFloat())
       ui->StrideLengthEdit->setText(QString::number(StrideLength));
     if(VerticalLength!=ui->VerticalLengthEdit->text().toFloat())
        ui->VerticalLengthEdit->setText(QString::number(VerticalLength));
}

void GaitCount::on_zeroButton_clicked()
{
    C->becomeOrigin_Gait(ff_Gait,&m_series_Gait);
    GT->GaitanalyseClearData();
}
