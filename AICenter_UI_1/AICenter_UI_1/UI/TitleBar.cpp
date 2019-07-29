#include "TitleBar.h"


TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	this->setParent(parent);
	
	FormSet::SetIcon(ui.btnMenu_Close, QChar(0xf00d), 15);//QChar决定图案
	FormSet::SetIcon(ui.btnMenu_Min, QChar(0xf068), 15);
	FormSet::SetIcon(ui.btnMenu, QChar(0xf0c9), 15);
	FormSet::SetIcon(ui.btnMenu_Max, QChar(0xf096), 15);

	
	ptr = (QMainWindow*)window();

	

}

TitleBar::~TitleBar()
{
	
}

void TitleBar::setPoint(QWidget *w) {
	widget = w;
	location = widget->geometry();
}

void TitleBar::on_btnMenu_clicked()
{
	
	
}

void TitleBar::on_btnMenu_Min_clicked()
{
	ptr->showMinimized();
	//emit beMin();
	
}

void TitleBar::on_btnMenu_Close_clicked()
{
	qApp->exit();
}

void TitleBar::on_btnMenu_Max_clicked()
{
	if (max) {
		widget->setGeometry(location);
	}
	else {
		location = widget->geometry();
		//this->showMaximized();
		ptr->setGeometry(QApplication::desktop()->availableGeometry());
	}
	max = !max;
}

/**************************************************************************
* 界面窗口操作
*/
void TitleBar::mouseMoveEvent(QMouseEvent *e)
{
	if (mousePressed && (e->buttons() && Qt::LeftButton)) {
		
		widget->move(e->globalPos() - mousePoint);
		e->accept();
	}
}

void TitleBar::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		mousePressed = true;
		mousePoint = e->globalPos() - widget->pos();
		e->accept();
	}
}

void TitleBar::mouseReleaseEvent(QMouseEvent *)
{
	mousePressed = false;
}