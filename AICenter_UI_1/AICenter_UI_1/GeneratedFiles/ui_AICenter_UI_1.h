/********************************************************************************
** Form generated from reading UI file 'AICenter_UI_1.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AICENTER_UI_1_H
#define UI_AICENTER_UI_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "AI_Assist.h"
#include "Device_Support.h"
#include "TitleBar.h"

QT_BEGIN_NAMESPACE

class Ui_AICenter_UI_1Class
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QWidget *MainWidget;
    QVBoxLayout *verticalLayout_3;
    QWidget *TopWidget;
    QVBoxLayout *verticalLayout;
    TitleBar *TitleWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *Device_Support_Button;
    QPushButton *AI_Assist_Button;
    QPushButton *Scene_Assist_Button;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    Device_Support *page;
    AI_Assist *page_2;

    void setupUi(QMainWindow *AICenter_UI_1Class)
    {
        if (AICenter_UI_1Class->objectName().isEmpty())
            AICenter_UI_1Class->setObjectName(QString::fromUtf8("AICenter_UI_1Class"));
        AICenter_UI_1Class->resize(1150, 696);
        centralWidget = new QWidget(AICenter_UI_1Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(7, 7, 7, 7);
        MainWidget = new QWidget(centralWidget);
        MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        verticalLayout_3 = new QVBoxLayout(MainWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        TopWidget = new QWidget(MainWidget);
        TopWidget->setObjectName(QString::fromUtf8("TopWidget"));
        verticalLayout = new QVBoxLayout(TopWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TitleWidget = new TitleBar(TopWidget);
        TitleWidget->setObjectName(QString::fromUtf8("TitleWidget"));

        verticalLayout->addWidget(TitleWidget);


        verticalLayout_3->addWidget(TopWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Device_Support_Button = new QPushButton(MainWidget);
        Device_Support_Button->setObjectName(QString::fromUtf8("Device_Support_Button"));

        verticalLayout_2->addWidget(Device_Support_Button);

        AI_Assist_Button = new QPushButton(MainWidget);
        AI_Assist_Button->setObjectName(QString::fromUtf8("AI_Assist_Button"));

        verticalLayout_2->addWidget(AI_Assist_Button);

        Scene_Assist_Button = new QPushButton(MainWidget);
        Scene_Assist_Button->setObjectName(QString::fromUtf8("Scene_Assist_Button"));

        verticalLayout_2->addWidget(Scene_Assist_Button);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);

        stackedWidget = new QStackedWidget(MainWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new Device_Support();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        page_2 = new AI_Assist();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(MainWidget);

        AICenter_UI_1Class->setCentralWidget(centralWidget);

        retranslateUi(AICenter_UI_1Class);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(AICenter_UI_1Class);
    } // setupUi

    void retranslateUi(QMainWindow *AICenter_UI_1Class)
    {
        AICenter_UI_1Class->setWindowTitle(QApplication::translate("AICenter_UI_1Class", "AICenter_UI_1", nullptr));
        Device_Support_Button->setText(QApplication::translate("AICenter_UI_1Class", "\350\256\276\345\244\207\346\224\257\346\214\201", nullptr));
        AI_Assist_Button->setText(QApplication::translate("AICenter_UI_1Class", "AI\350\276\205\345\212\251", nullptr));
        Scene_Assist_Button->setText(QApplication::translate("AICenter_UI_1Class", "\345\234\272\346\231\257\350\276\205\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AICenter_UI_1Class: public Ui_AICenter_UI_1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AICENTER_UI_1_H
