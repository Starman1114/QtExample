#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ScreenShot.h"
#include <QScreen>
#include <QPixmap>
#include <QDateTime>
#include <QDebug>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QVector>
#include<MyGlobalShortCut/MyGlobalShortCut.h>
#include "Frame.h"
#include "AddLabel.h"
#include <QMetaEnum>
#include <QDir>
#include <QDateTime>
#include <QTimer>
class ScreenShot : public QMainWindow
{
	Q_OBJECT

public:
	ScreenShot(QWidget *parent = Q_NULLPTR);
	~ScreenShot();

private:
	void closeEvent(QCloseEvent * e);
	

protected:
	//将图片设置为随着窗口变化而变化
	//virtual void resizeEvent(QResizeEvent *event) override;

signals:
	void beclose();

private slots:
	void addPBoard();
	void addNBoard();
	void deleteBoard(int ind);
	void running();
	void timerUpDate();
	void ChangeFirstType();
	void setRectValue(int x, int y, int w, int h);
	void ReturnRectValue(int x, int y, int w, int h);

private:
	Ui::ScreenShotClass ui;
	QPixmap pixmap;
	QVector<Frame*> FrameList;
	int colorInd = 0;
	
	QStringList dirList = {"./Positive" ,"./Negative" };
	QTimer *timer;
	AddLabel *aLabel;

};
