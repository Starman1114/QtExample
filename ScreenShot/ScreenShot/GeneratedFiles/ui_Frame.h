/********************************************************************************
** Form generated from reading UI file 'Frame.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAME_H
#define UI_FRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Frame_Class
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;

    void setupUi(QDialog *Frame_Class)
    {
        if (Frame_Class->objectName().isEmpty())
            Frame_Class->setObjectName(QString::fromUtf8("Frame_Class"));
        Frame_Class->resize(228, 168);
        verticalLayout = new QVBoxLayout(Frame_Class);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(Frame_Class);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);


        retranslateUi(Frame_Class);

        QMetaObject::connectSlotsByName(Frame_Class);
    } // setupUi

    void retranslateUi(QDialog *Frame_Class)
    {
        Frame_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("Frame_Class", "Dialog", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class Frame_Class: public Ui_Frame_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAME_H
