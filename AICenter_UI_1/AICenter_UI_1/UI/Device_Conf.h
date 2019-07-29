#ifndef DEVICE_CONF_H
#define DEVICE_CONF_H

#include <QtWidgets/QDialog>
#include "ui_Device_Conf.h"
#include "util.h"
#include "Device_Mode.h"




class Device_Conf : public QDialog
{
    Q_OBJECT

public:
    explicit Device_Conf(AI_GAME_CONF *game,QWidget *parent = Q_NULLPTR);
    ~Device_Conf();

private slots:
	
private:
	void keyPressEvent(QKeyEvent *event);

signals:
	

private:
    Ui::Device_Conf_Class ui;
	AI_GAME_CONF *game;
};

#endif // DEVICE_CONF_H
