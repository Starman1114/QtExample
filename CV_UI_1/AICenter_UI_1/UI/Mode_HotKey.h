#ifndef MODE_HOTKEY_H
#define MODE_HOTKEY_H

#include <QtWidgets/QDialog>
#include "ui_Mode_HotKey.h"
#include "util.h"



class Mode_HotKey : public QDialog
{
    Q_OBJECT

public:
    explicit Mode_HotKey(AI_MODE_CONF *mode,QWidget *parent = Q_NULLPTR);
    ~Mode_HotKey();

private slots:
	void on_checkBox_stateChanged(int arg1);
	void on_pushButton_clicked();

private:
	void keyPressEvent(QKeyEvent *event);
signals:
	

private:
    Ui::Mode_HotKey_Class ui;
	AI_MODE_CONF *mode;
	bool change = false;
};

#endif // MODE_HOTKEY_H
