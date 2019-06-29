#include "trashdialog.h"
#include "ui_trashdialog.h"

TrashDialog::TrashDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrashDialog)
{
    ui->setupUi(this);
    QFont font("Microsoft YaHei", 25, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗
    ui->listWidget->setFont(font);
    for(int i=0;i<FileName.length();i++){
        QListWidgetItem * item = new QListWidgetItem ();
        QCheckBox * box = new QCheckBox (FileName[i]);
        box->setCheckable ( true);
        CheckList.append(box);
        ui->listWidget->addItem( item );
        ui->listWidget->setItemWidget( item,CheckList.back());
    }

}

TrashDialog::~TrashDialog()
{
    delete ui;
}

void TrashDialog::on_okButton_clicked()
{
    for(int i=CheckList.length()-1;i>-1;i--){
        if(CheckList.at(i)->isChecked()){
            QStringList pre = CheckList.at(i)->text().split(QRegExp("[.]"));
            QFile file(QString("%1/%2.wav").arg(route).arg(pre[0]));
            if (file.exists())
            {
                file.remove();
                FileName.removeAt(i);

            }
            QFile file1(QString("%1/%2.raw").arg(route).arg(pre[0]));
            if (file1.exists())
            {
                file1.remove();
            }
        }
    }
    accept();
}

void TrashDialog::on_cancelButton_clicked()
{
    reject();
}

void TrashDialog::on_allBox_clicked(bool checked)
{
    if(checked){
        for(int i=0;i<CheckList.length();i++){
            if(!CheckList.at(i)->isChecked()){
                CheckList.at(i)->setChecked(true);
            }
        }
    }else{
        for(int i=0;i<CheckList.length();i++){
            if(CheckList.at(i)->isChecked()){
                CheckList.at(i)->setChecked(false);
            }
        }
    }
}
