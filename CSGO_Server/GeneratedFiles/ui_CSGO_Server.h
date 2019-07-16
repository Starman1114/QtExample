/********************************************************************************
** Form generated from reading UI file 'CSGO_Server.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSGO_SERVER_H
#define UI_CSGO_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CSGO_ServerClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QPushButton *checkButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CSGO_ServerClass)
    {
        if (CSGO_ServerClass->objectName().isEmpty())
            CSGO_ServerClass->setObjectName(QString::fromUtf8("CSGO_ServerClass"));
        CSGO_ServerClass->resize(259, 799);
        centralWidget = new QWidget(CSGO_ServerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        checkButton = new QPushButton(centralWidget);
        checkButton->setObjectName(QString::fromUtf8("checkButton"));

        verticalLayout->addWidget(checkButton);

        CSGO_ServerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CSGO_ServerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 259, 22));
        CSGO_ServerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CSGO_ServerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CSGO_ServerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CSGO_ServerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CSGO_ServerClass->setStatusBar(statusBar);

        retranslateUi(CSGO_ServerClass);

        QMetaObject::connectSlotsByName(CSGO_ServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *CSGO_ServerClass)
    {
        CSGO_ServerClass->setWindowTitle(QApplication::translate("CSGO_ServerClass", "CSGO_Server", nullptr));
        checkButton->setText(QApplication::translate("CSGO_ServerClass", "Check CFG", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CSGO_ServerClass: public Ui_CSGO_ServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSGO_SERVER_H
