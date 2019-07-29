/********************************************************************************
** Form generated from reading UI file 'AICenter_PC.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AICENTER_PC_H
#define UI_AICENTER_PC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <TitleBar.h>
#include "GameList.h"
#include "MySpeed.h"

QT_BEGIN_NAMESPACE

class Ui_AICenter_PCClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QWidget *MainWidget;
    QVBoxLayout *verticalLayout_3;
    QWidget *TopWidget;
    QVBoxLayout *verticalLayout_2;
    TitleBar *TitleWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *ChooseSpeed;
    QPushButton *ChooseGame;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    MySpeed *page_3;
    GameList *page_4;

    void setupUi(QMainWindow *AICenter_PCClass)
    {
        if (AICenter_PCClass->objectName().isEmpty())
            AICenter_PCClass->setObjectName(QString::fromUtf8("AICenter_PCClass"));
        AICenter_PCClass->resize(609, 401);
        centralWidget = new QWidget(AICenter_PCClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(7, 7, 7, 7);
        MainWidget = new QWidget(centralWidget);
        MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        verticalLayout_3 = new QVBoxLayout(MainWidget);
        verticalLayout_3->setSpacing(20);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        TopWidget = new QWidget(MainWidget);
        TopWidget->setObjectName(QString::fromUtf8("TopWidget"));
        verticalLayout_2 = new QVBoxLayout(TopWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        TitleWidget = new TitleBar(TopWidget);
        TitleWidget->setObjectName(QString::fromUtf8("TitleWidget"));

        verticalLayout_2->addWidget(TitleWidget);


        verticalLayout_3->addWidget(TopWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ChooseSpeed = new QPushButton(MainWidget);
        ChooseSpeed->setObjectName(QString::fromUtf8("ChooseSpeed"));
        ChooseSpeed->setMinimumSize(QSize(0, 40));
        ChooseSpeed->setFlat(false);

        verticalLayout->addWidget(ChooseSpeed);

        ChooseGame = new QPushButton(MainWidget);
        ChooseGame->setObjectName(QString::fromUtf8("ChooseGame"));
        ChooseGame->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(ChooseGame);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        stackedWidget = new QStackedWidget(MainWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_3 = new MySpeed();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        stackedWidget->addWidget(page_3);
        page_4 = new GameList();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        stackedWidget->addWidget(page_4);

        horizontalLayout->addWidget(stackedWidget);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(MainWidget);

        AICenter_PCClass->setCentralWidget(centralWidget);

        retranslateUi(AICenter_PCClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AICenter_PCClass);
    } // setupUi

    void retranslateUi(QMainWindow *AICenter_PCClass)
    {
        AICenter_PCClass->setWindowTitle(QApplication::translate("AICenter_PCClass", "AICenter_PC", nullptr));
        ChooseSpeed->setText(QApplication::translate("AICenter_PCClass", "\346\210\221\347\232\204\345\212\240\351\200\237", nullptr));
        ChooseGame->setText(QApplication::translate("AICenter_PCClass", "\346\270\270\346\210\217\345\272\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AICenter_PCClass: public Ui_AICenter_PCClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AICENTER_PC_H
