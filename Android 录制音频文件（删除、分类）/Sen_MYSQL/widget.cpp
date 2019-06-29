#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    InitStyle();
}

Widget::~Widget()
{
    delete ui;
}

//设置皮肤样式
void Widget::SetStyle(const QString &styleName)
{
    QFile file(QString(":/qss/%1.css").arg(styleName));
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
       // QString paletteColor = qss.mid(20, 7);
      //  QString paletteColor = "#444444";
        QString paletteColor = "#FFFFFF";
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void Widget::InitStyle()  //窗口栏设置
{
    //ui->label_tilte->setAlignment(Qt::AlignCenter);
    SetStyle("pybQSS");
    //去除选中边框

    ui->leftButton->setFocusPolicy(Qt::NoFocus);
    ui->rightButton->setFocusPolicy(Qt::NoFocus);

    height = 35;
    weight =50;
    ui->titleButton->setDisabled(true);
    SetIcon(ui->titleButton, QString("演讲情感分析"), "Microsoft YaHei",height,weight);
    SetIcon(ui->rightButton, QChar(0xf013), "Microsoft YaHei",height,weight);


    m_pStackedWidget = new QStackedWidget();
    setD = new SetData();
    workW = new WorkWidget();
    m_pStackedWidget->addWidget(workW);
    m_pStackedWidget->addWidget(setD);
    QVBoxLayout *vbox = new QVBoxLayout(ui->widget_main);
    vbox->addWidget(m_pStackedWidget);
    ui->widget_main->setLayout(vbox);

}

void Widget::on_rightButton_clicked()
{
    m_pStackedWidget->setCurrentIndex(1);
    SetIcon(ui->titleButton, QString("设置"), "Microsoft YaHei",height,weight);
    SetIcon(ui->leftButton, QString(" ")+QChar(0x276E), "Microsoft YaHei", height,weight);
}

void Widget::on_leftButton_clicked()
{
    m_pStackedWidget->setCurrentIndex(0);
    SetIcon(ui->titleButton, QString("演讲情感分析"), "Microsoft YaHei",height,weight);
    SetIcon(ui->leftButton, QString(" "), "Microsoft YaHei",height,weight);
}

void Widget::SetIcon(QPushButton* btn, QString c, QString family,int size, int weight)
{
    QFont font1(family, size, weight);
    btn->setFont(font1);
    btn->setText(c);
}

void Widget::SetIcon(QLabel *lab, QString c, QString family,int size, int weight)
{
    QFont font1(family, size, weight); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是weight）
    lab->setFont(font1);
    lab->setText(c);

}

