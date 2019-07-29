#include "Image_Small.h"

Image_Small::Image_Small(QWidget *parent) :
	QDialog(parent)
{
	ui.setupUi(this);

}


Image_Small::Image_Small(int index, QString name, QString image, QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
	this->index = index;
	ui.nameLabel->setText(name);

	pixmap = new QPixmap(image);
	pixmap->scaled(ui.imageLabel->size(), Qt::KeepAspectRatio);
	ui.imageLabel->setScaledContents(true);
	ui.imageLabel->setPixmap(*pixmap);
	ui.nameLabel->setStyleSheet("QLabel{color:#000000}");
	//ui.imageLabel->setStyleSheet(QString("background-image:url(:/AICenter_PC/Resources/images/pbug.jpg);background-size:100% 100%;"));

}

Image_Small::~Image_Small()
{
	delete pixmap;
}

void Image_Small::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		break;
	default:
		QDialog::keyPressEvent(event);
	}
}

void Image_Small::enterEvent(QEvent *e) {
	ui.nameLabel->setStyleSheet("QLabel{color:#00AFF0}");
	this->setStyleSheet("QDialog{border:1px solid #00AFF0;color: #00AFF0;}");
	
}

void Image_Small::leaveEvent(QEvent *e) {
	ui.nameLabel->setStyleSheet("QLabel{color:#000000}");
	this->setStyleSheet("QDialog{border:none}");
}

void Image_Small::mousePressEvent(QMouseEvent *event)
{
	//Qt::LeftButton
	//Qt::RightButton
	if (event->button() == Qt::LeftButton)
	{
		emit beclicked(index);
		
	}
}
