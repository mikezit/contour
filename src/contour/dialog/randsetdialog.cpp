#include "randsetdialog.h"
#include <QDoubleValidator>
#include <QIntValidator>

RandSetDialog::RandSetDialog ( QWidget * parent, Qt::WindowFlags f )
     :QDialog(parent,f)
{
     setupUi(this);
     QDoubleValidator  *rangeValidator = new QDoubleValidator(this);
     QIntValidator *intValidator = new QIntValidator(this);
     minXEdit->setValidator(rangeValidator);
     maxXEdit->setValidator(rangeValidator);  
     minYEdit->setValidator(rangeValidator);
     maxYEdit->setValidator(rangeValidator);
     minZEdit->setValidator(rangeValidator);
     maxZEdit->setValidator(rangeValidator);
     colsEdit->setValidator(intValidator);
     rowsEdit->setValidator(intValidator);
     numberEdit->setValidator(intValidator);

}

RandSetDialog::~RandSetDialog()
{

}

void RandSetDialog::initialInfo(CGridDataInfo info,int number)
{
     minXEdit->setText(QString::number(info.xMin));
     maxXEdit->setText(QString::number(info.xMax));
     minYEdit->setText(QString::number(info.yMin));
     maxYEdit->setText(QString::number(info.yMax));
     minZEdit->setText(QString::number(info.zMin));
     maxZEdit->setText(QString::number(info.zMax));
     colsEdit->setText(QString::number(info.cols));
     rowsEdit->setText(QString::number(info.rows));
     numberEdit->setText(QString::number(number));
}

void RandSetDialog::getInfo(CGridDataInfo &info,int &number) 
{
     info.xMin = minXEdit->text().toDouble();
     info.xMax = maxXEdit->text().toDouble();
     info.yMin = minYEdit->text().toDouble();
     info.yMax = maxYEdit->text().toDouble();
     info.zMin = minZEdit->text().toDouble();
     info.zMax = maxZEdit->text().toDouble();
     info.rows = rowsEdit->text().toInt();
     info.cols = colsEdit->text().toInt();
     number = numberEdit->text().toInt();
}
