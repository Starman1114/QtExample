/********************************************************************************
** Form generated from reading UI file 'Mode_Drop.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODE_DROP_H
#define UI_MODE_DROP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mode_Drop_Class
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QCheckBox *checkBox;

    void setupUi(QWidget *Mode_Drop_Class)
    {
        if (Mode_Drop_Class->objectName().isEmpty())
            Mode_Drop_Class->setObjectName(QString::fromUtf8("Mode_Drop_Class"));
        Mode_Drop_Class->resize(181, 26);
        verticalLayout = new QVBoxLayout(Mode_Drop_Class);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Mode_Drop_Class);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(Mode_Drop_Class);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(comboBox);

        checkBox = new QCheckBox(Mode_Drop_Class);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout->addWidget(checkBox);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Mode_Drop_Class);

        QMetaObject::connectSlotsByName(Mode_Drop_Class);
    } // setupUi

    void retranslateUi(QWidget *Mode_Drop_Class)
    {
        Mode_Drop_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("Mode_Drop_Class", "Form", nullptr)));
        label->setText(QApplication::translate("Mode_Drop_Class", "TextLabel", nullptr));
        checkBox->setText(QApplication::translate("Mode_Drop_Class", "\345\274\200\345\220\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mode_Drop_Class: public Ui_Mode_Drop_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODE_DROP_H
