/********************************************************************************
** Form generated from reading UI file 'Device_Conf.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICE_CONF_H
#define UI_DEVICE_CONF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Device_Conf_Class
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *pushButton;
    QWidget *tab_4;

    void setupUi(QWidget *Device_Conf_Class)
    {
        if (Device_Conf_Class->objectName().isEmpty())
            Device_Conf_Class->setObjectName(QString::fromUtf8("Device_Conf_Class"));
        Device_Conf_Class->resize(580, 368);
        verticalLayout_2 = new QVBoxLayout(Device_Conf_Class);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(Device_Conf_Class);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        horizontalLayout = new QHBoxLayout(tab_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(tab_3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget->addTab(tab_4, QString());

        verticalLayout_2->addWidget(tabWidget);


        retranslateUi(Device_Conf_Class);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Device_Conf_Class);
    } // setupUi

    void retranslateUi(QWidget *Device_Conf_Class)
    {
        Device_Conf_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("Device_Conf_Class", "Form", nullptr)));
        label->setText(QApplication::translate("Device_Conf_Class", "TextLabel", nullptr));
        pushButton->setText(QApplication::translate("Device_Conf_Class", "\345\220\257\345\212\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Device_Conf_Class", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("Device_Conf_Class", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Device_Conf_Class: public Ui_Device_Conf_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICE_CONF_H
