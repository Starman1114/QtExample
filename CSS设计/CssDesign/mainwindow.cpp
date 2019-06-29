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
    setWindowTitle("CSS设计");
    menu1=ui->menuBar->addMenu("设置(&Q)");
    QAction *aboutCSS=new QAction("CSS附注", this);
    QObject::connect(aboutCSS, SIGNAL(triggered(bool)), this, SLOT(ShowAboutCss(bool)));
    menu1->addAction(aboutCSS);

    ui->Backwidget->setStyleSheet(QString("QWidget#%1{background:#%2;}")
                                  .arg(ui->Backwidget->objectName())
                                  .arg("FFFFFF"));

    QString text = "无线36";
    QPushButton *botton=new QPushButton(this);
    botton->setText(text);
    botton->setObjectName(text);
    ui->stackedWidget->addWidget(botton);
    ui->comboBox->addItem("QPushButton");

    QLineEdit *line= new QLineEdit(this);
    line->setText(text);
    line->setObjectName(text);
    ui->stackedWidget->addWidget(line);
    ui->comboBox->addItem("QLineEdit");

    QLabel *label =new QLabel(this);
    label->setText(text);
    label->setObjectName(text);
    ui->stackedWidget->addWidget(label);
    ui->comboBox->addItem("QLabel");

    QComboBox *combo =new QComboBox(this);
    combo->addItem(text);
    combo->setObjectName(text);
    ui->stackedWidget->addWidget(combo);
    ui->comboBox->addItem("QComboBox");

    QTableWidget *tabwidget = new QTableWidget(this);
    tabwidget->setColumnCount(2);//只设置列数，行数动态中增加
    tabwidget->insertRow(0);//增加一行
    QStringList a = {text,"wireless36"};
    tabwidget->setHorizontalHeaderLabels(a);
    QTableWidgetItem *item = new QTableWidgetItem(text);
    tabwidget->setItem(0,0,item);
    tabwidget->setObjectName(text);
    ui->stackedWidget->addWidget(tabwidget);
    ui->comboBox->addItem("QTableWidget");






    //  QRegExp regx("[A-Z0-9]*");//正则表达式
  //  QValidator *validator = new QRegExpValidator(regx, this );
  //  ui->HEXEdit->setValidator( validator );//设置用户名的输入验证
    ui->HEXEdit->setFocusPolicy(Qt::NoFocus);

    ui->toolBox->setFrameShape(QFrame::Box);
    widget_Font = new CssDataWidget(this,":/src/FontSet.txt");
    ui->toolBox->insertItem(0,widget_Font,tr("字体"));
    widget_Backgroup = new CssDataWidget(this,":/src/BackgroupSet.txt");
    ui->toolBox->insertItem(1,widget_Backgroup,tr("背景"));
    widget_Border = new CssDataWidget(this,":/src/BorderSet.txt");
    ui->toolBox->insertItem(2,widget_Border,tr("边框"));

    ui->toolBox->setCurrentIndex(0);


}


void MainWindow::on_runSetButton_clicked()
{
   // qApp->setStyleSheet(ui->CSSEdit->placeholderText());

    //ui->pushButton->setStyleSheet(ui->CSSEdit->toPlainText());

    QString test =  ui->stackedWidget->currentWidget()->objectName();
    ui->CSSEdit->clear();
    QString preText = QString("%1#%2{\n").arg(ui->comboBox->currentText()).arg(test);

    ui->CSSEdit->append(preText+widget_Font->GetFontData());
    ui->CSSEdit->append(widget_Backgroup->GetFontData());
    ui->CSSEdit->append(widget_Border->GetFontData());
    ui->CSSEdit->append("}");

    qApp->setStyleSheet(ui->CSSEdit->toPlainText());
}

void MainWindow::on_runTextButton_clicked()
{
    qApp->setStyleSheet(ui->CSSEdit->toPlainText());
}

void MainWindow::on_RspinBox_valueChanged(int arg1)
{
    ui->HEXEdit->setText(QString("%1%2%3").arg(IntToHex(arg1))
                         .arg(IntToHex(ui->GspinBox->value()))
                         .arg(IntToHex(ui->BspinBox->value())));
}

void MainWindow::on_GspinBox_valueChanged(int arg1)
{
    ui->HEXEdit->setText(QString("%1%2%3").arg(IntToHex(ui->RspinBox->value()))
                         .arg(IntToHex(arg1))
                         .arg(IntToHex(ui->BspinBox->value())));
}

void MainWindow::on_BspinBox_valueChanged(int arg1)
{
    ui->HEXEdit->setText(QString("%1%2%3").arg(IntToHex(ui->RspinBox->value()))
                         .arg(IntToHex(ui->GspinBox->value()))
                         .arg(IntToHex(arg1)));
}

QString MainWindow::IntToHex(int number)
{
    if(number>15)
        return QString::number(number, 16).toUpper();
    else
        return "0"+QString::number(number, 16).toUpper();
}


void MainWindow::on_HEXEdit_textChanged(const QString &arg1)
{
    QString line = QString("QWidget#%1{background:#%2;}")
           .arg(ui->Backwidget->objectName())
           .arg(arg1);
    ui->Backwidget->setStyleSheet(line);
}

void MainWindow::ShowAboutCss(bool ok)
{
    if(!ok){
        AboutCss ac(this);
        ac.exec();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{

    if (e->key() == Qt::Key_Enter|| e->key() == Qt::Key_Return)
    {                 //小键盘                      //大键盘
        ui->runSetButton->clicked(true);
    }
}



void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
