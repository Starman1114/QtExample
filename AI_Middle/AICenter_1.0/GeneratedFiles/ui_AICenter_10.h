/********************************************************************************
** Form generated from reading UI file 'AICenter_10.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AICENTER_10_H
#define UI_AICENTER_10_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AICenter_10Class
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AICenter_10Class)
    {
        if (AICenter_10Class->objectName().isEmpty())
            AICenter_10Class->setObjectName(QString::fromUtf8("AICenter_10Class"));
        AICenter_10Class->resize(412, 292);
        centralWidget = new QWidget(AICenter_10Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        AICenter_10Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AICenter_10Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 412, 22));
        AICenter_10Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AICenter_10Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AICenter_10Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AICenter_10Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AICenter_10Class->setStatusBar(statusBar);

        retranslateUi(AICenter_10Class);

        QMetaObject::connectSlotsByName(AICenter_10Class);
    } // setupUi

    void retranslateUi(QMainWindow *AICenter_10Class)
    {
        AICenter_10Class->setWindowTitle(QApplication::translate("AICenter_10Class", "AICenter_10", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AICenter_10Class: public Ui_AICenter_10Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AICENTER_10_H
