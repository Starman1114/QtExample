/********************************************************************************
** Form generated from reading UI file 'GameList.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMELIST_H
#define UI_GAMELIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_GameList_Class
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *imageList;

    void setupUi(QDialog *GameList_Class)
    {
        if (GameList_Class->objectName().isEmpty())
            GameList_Class->setObjectName(QString::fromUtf8("GameList_Class"));
        GameList_Class->resize(210, 168);
        verticalLayout = new QVBoxLayout(GameList_Class);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        imageList = new QListWidget(GameList_Class);
        imageList->setObjectName(QString::fromUtf8("imageList"));

        verticalLayout->addWidget(imageList);


        retranslateUi(GameList_Class);

        QMetaObject::connectSlotsByName(GameList_Class);
    } // setupUi

    void retranslateUi(QWidget *GameList_Class)
    {
        GameList_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("GameList_Class", "Form", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class GameList_Class: public Ui_GameList_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMELIST_H
