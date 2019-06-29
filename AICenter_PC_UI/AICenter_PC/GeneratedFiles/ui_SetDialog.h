/********************************************************************************
** Form generated from reading UI file 'SetDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETDIALOG_H
#define UI_SETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SetDialog_Class
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *imageList;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *flashButton;
    QPushButton *saveButton;

    void setupUi(QDialog *SetDialog_Class)
    {
        if (SetDialog_Class->objectName().isEmpty())
            SetDialog_Class->setObjectName(QString::fromUtf8("SetDialog_Class"));
        SetDialog_Class->resize(210, 214);
        verticalLayout = new QVBoxLayout(SetDialog_Class);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 5);
        imageList = new QListWidget(SetDialog_Class);
        imageList->setObjectName(QString::fromUtf8("imageList"));

        verticalLayout->addWidget(imageList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        flashButton = new QPushButton(SetDialog_Class);
        flashButton->setObjectName(QString::fromUtf8("flashButton"));
        flashButton->setMinimumSize(QSize(30, 30));
        flashButton->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(flashButton);

        saveButton = new QPushButton(SetDialog_Class);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(saveButton->sizePolicy().hasHeightForWidth());
        saveButton->setSizePolicy(sizePolicy);
        saveButton->setMinimumSize(QSize(0, 30));
        saveButton->setMaximumSize(QSize(50, 30));
        QFont font;
        font.setPointSize(14);
        saveButton->setFont(font);

        horizontalLayout->addWidget(saveButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SetDialog_Class);

        QMetaObject::connectSlotsByName(SetDialog_Class);
    } // setupUi

    void retranslateUi(QDialog *SetDialog_Class)
    {
        SetDialog_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("SetDialog_Class", "Dialog", nullptr)));
        flashButton->setText(QString());
        saveButton->setText(QApplication::translate("SetDialog_Class", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetDialog_Class: public Ui_SetDialog_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETDIALOG_H
