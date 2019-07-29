/********************************************************************************
** Form generated from reading UI file 'Image_small.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGE_SMALL_H
#define UI_IMAGE_SMALL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Image_Small_Class
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *imageLabel;
    QLabel *nameLabel;

    void setupUi(QDialog *Image_Small_Class)
    {
        if (Image_Small_Class->objectName().isEmpty())
            Image_Small_Class->setObjectName(QString::fromUtf8("Image_Small_Class"));
        Image_Small_Class->resize(118, 138);
        Image_Small_Class->setMinimumSize(QSize(118, 120));
        verticalLayout = new QVBoxLayout(Image_Small_Class);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        imageLabel = new QLabel(Image_Small_Class);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imageLabel->sizePolicy().hasHeightForWidth());
        imageLabel->setSizePolicy(sizePolicy);
        imageLabel->setMinimumSize(QSize(100, 100));

        verticalLayout->addWidget(imageLabel);

        nameLabel = new QLabel(Image_Small_Class);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nameLabel->sizePolicy().hasHeightForWidth());
        nameLabel->setSizePolicy(sizePolicy1);
        nameLabel->setMinimumSize(QSize(0, 15));
        nameLabel->setLayoutDirection(Qt::LeftToRight);
        nameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(nameLabel);


        retranslateUi(Image_Small_Class);

        QMetaObject::connectSlotsByName(Image_Small_Class);
    } // setupUi

    void retranslateUi(QDialog *Image_Small_Class)
    {
        Image_Small_Class->setProperty("windowMySpeed", QVariant(QApplication::translate("Image_Small_Class", "Dialog", nullptr)));
        imageLabel->setText(QString());
        nameLabel->setText(QApplication::translate("Image_Small_Class", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Image_Small_Class: public Ui_Image_Small_Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGE_SMALL_H
