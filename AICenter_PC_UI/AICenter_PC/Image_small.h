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
	//��дmousePressEvent�¼�
	void mousePressEvent(QMouseEvent *event);
	void enterEvent(QEvent *e); //�������¼�
	void leaveEvent(QEvent *e);//����뿪�¼�

signals:
	void beclicked(int ind);

private:
    Ui::Image_Small_Class ui;
	int index;
	QPixmap *pixmap;
};

#endif // IMAGE_SMALL_H
