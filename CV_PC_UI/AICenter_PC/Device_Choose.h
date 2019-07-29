#ifndef DEVICE_CHOOSE_H
#define DEVICE_CHOOSE_H

#include <QtWidgets/QDialog>
#include "ui_Device_Choose.h"
#include <qDebug>
#include <QMouseEvent>
#include "FormSet.h"
class Device_Choose : public QDialog
{
    Q_OBJECT

public:
	explicit Device_Choose(QWidget *parent = Q_NULLPTR);
    explicit Device_Choose(int index,QString name, QWidget *parent = Q_NULLPTR);
    ~Device_Choose();

private:
	//重写mousePressEvent事件
	void mousePressEvent(QMouseEvent *event);
	void enterEvent(QEvent *e); //鼠标进入事件
	void leaveEvent(QEvent *e);//鼠标离开事件

private slots:
	void onStateChanged(int state);

signals:
	void beChoosen(int ind,bool isChoosen);

private:
    Ui::Device_Choose_Class ui;
	int index;
	
};

#endif // DEVICE_CHOOSE_H
