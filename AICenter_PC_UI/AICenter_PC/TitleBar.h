#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include "ui_TitleBar.h"
#include <QMouseEvent>
#include "FormSet.h"
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

private slots:
	/**************************************************************************
	* ´°¿ÚÀ¸²Ù×÷
	*/
	void on_btnMenu_Close_clicked();
	void on_btnMenu_Min_clicked();
	void on_btnMenu_clicked();

signals:
	void beMin();
	void beExit();

private:
    Ui::TitleBar ui;
	QPoint mousePoint;
	bool mousePressed = false;
	QRect location;

	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *);

	QMainWindow *ptr;
};

#endif // TITLEBAR_H
