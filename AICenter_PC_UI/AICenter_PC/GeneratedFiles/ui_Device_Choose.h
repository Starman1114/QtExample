/********************************************************************************
** Form generated from reading UI file 'Device_Choose.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICE_CHOOSE_H
#define UI_DEVICE_CHOOSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Device_Choose_Class
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;

    void setupUi(QDialog *Device_Choose_Class)
    {
        if (Device_Choose_Class->objectName().isEmpty())
            Device_Choose_Class->setObjectName(QString::fromUtf8("Device_Choose_Class"));
        Device_Choose_Class->resize(178, 32);
        Device_Choose_Class->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(Device_Choose_Class);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkBox = new QCheckBox(Device_Choose_Class);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);


        retranslateUi(Device_Choose_Class);

        QMetaObject::connectSlotsByName(Device_Choose_Class);
    } // setupUi

    void retranslateUi(QDialog *Device_Choose_Class)
    {
        Device_Choose_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("Device_Choose_Class", "Dialog", nullptr)));
        checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Device_Choose_Class: public Ui_Device_Choose_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICE_CHOOSE_H
