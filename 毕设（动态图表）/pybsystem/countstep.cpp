#include "countstep.h"
#include "ui_countstep.h"

CountStep::CountStep(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CountStep)
{
    ui->setupUi(this);
    setWindowTitle("计步");
    InitStyle();

    C = new Chart();
    F = new FunctionData();
    ChartShow();

    CT = new Count();
    CT->start();
    CT->pause.lock();

    connect(CT, SIGNAL(resultReady()), this, SLOT(changeData()));
    C->becomeOrigin_Count(ff_Count,&m_series_Count);
}

CountStep::~CountStep()
{
    delete ui;
}

void CountStep::ChartShow()
{
    StartShow();
    for(int i=0;i<ff_Count.N;i++){
        //添加图表
        C->graphShowSetup(ui->tabWidget,ff_Count.name[i],&axisX_Count,&axisY_Count);
        C->setUp(chartView,chart,ui->tabWidget->widget(i),ff_Count.f[i],&m_series_Count,&axisX_Count,&axisY_Count,i);
    }
}



void CountStep::StartShow()
{
    QString file_name =":/qss/countStep.txt"; //文件绝对路径
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    F->readData(&ff_Count,&in);
    file.close();
}






void CountStep::InitStyle()  //窗口栏设置
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
bool CountStep::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        this->on_btnMenu_Max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void CountStep::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton) && !max) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void CountStep::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void CountStep::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void CountStep::on_btnMenu_Close_clicked()
{
    //qApp->exit();
    hide();
    emit beClose();
}

void CountStep::on_btnMenu_Max_clicked()
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

void CountStep::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}




void CountStep::on_runButton_clicked()
{
    if(!step_Count){
        weight1=ui->weightEdit->text().toInt();
        height1=ui->heightEdit->text().toInt();
        ui->weightEdit->setDisabled(true);
        ui->heightEdit->setDisabled(true);
        step_Count=true;
        CT->pause.unlock();
        ui->runButton->setText("暂停");
    }else{

        ui->weightEdit->setEnabled(true);
        ui->heightEdit->setEnabled(true);
        step_Count=false;
        CT->pause.lock();
        ui->runButton->setText("运行");
    }

}

void CountStep::changeData()
{
    if(STEPS!=ui->stepEdit->text().toLong())
        ui->stepEdit->setText(QString::number(STEPS));
    if(ENERGS!=ui->energyEdit->text().toLong())
        ui->energyEdit->setText(QString::number(ENERGS));
}

void CountStep::on_zeroButton_clicked()
{
    STEPS=0;
    ENERGS=0;
    C->becomeOrigin_Count(ff_Count,&m_series_Count);
}
