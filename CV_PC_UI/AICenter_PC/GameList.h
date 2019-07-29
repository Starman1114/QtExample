#ifndef GAMELIST_H
#define GAMELIST_H

#include <QtWidgets/QDialog>
#include "ui_GameList.h"
#include "FormSet.h"
#include "Image_Small.h"

class GameList : public QDialog
{
    Q_OBJECT

public:
    explicit GameList(QWidget *parent = Q_NULLPTR);
    ~GameList();
	bool setAdd(int ind);
	bool reset(int ind);

private slots:
	void sendIndex(int ind);

signals:
	void add(int ind);

private:
    Ui::GameList_Class ui;
};

#endif // GAMELIST_H
