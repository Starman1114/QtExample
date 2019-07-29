/********************************************************************************
** Form generated from reading UI file 'Device_Support.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICE_SUPPORT_H
#define UI_DEVICE_SUPPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Device_Support_Class
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget_Device;

    void setupUi(QWidget *Device_Support_Class)
    {
        if (Device_Support_Class->objectName().isEmpty())
            Device_Support_Class->setObjectName(QString::fromUtf8("Device_Support_Class"));
        Device_Support_Class->resize(363, 351);
        verticalLayout = new QVBoxLayout(Device_Support_Class);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeWidget_Device = new QTreeWidget(Device_Support_Class);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget_Device->setHeaderItem(__qtreewidgetitem);
        treeWidget_Device->setObjectName(QString::fromUtf8("treeWidget_Device"));

        verticalLayout->addWidget(treeWidget_Device);


        retranslateUi(Device_Support_Class);

        QMetaObject::connectSlotsByName(Device_Support_Class);
    } // setupUi

    void retranslateUi(QWidget *Device_Support_Class)
    {
        Device_Support_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("Device_Support_Class", "Form", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class Device_Support_Class: public Ui_Device_Support_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICE_SUPPORT_H
