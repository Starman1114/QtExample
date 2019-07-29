#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include "ui_TitleBar.h"
#include <QMouseEvent>
#include "util.h"
#include <QMainWindow>


namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();
	void setPoint(QWidget *w);

private slots:
	/**************************************************************************
	* ´°¿ÚÀ¸²Ù×÷
	*/
	void on_btnMenu_Close_clicked();
	void on_btnMenu_Min_clicked();
	void on_btnMenu_clicked();
	void on_btnMenu_Max_clicked();

signals:
	//void beMin();
	//void beExit();
	//void beMax();

private:
    Ui::TitleBar ui;
	QPoint mousePoint;
	bool mousePressed = false;
	bool max = false;
	QRect location;
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *);
	
	QMainWindow *ptr;

	QWidget *widget;
};

#endif // TITLEBAR_H
