/********************************************************************************
** Form generated from reading UI file 'AI_Assist.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AI_ASSIST_H
#define UI_AI_ASSIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AI_Assist_Class
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *imageList;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QWidget *page_4;

    void setupUi(QWidget *AI_Assist_Class)
    {
        if (AI_Assist_Class->objectName().isEmpty())
            AI_Assist_Class->setObjectName(QString::fromUtf8("AI_Assist_Class"));
        AI_Assist_Class->resize(846, 443);
        horizontalLayout = new QHBoxLayout(AI_Assist_Class);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        imageList = new QListWidget(AI_Assist_Class);
        imageList->setObjectName(QString::fromUtf8("imageList"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imageList->sizePolicy().hasHeightForWidth());
        imageList->setSizePolicy(sizePolicy);
        imageList->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(imageList);

        stackedWidget = new QStackedWidget(AI_Assist_Class);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        stackedWidget->addWidget(page_4);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(AI_Assist_Class);

        QMetaObject::connectSlotsByName(AI_Assist_Class);
    } // setupUi

    void retranslateUi(QWidget *AI_Assist_Class)
    {
        AI_Assist_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("AI_Assist_Class", "Form", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class AI_Assist_Class: public Ui_AI_Assist_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AI_ASSIST_H
