#ifndef IMAGE_SMALL_H
#define IMAGE_SMALL_H

#include <QtWidgets/QDialog>
#include "ui_Image_Small.h"
#include <qDebug>
#include <QMouseEvent>
class Image_Small : public QDialog
{
    Q_OBJECT

public:
	explicit Image_Small(QWidget *parent = Q_NULLPTR);
    explicit Image_Small(int index,QString name ,QString image, QWidget *parent = Q_NULLPTR);
    ~Image_Small();

private:
	//重写mousePressEvent事件
	void mousePressEvent(QMouseEvent *event);
	void enterEvent(QEvent *e); //鼠标进入事件
	void leaveEvent(QEvent *e);//鼠标离开事件

signals:
	void beclicked(int ind);

private:
    Ui::Image_Small_Class ui;
	int index;
	QPixmap *pixmap;
};

#endif // IMAGE_SMALL_H
