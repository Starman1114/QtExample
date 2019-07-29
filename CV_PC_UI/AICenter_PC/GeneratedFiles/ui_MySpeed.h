/********************************************************************************
** Form generated from reading UI file 'MySpeed.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSPEED_H
#define UI_MYSPEED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MySpeed_Class
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *imageList;

    void setupUi(QDialog *MySpeed_Class)
    {
        if (MySpeed_Class->objectName().isEmpty())
            MySpeed_Class->setObjectName(QString::fromUtf8("MySpeed_Class"));
        MySpeed_Class->resize(228, 168);
        verticalLayout = new QVBoxLayout(MySpeed_Class);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        imageList = new QListWidget(MySpeed_Class);
        imageList->setObjectName(QString::fromUtf8("imageList"));

        verticalLayout->addWidget(imageList);


        retranslateUi(MySpeed_Class);

        QMetaObject::connectSlotsByName(MySpeed_Class);
    } // setupUi

    void retranslateUi(QDialog *MySpeed_Class)
    {
        MySpeed_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("MySpeed_Class", "Dialog", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class MySpeed_Class: public Ui_MySpeed_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSPEED_H
