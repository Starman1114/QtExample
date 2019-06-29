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
	//FormSet::SetIcon(ui.lab_Title, "IntelAI", 15);
	FormSet::SetIcon(ui.loginButton, "Login", 10);

	//ui.lab_Title->setDisabled(true);
	
	ptr = (QMainWindow*)window();


}

TitleBar::~TitleBar()
{
	
}

void TitleBar::on_btnMenu_clicked()
{
	
	
}

void TitleBar::on_btnMenu_Min_clicked()
{
	//this->showMinimized();
	emit beMin();
	
}

void TitleBar::on_btnMenu_Close_clicked()
{
	emit beExit();
}

/**************************************************************************
* 界面窗口操作
*/
void TitleBar::mouseMoveEvent(QMouseEvent *e)
{
	if (mousePressed && (e->buttons() && Qt::LeftButton)) {
		
		ptr->move(e->globalPos() - mousePoint);
		e->accept();
	}
}

void TitleBar::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		mousePressed = true;
		mousePoint = e->globalPos() - ptr->pos();
		e->accept();
	}
}

void TitleBar::mouseReleaseEvent(QMouseEvent *)
{
	mousePressed = false;
}