/********************************************************************************
** Form generated from reading ui file 'colormapedit.ui'
**
** Created: Fri May 15 11:19:02 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_COLORMAPEDIT_H
#define UI_COLORMAPEDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QToolButton>
#include "../dialog/colorruler.h"

QT_BEGIN_NAMESPACE

class Ui_colormapEdit
{
public:
    ColorFrame *colorFrame;
    QToolButton *toolButton_1;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;
    QToolButton *toolButton_7;
    QToolButton *toolButton_8;
    QToolButton *toolButton_9;
    QToolButton *toolButton_10;
    QToolButton *toolButton_11;
    QToolButton *toolButton_12;
    QToolButton *toolButton_13;
    QToolButton *toolButton_14;
    QToolButton *toolButton_15;
    QToolButton *toolButton_16;
    QToolButton *toolButton_17;
    QToolButton *toolButton_18;
    QToolButton *toolButton_19;
    QToolButton *toolButton_20;
    QToolButton *toolButton_21;
    QToolButton *toolButton_22;
    QToolButton *toolButton_23;
    QToolButton *toolButton_24;
    QToolButton *toolButton_25;
    QToolButton *toolButton_26;
    QToolButton *toolButton_27;
    QToolButton *toolButton_28;
    QToolButton *toolButton_29;
    QToolButton *toolButton_30;
    QToolButton *toolButton_31;
    QToolButton *toolButton_32;
    QSlider *rotateSlider;
    QLabel *label;
    QPushButton *okButton;
    QPushButton *applyButton;
    QPushButton *cancelButton;
    QLabel *label_2;
    QSlider *biasSlider;
    QLabel *label_3;
    QSlider *contrastSlider;
    QRadioButton *colorNumberButton;
    QPushButton *rotateResetButton;
    QPushButton *biasResetButton;
    QPushButton *contrastRestButton;
    QRadioButton *dynamicButton;
    QLabel *label_4;
    QComboBox *mapBox;

    void setupUi(QDialog *colormapEdit)
    {
    if (colormapEdit->objectName().isEmpty())
        colormapEdit->setObjectName(QString::fromUtf8("colormapEdit"));
    colormapEdit->resize(360, 487);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(colormapEdit->sizePolicy().hasHeightForWidth());
    colormapEdit->setSizePolicy(sizePolicy);
    colormapEdit->setMaximumSize(QSize(421, 508));
    colorFrame = new ColorFrame(colormapEdit);
    colorFrame->setObjectName(QString::fromUtf8("colorFrame"));
    colorFrame->setGeometry(QRect(20, 20, 321, 41));
    colorFrame->setFrameShape(QFrame::Box);
    colorFrame->setFrameShadow(QFrame::Sunken);
    toolButton_1 = new QToolButton(colormapEdit);
    toolButton_1->setObjectName(QString::fromUtf8("toolButton_1"));
    toolButton_1->setGeometry(QRect(20, 80, 41, 41));
    toolButton_2 = new QToolButton(colormapEdit);
    toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
    toolButton_2->setGeometry(QRect(60, 80, 41, 41));
    toolButton_3 = new QToolButton(colormapEdit);
    toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
    toolButton_3->setGeometry(QRect(100, 80, 41, 41));
    toolButton_4 = new QToolButton(colormapEdit);
    toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
    toolButton_4->setGeometry(QRect(140, 80, 41, 41));
    toolButton_5 = new QToolButton(colormapEdit);
    toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
    toolButton_5->setGeometry(QRect(180, 80, 41, 41));
    toolButton_6 = new QToolButton(colormapEdit);
    toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));
    toolButton_6->setGeometry(QRect(220, 80, 41, 41));
    toolButton_7 = new QToolButton(colormapEdit);
    toolButton_7->setObjectName(QString::fromUtf8("toolButton_7"));
    toolButton_7->setGeometry(QRect(260, 80, 41, 41));
    toolButton_8 = new QToolButton(colormapEdit);
    toolButton_8->setObjectName(QString::fromUtf8("toolButton_8"));
    toolButton_8->setGeometry(QRect(300, 80, 41, 41));
    toolButton_9 = new QToolButton(colormapEdit);
    toolButton_9->setObjectName(QString::fromUtf8("toolButton_9"));
    toolButton_9->setGeometry(QRect(20, 120, 41, 41));
    toolButton_10 = new QToolButton(colormapEdit);
    toolButton_10->setObjectName(QString::fromUtf8("toolButton_10"));
    toolButton_10->setGeometry(QRect(60, 120, 41, 41));
    toolButton_11 = new QToolButton(colormapEdit);
    toolButton_11->setObjectName(QString::fromUtf8("toolButton_11"));
    toolButton_11->setGeometry(QRect(100, 120, 41, 41));
    toolButton_12 = new QToolButton(colormapEdit);
    toolButton_12->setObjectName(QString::fromUtf8("toolButton_12"));
    toolButton_12->setGeometry(QRect(140, 120, 41, 41));
    toolButton_13 = new QToolButton(colormapEdit);
    toolButton_13->setObjectName(QString::fromUtf8("toolButton_13"));
    toolButton_13->setGeometry(QRect(180, 120, 41, 41));
    toolButton_14 = new QToolButton(colormapEdit);
    toolButton_14->setObjectName(QString::fromUtf8("toolButton_14"));
    toolButton_14->setGeometry(QRect(220, 120, 41, 41));
    toolButton_15 = new QToolButton(colormapEdit);
    toolButton_15->setObjectName(QString::fromUtf8("toolButton_15"));
    toolButton_15->setGeometry(QRect(260, 120, 41, 41));
    toolButton_16 = new QToolButton(colormapEdit);
    toolButton_16->setObjectName(QString::fromUtf8("toolButton_16"));
    toolButton_16->setGeometry(QRect(300, 120, 41, 41));
    toolButton_17 = new QToolButton(colormapEdit);
    toolButton_17->setObjectName(QString::fromUtf8("toolButton_17"));
    toolButton_17->setGeometry(QRect(20, 160, 41, 41));
    toolButton_18 = new QToolButton(colormapEdit);
    toolButton_18->setObjectName(QString::fromUtf8("toolButton_18"));
    toolButton_18->setGeometry(QRect(60, 160, 41, 41));
    toolButton_19 = new QToolButton(colormapEdit);
    toolButton_19->setObjectName(QString::fromUtf8("toolButton_19"));
    toolButton_19->setGeometry(QRect(100, 160, 41, 41));
    toolButton_20 = new QToolButton(colormapEdit);
    toolButton_20->setObjectName(QString::fromUtf8("toolButton_20"));
    toolButton_20->setGeometry(QRect(140, 160, 41, 41));
    toolButton_21 = new QToolButton(colormapEdit);
    toolButton_21->setObjectName(QString::fromUtf8("toolButton_21"));
    toolButton_21->setGeometry(QRect(180, 160, 41, 41));
    toolButton_22 = new QToolButton(colormapEdit);
    toolButton_22->setObjectName(QString::fromUtf8("toolButton_22"));
    toolButton_22->setGeometry(QRect(220, 160, 41, 41));
    toolButton_23 = new QToolButton(colormapEdit);
    toolButton_23->setObjectName(QString::fromUtf8("toolButton_23"));
    toolButton_23->setGeometry(QRect(260, 160, 41, 41));
    toolButton_24 = new QToolButton(colormapEdit);
    toolButton_24->setObjectName(QString::fromUtf8("toolButton_24"));
    toolButton_24->setGeometry(QRect(300, 160, 41, 41));
    toolButton_25 = new QToolButton(colormapEdit);
    toolButton_25->setObjectName(QString::fromUtf8("toolButton_25"));
    toolButton_25->setGeometry(QRect(20, 200, 41, 41));
    toolButton_26 = new QToolButton(colormapEdit);
    toolButton_26->setObjectName(QString::fromUtf8("toolButton_26"));
    toolButton_26->setGeometry(QRect(60, 200, 41, 41));
    toolButton_27 = new QToolButton(colormapEdit);
    toolButton_27->setObjectName(QString::fromUtf8("toolButton_27"));
    toolButton_27->setGeometry(QRect(100, 200, 41, 41));
    toolButton_28 = new QToolButton(colormapEdit);
    toolButton_28->setObjectName(QString::fromUtf8("toolButton_28"));
    toolButton_28->setGeometry(QRect(140, 200, 41, 41));
    toolButton_29 = new QToolButton(colormapEdit);
    toolButton_29->setObjectName(QString::fromUtf8("toolButton_29"));
    toolButton_29->setGeometry(QRect(180, 200, 41, 41));
    toolButton_30 = new QToolButton(colormapEdit);
    toolButton_30->setObjectName(QString::fromUtf8("toolButton_30"));
    toolButton_30->setGeometry(QRect(220, 200, 41, 41));
    toolButton_31 = new QToolButton(colormapEdit);
    toolButton_31->setObjectName(QString::fromUtf8("toolButton_31"));
    toolButton_31->setGeometry(QRect(260, 200, 41, 41));
    toolButton_32 = new QToolButton(colormapEdit);
    toolButton_32->setObjectName(QString::fromUtf8("toolButton_32"));
    toolButton_32->setGeometry(QRect(300, 200, 41, 41));
    rotateSlider = new QSlider(colormapEdit);
    rotateSlider->setObjectName(QString::fromUtf8("rotateSlider"));
    rotateSlider->setGeometry(QRect(80, 336, 224, 16));
    rotateSlider->setOrientation(Qt::Horizontal);
    label = new QLabel(colormapEdit);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(18, 332, 56, 25));
    QFont font;
    font.setPointSize(10);
    font.setBold(false);
    font.setWeight(50);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    okButton = new QPushButton(colormapEdit);
    okButton->setObjectName(QString::fromUtf8("okButton"));
    okButton->setGeometry(QRect(30, 440, 75, 23));
    applyButton = new QPushButton(colormapEdit);
    applyButton->setObjectName(QString::fromUtf8("applyButton"));
    applyButton->setGeometry(QRect(140, 440, 75, 23));
    cancelButton = new QPushButton(colormapEdit);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
    cancelButton->setGeometry(QRect(260, 440, 75, 23));
    label_2 = new QLabel(colormapEdit);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(18, 366, 56, 25));
    QFont font1;
    font1.setPointSize(10);
    label_2->setFont(font1);
    label_2->setAlignment(Qt::AlignCenter);
    biasSlider = new QSlider(colormapEdit);
    biasSlider->setObjectName(QString::fromUtf8("biasSlider"));
    biasSlider->setGeometry(QRect(80, 370, 224, 16));
    biasSlider->setOrientation(Qt::Horizontal);
    label_3 = new QLabel(colormapEdit);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(18, 400, 56, 25));
    label_3->setFont(font1);
    label_3->setAlignment(Qt::AlignCenter);
    contrastSlider = new QSlider(colormapEdit);
    contrastSlider->setObjectName(QString::fromUtf8("contrastSlider"));
    contrastSlider->setGeometry(QRect(80, 404, 224, 16));
    contrastSlider->setOrientation(Qt::Horizontal);
    colorNumberButton = new QRadioButton(colormapEdit);
    colorNumberButton->setObjectName(QString::fromUtf8("colorNumberButton"));
    colorNumberButton->setGeometry(QRect(20, 310, 131, 18));
    rotateResetButton = new QPushButton(colormapEdit);
    rotateResetButton->setObjectName(QString::fromUtf8("rotateResetButton"));
    rotateResetButton->setGeometry(QRect(310, 332, 41, 25));
    biasResetButton = new QPushButton(colormapEdit);
    biasResetButton->setObjectName(QString::fromUtf8("biasResetButton"));
    biasResetButton->setGeometry(QRect(310, 366, 41, 25));
    contrastRestButton = new QPushButton(colormapEdit);
    contrastRestButton->setObjectName(QString::fromUtf8("contrastRestButton"));
    contrastRestButton->setGeometry(QRect(310, 400, 41, 25));
    dynamicButton = new QRadioButton(colormapEdit);
    dynamicButton->setObjectName(QString::fromUtf8("dynamicButton"));
    dynamicButton->setGeometry(QRect(20, 290, 121, 18));
    dynamicButton->setAutoExclusive(false);
    label_4 = new QLabel(colormapEdit);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(20, 260, 71, 16));
    mapBox = new QComboBox(colormapEdit);
    mapBox->setObjectName(QString::fromUtf8("mapBox"));
    mapBox->setGeometry(QRect(90, 250, 101, 31));

    retranslateUi(colormapEdit);

    QMetaObject::connectSlotsByName(colormapEdit);
    } // setupUi

    void retranslateUi(QDialog *colormapEdit)
    {
    colormapEdit->setWindowTitle(QApplication::translate("colormapEdit", "colormapedit", 0, QApplication::UnicodeUTF8));
    toolButton_1->setText(QString());
    toolButton_2->setText(QString());
    toolButton_3->setText(QString());
    toolButton_4->setText(QString());
    toolButton_5->setText(QString());
    toolButton_6->setText(QString());
    toolButton_7->setText(QString());
    toolButton_8->setText(QString());
    toolButton_9->setText(QString());
    toolButton_10->setText(QString());
    toolButton_11->setText(QString());
    toolButton_12->setText(QString());
    toolButton_13->setText(QString());
    toolButton_14->setText(QString());
    toolButton_15->setText(QString());
    toolButton_16->setText(QString());
    toolButton_17->setText(QString());
    toolButton_18->setText(QString());
    toolButton_19->setText(QString());
    toolButton_20->setText(QString());
    toolButton_21->setText(QString());
    toolButton_22->setText(QString());
    toolButton_23->setText(QString());
    toolButton_24->setText(QString());
    toolButton_25->setText(QString());
    toolButton_26->setText(QString());
    toolButton_27->setText(QString());
    toolButton_28->setText(QString());
    toolButton_29->setText(QString());
    toolButton_30->setText(QString());
    toolButton_31->setText(QString());
    toolButton_32->setText(QString());
    label->setText(QApplication::translate("colormapEdit", "Rotate", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("colormapEdit", "OK", 0, QApplication::UnicodeUTF8));
    applyButton->setText(QApplication::translate("colormapEdit", "Apply", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("colormapEdit", "Cancel", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("colormapEdit", "Bias", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("colormapEdit", "Contrast", 0, QApplication::UnicodeUTF8));
    colorNumberButton->setText(QApplication::translate("colormapEdit", "Show Color Numbers", 0, QApplication::UnicodeUTF8));
    rotateResetButton->setText(QApplication::translate("colormapEdit", "Reset", 0, QApplication::UnicodeUTF8));
    biasResetButton->setText(QApplication::translate("colormapEdit", "Reset", 0, QApplication::UnicodeUTF8));
    contrastRestButton->setText(QApplication::translate("colormapEdit", "Reset", 0, QApplication::UnicodeUTF8));
    dynamicButton->setText(QApplication::translate("colormapEdit", "Dynamic Adjust", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("colormapEdit", "Map Color:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(colormapEdit);
    } // retranslateUi

};

namespace Ui {
    class colormapEdit: public Ui_colormapEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORMAPEDIT_H
