#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AICenter_PC.h"
#include "TitleBar.h"
#include "FormSet.h"
#include "MySpeed.h"
#include "GameList.h" 

class AICenter_PC : public QMainWindow
{
	Q_OBJECT

public:
	AICenter_PC(QWidget *parent = Q_NULLPTR);
	~AICenter_PC();

private:
	void SetStyle(const QString &styleName);//样式表
	void Initialization();
	void paintEvent(QPaintEvent *event);

private slots:
	/**************************************************************************
	* 窗口栏操作
	*/
	void on_btnMenu_Min_clicked();
	void on_btnMenu_Close_clicked();
	/**************************************************************************
	* 切换窗口
	*/
	void on_ChooseSpeed_clicked();
	void on_ChooseGame_clicked();

	/**************************************************************************
	* 添加游戏
	*/
	bool addGame(int ind);
	bool deleteGame(int ind); 

private:
	Ui::AICenter_PCClass ui;

};
