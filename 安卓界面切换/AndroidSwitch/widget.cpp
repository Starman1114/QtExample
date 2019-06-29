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
    ui->label_tilte->setAlignment(Qt::AlignCenter);
    SetStyle("pybQSS");
    //去除选中边框
    ui->oneButton->setFocusPolicy(Qt::NoFocus);
    ui->twoButton->setFocusPolicy(Qt::NoFocus);
    ui->leftButton->setFocusPolicy(Qt::NoFocus);
    ui->rightButton->setFocusPolicy(Qt::NoFocus);

    int height =  ui->rightButton->height()-3;
    SetIcon(ui->rightButton, QChar(0xf013), height);
    SetIcon(ui->leftButton, QChar(0x276E)+QString(" 我"), height);
    SetIcon(ui->label_tilte, QString("音频录制"), height);

    m_pStackedWidget = new QStackedWidget();
    one = new OneWidget();
    two = new TwoWidget();
    setD = new SetData();
    m_pStackedWidget->addWidget(one);
    m_pStackedWidget->addWidget(two);
    m_pStackedWidget->addWidget(setD);
    QVBoxLayout *vbox = new QVBoxLayout(ui->widget_main);
    vbox->addWidget(m_pStackedWidget);
    ui->widget_main->setLayout(vbox);

}

void Widget::SetIcon(QPushButton* btn, QString c, int size)
{
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setText(c);
}

void Widget::SetIcon(QLabel *lab, QString c, int size)
{
    iconFont.setPointSize(size);
    lab->setFont(iconFont);
    lab->setText(c);
}

void Widget::on_oneButton_clicked()
{
    m_pStackedWidget->setCurrentIndex(0);
    SetIcon(ui->label_tilte, QString("音频录制"), ui->label_tilte->font().pointSize());
}

void Widget::on_twoButton_clicked()
{
    m_pStackedWidget->setCurrentIndex(1);
}

void Widget::on_rightButton_clicked()
{
    m_pStackedWidget->setCurrentIndex(2);
    SetIcon(ui->label_tilte, QString("设置"), ui->label_tilte->font().pointSize());

}
