#include "aboutcss.h"
#include "ui_aboutcss.h"

AboutCss::AboutCss(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutCss)
{
    ui->setupUi(this);
    ReadTxt(":/src/AboutCss.txt");
    ui->toolBox->setCurrentIndex(0);

}

AboutCss::~AboutCss()
{
    delete ui;
}

void AboutCss::ReadTxt(QString FireName)
{
    QFile file(FireName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
     }
    QTextStream in(&file);
    ChangeBox(&in);
}

void AboutCss::ChangeBox(QTextStream *in)
{
    QTextBrowser *text;
    QString line = in->readLine();
    while (!line.isNull()){
        if(line.length()>1){
            if(line.at(0)=="#"){
                QStringList head =  line.split(QRegExp("[#]"));
                text = new QTextBrowser();
                ui->toolBox->insertItem(0,text,head[1]);

            }else{
                text->append(line);
            }
        }
        line = in->readLine();
    }
}

void AboutCss::on_pushButton_clicked()
{
    accept();
}
