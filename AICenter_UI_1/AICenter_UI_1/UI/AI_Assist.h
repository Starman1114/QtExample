#ifndef AI_ASSIST_H
#define AI_ASSIST_H

#include <QtWidgets/QDialog>
#include "ui_AI_Assist.h"
#include "util.h"
#include "Image_Small.h"
#include "Device_Conf.h"



class AI_Assist : public QDialog
{
    Q_OBJECT

public:
    explicit AI_Assist(QWidget *parent = Q_NULLPTR);
    ~AI_Assist();

private slots:
	void gain_Game_Ind(int ind);

signals:
	
private:
	int ReadXMLFile(QString FilePath);
	void keyPressEvent(QKeyEvent *event);

private:
    Ui::AI_Assist_Class ui;
	vector<AI_GAME_CONF> gameList;
};

#endif // AI_ASSIST_H
