#include "Image_Big.h"

Image_Big::Image_Big(QWidget *parent) :
	QDialog(parent)
{
	ui.setupUi(this);
	ui.deleteButton->hide();
}


Image_Big::Image_Big(int index, QString name, QString image, QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
	this->index = index;
	this->image = image;
	ui.nameLabel->setText(name);
	this->setStyleSheet(QString("QDialog#Image_Big_Class{border-image:url(%1);}QLabel{color:#DDDDDD;font-size: 20px;}").arg(image));

	FormSet::SetIcon(ui.runButton, QChar(0x0050), 35);

}

Image_Big::~Image_Big()
{

}


void Image_Big::enterEvent(QEvent *e) {
	this->setStyleSheet(QString("QDialog#Image_Big_Class{border-image:url(%1); border:10px solid #014F84;color: #014F84;} QLabel{color:#FFFFFF;font-size: 20px;}").arg(image));
	//this->setStyleSheet("QDialog{border:1px solid #014F84;color: #014F84;}");
	ui.deleteButton->show();
	
}

void Image_Big::leaveEvent(QEvent *e) {
	this->setStyleSheet(QString("QDialog#Image_Big_Class{border-image:url(%1);border:none}QLabel{color:#A6A6A6;font-size: 20px;}").arg(image));
//	this->setStyleSheet("QDialog{border:none}");
	ui.deleteButton->hide();

}

void Image_Big::on_deleteButton_clicked() {
	
	emit deleteDialog(this->index);
}

void Image_Big::on_KeyBoardButton_clicked() {
	SetDialog dialog(this);
	dialog.setStyleSheet(QString("background:none;"));
	
	if (dialog.exec() == QDialog::Accepted) {
		isChoosen = true;
		ui.KeyBoardButton->setStyleSheet(QString("QPushButton{padding:3px;margin:1px 1px 1px 1px;background:none;border-image:url(%1);} QPushButton:hover{padding:3px;margin:1px 1px 1px 1px;background:none;border-image:url(%2);}")
			.arg(":/AICenter_PC/Resources/images/Keyboard_Choose.png").arg(":/AICenter_PC/Resources/images/Keyboard.png"));
	}
	
	
}

//void Image_Big::mousePressEvent(QMouseEvent *event)
//{
//	//Qt::LeftButton
//	//Qt::RightButton
//	if (event->button() == Qt::LeftButton)
//	{
//		emit beclicked(index);
//	}
//}


