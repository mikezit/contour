/********************************************************************************
** Form generated from reading UI file 'trace.ui'
**
** Created: Sat Mar 5 23:35:56 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACE_H
#define UI_TRACE_H

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
#include <QtGui/QRadioButton>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TracingDialog
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *startEdit;
    QLabel *label_2;
    QLineEdit *endEdit;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *numberRadio;
    QRadioButton *stepRadio;
    QLineEdit *stepEdit;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *getButton;
    QPushButton *defaultButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QTableWidget *valueWidget;
    QPushButton *cleanButton;

    void setupUi(QDialog *TracingDialog)
    {
        if (TracingDialog->objectName().isEmpty())
            TracingDialog->setObjectName(QString::fromUtf8("TracingDialog"));
        TracingDialog->resize(402, 346);
        groupBox = new QGroupBox(TracingDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(140, 10, 241, 181));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        startEdit = new QLineEdit(groupBox);
        startEdit->setObjectName(QString::fromUtf8("startEdit"));

        gridLayout->addWidget(startEdit, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        endEdit = new QLineEdit(groupBox);
        endEdit->setObjectName(QString::fromUtf8("endEdit"));

        gridLayout->addWidget(endEdit, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        numberRadio = new QRadioButton(groupBox_2);
        numberRadio->setObjectName(QString::fromUtf8("numberRadio"));

        verticalLayout->addWidget(numberRadio);

        stepRadio = new QRadioButton(groupBox_2);
        stepRadio->setObjectName(QString::fromUtf8("stepRadio"));

        verticalLayout->addWidget(stepRadio);


        horizontalLayout_2->addLayout(verticalLayout);

        stepEdit = new QLineEdit(groupBox_2);
        stepEdit->setObjectName(QString::fromUtf8("stepEdit"));

        horizontalLayout_2->addWidget(stepEdit);


        gridLayout->addWidget(groupBox_2, 2, 0, 1, 2);

        addButton = new QPushButton(TracingDialog);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(130, 240, 71, 29));
        removeButton = new QPushButton(TracingDialog);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(130, 270, 71, 29));
        getButton = new QPushButton(TracingDialog);
        getButton->setObjectName(QString::fromUtf8("getButton"));
        getButton->setGeometry(QRect(250, 200, 61, 29));
        defaultButton = new QPushButton(TracingDialog);
        defaultButton->setObjectName(QString::fromUtf8("defaultButton"));
        defaultButton->setGeometry(QRect(320, 200, 61, 29));
        layoutWidget = new QWidget(TracingDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(220, 300, 162, 33));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        valueWidget = new QTableWidget(TracingDialog);
        valueWidget->setObjectName(QString::fromUtf8("valueWidget"));
        valueWidget->setGeometry(QRect(10, 10, 111, 321));
        cleanButton = new QPushButton(TracingDialog);
        cleanButton->setObjectName(QString::fromUtf8("cleanButton"));
        cleanButton->setGeometry(QRect(130, 300, 71, 29));

        retranslateUi(TracingDialog);
        QObject::connect(okButton, SIGNAL(pressed()), TracingDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(pressed()), TracingDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TracingDialog);
    } // setupUi

    void retranslateUi(QDialog *TracingDialog)
    {
        TracingDialog->setWindowTitle(QApplication::translate("TracingDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TracingDialog", "Auto", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TracingDialog", "start value", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TracingDialog", "end value", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        numberRadio->setText(QApplication::translate("TracingDialog", "number", 0, QApplication::UnicodeUTF8));
        stepRadio->setText(QApplication::translate("TracingDialog", "step", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("TracingDialog", "Add", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("TracingDialog", "Remove", 0, QApplication::UnicodeUTF8));
        getButton->setText(QApplication::translate("TracingDialog", "Get", 0, QApplication::UnicodeUTF8));
        defaultButton->setText(QApplication::translate("TracingDialog", "Default", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("TracingDialog", "Ok", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("TracingDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        cleanButton->setText(QApplication::translate("TracingDialog", "Clean All", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TracingDialog: public Ui_TracingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACE_H
