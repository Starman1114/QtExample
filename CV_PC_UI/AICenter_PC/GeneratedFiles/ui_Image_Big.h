/********************************************************************************
** Form generated from reading UI file 'Image_Big.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGE_BIG_H
#define UI_IMAGE_BIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Image_Big_Class
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *deleteButton;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *nameLabel;
    QPushButton *KeyBoardButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *runButton;

    void setupUi(QDialog *Image_Big_Class)
    {
        if (Image_Big_Class->objectName().isEmpty())
            Image_Big_Class->setObjectName(QString::fromUtf8("Image_Big_Class"));
        Image_Big_Class->resize(180, 240);
        Image_Big_Class->setMinimumSize(QSize(180, 240));
        verticalLayout = new QVBoxLayout(Image_Big_Class);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        deleteButton = new QPushButton(Image_Big_Class);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        horizontalLayout_2->addWidget(deleteButton);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 153, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        widget = new QWidget(Image_Big_Class);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 60));
        widget->setMaximumSize(QSize(16777215, 60));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        nameLabel = new QLabel(widget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        horizontalLayout->addWidget(nameLabel);

        KeyBoardButton = new QPushButton(widget);
        KeyBoardButton->setObjectName(QString::fromUtf8("KeyBoardButton"));

        horizontalLayout->addWidget(KeyBoardButton);

        horizontalSpacer = new QSpacerItem(42, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        runButton = new QPushButton(widget);
        runButton->setObjectName(QString::fromUtf8("runButton"));
        runButton->setMinimumSize(QSize(40, 40));
        runButton->setMaximumSize(QSize(40, 40));

        horizontalLayout->addWidget(runButton);


        verticalLayout->addWidget(widget);


        retranslateUi(Image_Big_Class);

        QMetaObject::connectSlotsByName(Image_Big_Class);
    } // setupUi

    void retranslateUi(QDialog *Image_Big_Class)
    {
        Image_Big_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("Image_Big_Class", "Dialog", nullptr)));
        deleteButton->setText(QApplication::translate("Image_Big_Class", "Delete", nullptr));
        nameLabel->setText(QApplication::translate("Image_Big_Class", "TextLabel", nullptr));
        KeyBoardButton->setText(QString());
        runButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Image_Big_Class: public Ui_Image_Big_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGE_BIG_H
