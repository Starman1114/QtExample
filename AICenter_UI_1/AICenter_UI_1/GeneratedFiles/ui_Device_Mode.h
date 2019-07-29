/********************************************************************************
** Form generated from reading UI file 'Device_Mode.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICE_MODE_H
#define UI_DEVICE_MODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Device_Mode_Class
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QListWidget *imageList;
    QLabel *imageLabel;

    void setupUi(QWidget *Device_Mode_Class)
    {
        if (Device_Mode_Class->objectName().isEmpty())
            Device_Mode_Class->setObjectName(QString::fromUtf8("Device_Mode_Class"));
        Device_Mode_Class->resize(412, 197);
        verticalLayout = new QVBoxLayout(Device_Mode_Class);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(Device_Mode_Class);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        imageList = new QListWidget(Device_Mode_Class);
        imageList->setObjectName(QString::fromUtf8("imageList"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imageList->sizePolicy().hasHeightForWidth());
        imageList->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(imageList);

        imageLabel = new QLabel(Device_Mode_Class);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));

        horizontalLayout->addWidget(imageLabel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Device_Mode_Class);

        QMetaObject::connectSlotsByName(Device_Mode_Class);
    } // setupUi

    void retranslateUi(QWidget *Device_Mode_Class)
    {
        Device_Mode_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("Device_Mode_Class", "Form", nullptr)));
        label->setText(QApplication::translate("Device_Mode_Class", "TextLabel", nullptr));
        imageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Device_Mode_Class: public Ui_Device_Mode_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICE_MODE_H
