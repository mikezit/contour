/********************************************************************************
** Form generated from reading UI file 'randset.ui'
**
** Created: Sat Mar 5 23:35:56 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANDSET_H
#define UI_RANDSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RandSet
{
public:
    QGroupBox *groupBox;
    QLineEdit *maxXEdit;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *minXEdit;
    QGroupBox *groupBox_2;
    QLineEdit *maxYEdit;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *minYEdit;
    QGroupBox *groupBox_3;
    QLineEdit *maxZEdit;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *minZEdit;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QLineEdit *rowsEdit;
    QLabel *label_8;
    QLineEdit *colsEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QLineEdit *numberEdit;

    void setupUi(QDialog *RandSet)
    {
        if (RandSet->objectName().isEmpty())
            RandSet->setObjectName(QString::fromUtf8("RandSet"));
        RandSet->resize(441, 306);
        groupBox = new QGroupBox(RandSet);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 201, 91));
        maxXEdit = new QLineEdit(groupBox);
        maxXEdit->setObjectName(QString::fromUtf8("maxXEdit"));
        maxXEdit->setGeometry(QRect(60, 50, 113, 25));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 59, 19));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 59, 19));
        minXEdit = new QLineEdit(groupBox);
        minXEdit->setObjectName(QString::fromUtf8("minXEdit"));
        minXEdit->setGeometry(QRect(60, 20, 113, 25));
        groupBox_2 = new QGroupBox(RandSet);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 100, 201, 91));
        maxYEdit = new QLineEdit(groupBox_2);
        maxYEdit->setObjectName(QString::fromUtf8("maxYEdit"));
        maxYEdit->setGeometry(QRect(60, 50, 113, 25));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 20, 59, 19));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 50, 59, 19));
        minYEdit = new QLineEdit(groupBox_2);
        minYEdit->setObjectName(QString::fromUtf8("minYEdit"));
        minYEdit->setGeometry(QRect(60, 20, 113, 25));
        groupBox_3 = new QGroupBox(RandSet);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 200, 201, 91));
        maxZEdit = new QLineEdit(groupBox_3);
        maxZEdit->setObjectName(QString::fromUtf8("maxZEdit"));
        maxZEdit->setGeometry(QRect(60, 50, 113, 25));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 20, 59, 19));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 50, 59, 19));
        minZEdit = new QLineEdit(groupBox_3);
        minZEdit->setObjectName(QString::fromUtf8("minZEdit"));
        minZEdit->setGeometry(QRect(60, 20, 113, 25));
        layoutWidget = new QWidget(RandSet);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(250, 250, 171, 33));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        groupBox_4 = new QGroupBox(RandSet);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(260, 20, 131, 81));
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 0, 1, 2);

        rowsEdit = new QLineEdit(groupBox_4);
        rowsEdit->setObjectName(QString::fromUtf8("rowsEdit"));

        gridLayout->addWidget(rowsEdit, 0, 2, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        colsEdit = new QLineEdit(groupBox_4);
        colsEdit->setObjectName(QString::fromUtf8("colsEdit"));

        gridLayout->addWidget(colsEdit, 1, 2, 1, 1);

        widget = new QWidget(RandSet);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(260, 120, 111, 27));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_2->addWidget(label_9);

        numberEdit = new QLineEdit(widget);
        numberEdit->setObjectName(QString::fromUtf8("numberEdit"));

        horizontalLayout_2->addWidget(numberEdit);

        label_9->raise();
        numberEdit->raise();

        retranslateUi(RandSet);
        QObject::connect(okButton, SIGNAL(clicked()), RandSet, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), RandSet, SLOT(reject()));

        QMetaObject::connectSlotsByName(RandSet);
    } // setupUi

    void retranslateUi(QDialog *RandSet)
    {
        RandSet->setWindowTitle(QApplication::translate("RandSet", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("RandSet", "X", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RandSet", "minX", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RandSet", "maxX", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("RandSet", "Y", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RandSet", "minY", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("RandSet", "maxY", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("RandSet", "Z", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("RandSet", "minZ", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("RandSet", "maxZ", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("RandSet", "Ok", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("RandSet", "Cancel", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QString());
        label_7->setText(QApplication::translate("RandSet", "Rows", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("RandSet", "Cols", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("RandSet", "Number", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RandSet: public Ui_RandSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANDSET_H
