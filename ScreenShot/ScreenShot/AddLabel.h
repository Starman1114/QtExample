#ifndef ADDLABEL_H
#define ADDLABEL_H

#include <QtWidgets/QDialog>
#include "ui_AddLabel.h"
#include <QMouseEvent>
#include <qDebug>
#include <QMenu>
#include "configure.h"
#include <QMouseEvent>
#include <QKeyEvent>

class AddLabel : public QDialog
{
    Q_OBJECT

public:
    explicit AddLabel(QWidget *parent = Q_NULLPTR);
	~AddLabel();
	void setValue(int x, int y, int w, int h);

public slots:
	
private slots:
	void beClose();


signals:
	void putRect(int x, int y, int w, int h);
private:
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *);

	void keyPressEvent(QKeyEvent* e);

private:
    Ui::AddLabel_Class ui;
	QPoint mousePoint;
	bool mousePressed = false;
	
};

#endif // ADDLABEL_H
