#ifndef DEVICE_MODE_H
#define DEVICE_MODE_H

#include <QtWidgets/QDialog>
#include "ui_Device_Mode.h"
#include "util.h"
#include "Mode_Drop.h"
#include "Mode_HotKey.h"





class Device_Mode : public QDialog
{
    Q_OBJECT

public:
    explicit Device_Mode(AI_DEVICE_CONF *device,QWidget *parent = Q_NULLPTR);
    ~Device_Mode();

private slots:
	
private:
	void keyPressEvent(QKeyEvent *event);

signals:
	

private:
    Ui::Device_Mode_Class ui;
	AI_DEVICE_CONF *device;
	QPixmap *pixmap;
};

#endif // DEVICE_MODE_H
