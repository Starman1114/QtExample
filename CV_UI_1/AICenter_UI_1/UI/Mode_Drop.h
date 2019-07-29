#ifndef MODE_DROP_H
#define MODE_DROP_H

#include <QtWidgets/QDialog>
#include "ui_Mode_Drop.h"
#include "util.h"



class Mode_Drop : public QDialog
{
    Q_OBJECT

public:
    explicit Mode_Drop(AI_MODE_CONF *mode,QWidget *parent = Q_NULLPTR);
    ~Mode_Drop();

private slots:
	void on_checkBox_stateChanged(int arg1);

private:
	void keyPressEvent(QKeyEvent *event);

signals:
	

private:
    Ui::Mode_Drop_Class ui;
	AI_MODE_CONF *mode;
};

#endif // MODE_DROP_H
