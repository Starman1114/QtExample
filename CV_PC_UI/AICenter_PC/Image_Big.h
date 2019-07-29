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
	//��дmousePressEvent�¼�
	//void mousePressEvent(QMouseEvent *event);
	void enterEvent(QEvent *e); //�������¼�
	void leaveEvent(QEvent *e);//����뿪�¼�

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
