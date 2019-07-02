#include "AddLabel.h"


AddLabel::AddLabel(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Dialog);
	this->setStyleSheet(QString("#AddLabel_Class{border:2px solid  %1;background:none;}").arg("#005DBC"));
}

AddLabel::~AddLabel()
{
	
}		   

void AddLabel::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
	{
		emit putRect(ui.xBox->value(), ui.yBox->value(), ui.wBox->value(), ui.hBox->value());
	}
}

void AddLabel::beClose() {
	this->close();
}


void AddLabel::setValue(int x, int y, int w, int h) {
	ui.xBox->setValue(x);
	ui.yBox->setValue(y);
	ui.wBox->setValue(w);
	ui.hBox->setValue(h);
}

/**************************************************************************
* 界面窗口操作
*/
void AddLabel::mouseMoveEvent(QMouseEvent *e)
{
	if (mousePressed && (e->buttons() && Qt::LeftButton)) {
		this->move(e->globalPos() - mousePoint);
		e->accept();
	}
}

void AddLabel::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		mousePressed = true;
		mousePoint = e->globalPos() - this->pos();
		e->accept();
	}

}

void AddLabel::mouseReleaseEvent(QMouseEvent *)
{
	mousePressed = false;
}