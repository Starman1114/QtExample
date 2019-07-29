/********************************************************************************
** Form generated from reading UI file 'TitleBar.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TITLEBAR_H
#define UI_TITLEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TitleBar
{
public:
    QHBoxLayout *horizontalLayout_2;
    QLabel *lab_Ico;
    QVBoxLayout *verticalLayout;
    QLabel *lab_Title;
    QPushButton *loginButton;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnMenu;
    QPushButton *btnMenu_Min;
    QPushButton *btnMenu_Close;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *TitleBar)
    {
        if (TitleBar->objectName().isEmpty())
            TitleBar->setObjectName(QString::fromUtf8("TitleBar"));
        TitleBar->resize(466, 68);
        QFont font;
        font.setPointSize(8);
        TitleBar->setFont(font);
        horizontalLayout_2 = new QHBoxLayout(TitleBar);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lab_Ico = new QLabel(TitleBar);
        lab_Ico->setObjectName(QString::fromUtf8("lab_Ico"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lab_Ico->sizePolicy().hasHeightForWidth());
        lab_Ico->setSizePolicy(sizePolicy);
        lab_Ico->setMinimumSize(QSize(80, 50));
        lab_Ico->setMaximumSize(QSize(80, 50));
        lab_Ico->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lab_Ico);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 10, -1, 10);
        lab_Title = new QLabel(TitleBar);
        lab_Title->setObjectName(QString::fromUtf8("lab_Title"));
        QFont font1;
        font1.setPointSize(15);
        lab_Title->setFont(font1);

        verticalLayout->addWidget(lab_Title);

        loginButton = new QPushButton(TitleBar);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));

        verticalLayout->addWidget(loginButton);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(185, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnMenu = new QPushButton(TitleBar);
        btnMenu->setObjectName(QString::fromUtf8("btnMenu"));
        sizePolicy.setHeightForWidth(btnMenu->sizePolicy().hasHeightForWidth());
        btnMenu->setSizePolicy(sizePolicy);
        btnMenu->setMinimumSize(QSize(35, 35));
        btnMenu->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(btnMenu);

        btnMenu_Min = new QPushButton(TitleBar);
        btnMenu_Min->setObjectName(QString::fromUtf8("btnMenu_Min"));
        sizePolicy.setHeightForWidth(btnMenu_Min->sizePolicy().hasHeightForWidth());
        btnMenu_Min->setSizePolicy(sizePolicy);
        btnMenu_Min->setMinimumSize(QSize(35, 35));
        btnMenu_Min->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Min->setFocusPolicy(Qt::NoFocus);
        btnMenu_Min->setFlat(false);

        horizontalLayout->addWidget(btnMenu_Min);

        btnMenu_Close = new QPushButton(TitleBar);
        btnMenu_Close->setObjectName(QString::fromUtf8("btnMenu_Close"));
        sizePolicy.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
        btnMenu_Close->setSizePolicy(sizePolicy);
        btnMenu_Close->setMinimumSize(QSize(35, 35));
        btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Close->setFocusPolicy(Qt::NoFocus);
        btnMenu_Close->setFlat(false);

        horizontalLayout->addWidget(btnMenu_Close);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_2);


        retranslateUi(TitleBar);

        QMetaObject::connectSlotsByName(TitleBar);
    } // setupUi

    void retranslateUi(QWidget *TitleBar)
    {
        TitleBar->setWindowTitle(QApplication::translate("TitleBar", "Form", nullptr));
        lab_Ico->setText(QString());
        lab_Title->setText(QApplication::translate("TitleBar", "Wireless36", nullptr));
        loginButton->setText(QApplication::translate("TitleBar", "Login", nullptr));
#ifndef QT_NO_TOOLTIP
        btnMenu->setToolTip(QApplication::translate("TitleBar", "Setting", nullptr));
#endif // QT_NO_TOOLTIP
        btnMenu->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Min->setToolTip(QApplication::translate("TitleBar", "Min", nullptr));
#endif // QT_NO_TOOLTIP
        btnMenu_Min->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Close->setToolTip(QApplication::translate("TitleBar", "Close", nullptr));
#endif // QT_NO_TOOLTIP
        btnMenu_Close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TitleBar: public Ui_TitleBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TITLEBAR_H
