#ifndef IMAGE_BIG_H
#define IMAGE_BIG_H

#include <QtWidgets/QDialog>
#include "ui_Image_Big.h"
#include <qDebug>
#include <QMouseEvent>
#include "FormSet.h"
class Image_Big : public QDialog
{
    Q_OBJECT

public:
	explicit Image_Big(QWidget *parent = Q_NULLPTR);
    explicit Image_Big(int index,QString name ,QString image, QWidget *parent = Q_NULLPTR);
    ~Image_Big();

private:
	//重写mousePressEvent事件
	//void mousePressEvent(QMouseEvent *event);
	void enterEvent(QEvent *e); //鼠标进入事件
	void leaveEvent(QEvent *e);//鼠标离开事件

private slots:
	void on_deleteButton_clicked();
	void on_KeyBoardButton_clicked();

signals:
	void deleteDialog(int ind);

private:
    Ui::Image_Big_Class ui;
	int index;
	QString image;
	bool isChoosen = false;
};

#endif // IMAGE_BIG_H
