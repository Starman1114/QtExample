/********************************************************************************
** Form generated from reading UI file 'ScreenShot.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENSHOT_H
#define UI_SCREENSHOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenShotClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *textLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLineEdit *DirNameEdit;
    QSpinBox *timeBox;
    QLabel *sizeLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ScreenShotClass)
    {
        if (ScreenShotClass->objectName().isEmpty())
            ScreenShotClass->setObjectName(QString::fromUtf8("ScreenShotClass"));
        ScreenShotClass->resize(304, 155);
        centralWidget = new QWidget(ScreenShotClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textLabel = new QLabel(centralWidget);
        textLabel->setObjectName(QString::fromUtf8("textLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textLabel->sizePolicy().hasHeightForWidth());
        textLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(textLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        DirNameEdit = new QLineEdit(centralWidget);
        DirNameEdit->setObjectName(QString::fromUtf8("DirNameEdit"));

        horizontalLayout->addWidget(DirNameEdit);

        timeBox = new QSpinBox(centralWidget);
        timeBox->setObjectName(QString::fromUtf8("timeBox"));
        timeBox->setMaximum(2000);
        timeBox->setValue(150);

        horizontalLayout->addWidget(timeBox);

        sizeLabel = new QLabel(centralWidget);
        sizeLabel->setObjectName(QString::fromUtf8("sizeLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sizeLabel->sizePolicy().hasHeightForWidth());
        sizeLabel->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(sizeLabel);


        verticalLayout->addLayout(horizontalLayout);

        ScreenShotClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ScreenShotClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 304, 22));
        ScreenShotClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ScreenShotClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ScreenShotClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ScreenShotClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ScreenShotClass->setStatusBar(statusBar);

        retranslateUi(ScreenShotClass);

        QMetaObject::connectSlotsByName(ScreenShotClass);
    } // setupUi

    void retranslateUi(QMainWindow *ScreenShotClass)
    {
        ScreenShotClass->setWindowTitle(QApplication::translate("ScreenShotClass", "ScreenShot", nullptr));
        textLabel->setText(QApplication::translate("ScreenShotClass", "TextLabel", nullptr));
        DirNameEdit->setText(QApplication::translate("ScreenShotClass", "Game", nullptr));
        sizeLabel->setText(QApplication::translate("ScreenShotClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScreenShotClass: public Ui_ScreenShotClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENSHOT_H
