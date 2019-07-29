/********************************************************************************
** Form generated from reading UI file 'Mode_HotKey.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODE_HOTKEY_H
#define UI_MODE_HOTKEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mode_HotKey_Class
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QCheckBox *checkBox;

    void setupUi(QWidget *Mode_HotKey_Class)
    {
        if (Mode_HotKey_Class->objectName().isEmpty())
            Mode_HotKey_Class->setObjectName(QString::fromUtf8("Mode_HotKey_Class"));
        Mode_HotKey_Class->resize(230, 28);
        verticalLayout = new QVBoxLayout(Mode_HotKey_Class);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Mode_HotKey_Class);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(Mode_HotKey_Class);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_2);

        pushButton = new QPushButton(Mode_HotKey_Class);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushButton);

        checkBox = new QCheckBox(Mode_HotKey_Class);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout->addWidget(checkBox);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Mode_HotKey_Class);

        QMetaObject::connectSlotsByName(Mode_HotKey_Class);
    } // setupUi

    void retranslateUi(QWidget *Mode_HotKey_Class)
    {
        Mode_HotKey_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("Mode_HotKey_Class", "Form", nullptr)));
        label->setText(QApplication::translate("Mode_HotKey_Class", "TextLabel", nullptr));
        label_2->setText(QApplication::translate("Mode_HotKey_Class", "\347\203\255\351\224\256\350\256\276\347\275\256\344\270\272\357\274\232", nullptr));
        pushButton->setText(QString());
        checkBox->setText(QApplication::translate("Mode_HotKey_Class", "\345\274\200\345\220\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mode_HotKey_Class: public Ui_Mode_HotKey_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODE_HOTKEY_H
