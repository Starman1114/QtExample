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
	//��дmousePressEvent�¼�
	void mousePressEvent(QMouseEvent *event);
	void enterEvent(QEvent *e); //�������¼�
	void leaveEvent(QEvent *e);//����뿪�¼�

private slots:
	void onStateChanged(int state);

signals:
	void beChoosen(int ind,bool isChoosen);

private:
    Ui::Device_Choose_Class ui;
	int index;
	
};

#endif // DEVICE_CHOOSE_H
