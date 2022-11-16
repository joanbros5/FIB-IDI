/********************************************************************************
** Form generated from reading UI file 'Form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyQLCDNumber.h"
#include "MyQLabel.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_5;
    MyQLabel *label;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    MyQLCDNumber *lcdNumber_2;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    MyQLCDNumber *lcdNumber_3;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    MyQLCDNumber *lcdNumber_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_9;
    MyQLCDNumber *lcdNumber;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(432, 422);
        gridLayout = new QGridLayout(MyForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label = new MyQLabel(MyForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("background-color: green;"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButton_2 = new QPushButton(MyForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_7->addWidget(pushButton_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(MyForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        lcdNumber_2 = new MyQLCDNumber(MyForm);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));

        horizontalLayout_4->addWidget(lcdNumber_2);


        horizontalLayout_7->addLayout(horizontalLayout_4);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        pushButton_3 = new QPushButton(MyForm);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_8->addWidget(pushButton_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(MyForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        lcdNumber_3 = new MyQLCDNumber(MyForm);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));

        horizontalLayout_5->addWidget(lcdNumber_3);


        horizontalLayout_8->addLayout(horizontalLayout_5);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        pushButton_4 = new QPushButton(MyForm);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_9->addWidget(pushButton_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(MyForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        lcdNumber_4 = new MyQLCDNumber(MyForm);
        lcdNumber_4->setObjectName(QString::fromUtf8("lcdNumber_4"));

        horizontalLayout_6->addWidget(lcdNumber_4);


        horizontalLayout_9->addLayout(horizontalLayout_6);


        verticalLayout_4->addLayout(horizontalLayout_9);


        verticalLayout_5->addLayout(verticalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_9 = new QLabel(MyForm);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 0);"));

        verticalLayout_3->addWidget(label_9);

        lcdNumber = new MyQLCDNumber(MyForm);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));

        verticalLayout_3->addWidget(lcdNumber);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButton = new QRadioButton(MyForm);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setChecked(true);

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(MyForm);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);


        horizontalLayout_3->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_5->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_5, 0, 0, 1, 1);


        retranslateUi(MyForm);
        QObject::connect(pushButton, SIGNAL(pressed()), MyForm, SLOT(close()));
        QObject::connect(radioButton, SIGNAL(pressed()), label, SLOT(abre()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), label, SLOT(cierra()));
        QObject::connect(pushButton_2, SIGNAL(pressed()), lcdNumber_2, SLOT(suma1()));
        QObject::connect(pushButton_3, SIGNAL(pressed()), lcdNumber_3, SLOT(suma1()));
        QObject::connect(pushButton_4, SIGNAL(pressed()), lcdNumber_4, SLOT(suma1()));
        QObject::connect(pushButton_2, SIGNAL(pressed()), lcdNumber, SLOT(suma1()));
        QObject::connect(pushButton_3, SIGNAL(pressed()), lcdNumber, SLOT(suma1()));
        QObject::connect(pushButton_4, SIGNAL(pressed()), lcdNumber, SLOT(suma4()));
        QObject::connect(radioButton, SIGNAL(clicked()), lcdNumber_2, SLOT(abre()));
        QObject::connect(radioButton, SIGNAL(clicked()), lcdNumber_3, SLOT(abre()));
        QObject::connect(radioButton, SIGNAL(clicked()), lcdNumber_4, SLOT(abre()));
        QObject::connect(radioButton, SIGNAL(clicked()), lcdNumber, SLOT(abre()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), lcdNumber_2, SLOT(cierra()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), lcdNumber_3, SLOT(cierra()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), lcdNumber_4, SLOT(cierra()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), lcdNumber, SLOT(cierra()));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("MyForm", "OPEN", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MyForm", "COCHE", nullptr));
        label_3->setText(QCoreApplication::translate("MyForm", "Coches:", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MyForm", "MOTO", nullptr));
        label_4->setText(QCoreApplication::translate("MyForm", "Motos:", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MyForm", "CAMI\303\223N", nullptr));
        label_5->setText(QCoreApplication::translate("MyForm", "Camiones:", nullptr));
        label_9->setText(QCoreApplication::translate("MyForm", "$$$$$$$$", nullptr));
        radioButton->setText(QCoreApplication::translate("MyForm", "ABRE HOSTIA", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MyForm", "CIERRA JODER", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "QuitaBicho", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
