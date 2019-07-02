/********************************************************************************
** Form generated from reading UI file 'AddLabel.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDLABEL_H
#define UI_ADDLABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_AddLabel_Class
{
public:
    QHBoxLayout *horizontalLayout;
    QSpinBox *xBox;
    QSpinBox *yBox;
    QSpinBox *wBox;
    QSpinBox *hBox;

    void setupUi(QDialog *AddLabel_Class)
    {
        if (AddLabel_Class->objectName().isEmpty())
            AddLabel_Class->setObjectName(QString::fromUtf8("AddLabel_Class"));
        AddLabel_Class->resize(282, 46);
        horizontalLayout = new QHBoxLayout(AddLabel_Class);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        xBox = new QSpinBox(AddLabel_Class);
        xBox->setObjectName(QString::fromUtf8("xBox"));
        xBox->setMaximum(10000);

        horizontalLayout->addWidget(xBox);

        yBox = new QSpinBox(AddLabel_Class);
        yBox->setObjectName(QString::fromUtf8("yBox"));
        yBox->setMaximum(10000);

        horizontalLayout->addWidget(yBox);

        wBox = new QSpinBox(AddLabel_Class);
        wBox->setObjectName(QString::fromUtf8("wBox"));
        wBox->setMaximum(10000);

        horizontalLayout->addWidget(wBox);

        hBox = new QSpinBox(AddLabel_Class);
        hBox->setObjectName(QString::fromUtf8("hBox"));
        hBox->setMaximum(10000);

        horizontalLayout->addWidget(hBox);


        retranslateUi(AddLabel_Class);

        QMetaObject::connectSlotsByName(AddLabel_Class);
    } // setupUi

    void retranslateUi(QDialog *AddLabel_Class)
    {
        AddLabel_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("AddLabel_Class", "Dialog", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class AddLabel_Class: public Ui_AddLabel_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDLABEL_H
