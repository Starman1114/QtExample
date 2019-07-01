#ifndef FRAME_H
#define FRAME_H

#include <QtWidgets/QDialog>
#include "ui_Frame.h"
#include <QMouseEvent>
#include <qDebug>
#include <QMenu>
#include "configure.h"
class Frame : public QDialog
{
    Q_OBJECT

public:
    explicit Frame(QWidget *parent = Q_NULLPTR);
	explicit Frame(int ind, int type);
    ~Frame();
	QRect getRect();
	void ChangeInd(int nind);
	int returnType();
	void changeIsRun(bool isr);

public slots:
	void ChangeType();
private slots:
	void beClose();
	void Delete();

signals:
	void returnInd(int ind);
private:
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *);

	void showEvent(QShowEvent *event);
	void calculateCurrentStrechRect();

	WindowStretchRectState getCurrentStretchState(QPoint cursorPos);
	void updateMouseStyle(WindowStretchRectState stretchState);

	void updateWindowSize();

	void contextMenuEvent(QContextMenuEvent* e);

private:
    Ui::Frame_Class ui;
	QPoint mousePoint;
	QPoint m_startPoint;
	QPoint m_endPoint;
	bool mousePressed = false;
	QRect m_windowRectBeforeStretch;

	bool atAngle = false;

	// 四个角Rect
	QRect m_leftTopRect;
	QRect m_leftBottomRect;
	QRect m_rightTopRect;
	QRect m_rightBottomRect;

	 // 四条边Rect
	QRect m_topBorderRect;
	QRect m_rightBorderRect;
	QRect m_bottomBorderRect;
	QRect m_leftBorderRect;
	WindowStretchRectState m_stretchRectState;

	QAction *m_ChangeAction;
	QAction *m_deleteAction;

	QStringList boardColor = { "#00CD66","#FF8C00" };
	int type;
	int ind;
	bool isRun = false;
};

#endif // FRAME_H
