#include "Device_Choose.h"

Device_Choose::Device_Choose(QWidget *parent) :
	QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.checkBox, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));
}


Device_Choose::Device_Choose(int index, QString name, QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
	this->index = index;
	ui.checkBox->setText(name);

}

Device_Choose::~Device_Choose()
{

}


void Device_Choose::onStateChanged(int state)
{
	if (state == Qt::Checked) // "选中"
	{
		emit beChoosen(this->index, true);
	}
	else if(state == Qt::Unchecked)// 未选中 - Qt::Unchecked
	{
		emit beChoosen(this->index, false);
	}
	
}


void Device_Choose::enterEvent(QEvent *e) {
	
	
}

void Device_Choose::leaveEvent(QEvent *e) {
	
}

void Device_Choose::mousePressEvent(QMouseEvent *event)
{
	
	if (event->button() == Qt::LeftButton)
	{
		
	}
}
