#include "tracesetdialog.h"
#include <QDebug>
#include <QHeaderView>

TraceDialog::TraceDialog( QWidget * parent /*= 0*/, Qt::WindowFlags f/* = 0*/)
     :QDialog(parent,f)
{
     setupUi(this);
     _buttonGroup = new QButtonGroup;
     _buttonGroup->addButton(numberRadio);
     _buttonGroup->addButton(stepRadio);

     valueWidget->setColumnCount(1);
     valueWidget->horizontalHeader()->hide();
     valueWidget->verticalHeader()->hide();
     connect(getButton,SIGNAL(pressed()),this,SLOT(getList()));
     connect(defaultButton,SIGNAL(pressed()),this,SLOT(toDefault()));
     connect(addButton,SIGNAL(pressed()),this,SLOT(addValue()));
     connect(removeButton,SIGNAL(pressed()),this,SLOT(removeValue()));
     connect(cleanButton,SIGNAL(pressed()),this,SLOT(cleanAllValue()));
}
  
TraceDialog::~TraceDialog()
{

}

void TraceDialog::setTraceValue(QVector<float> &valueList)
{
     valueWidget->clearContents();
     valueWidget->setRowCount(valueList.count());
     QTableWidgetItem *item;
     for(int i=0;i<valueList.count();i++)
     {
	  item = new QTableWidgetItem(QString::number(valueList[i]));
	  valueWidget->setItem(i,0,item);
     }
}

QVector<float> TraceDialog::getTraceValue()
{
     QVector<float> valueList;
     for(int i=0;i<valueWidget->rowCount();i++)
     {
	  valueList<<valueWidget->item(i,0)->text().toDouble();
     }
     return valueList;
}

void TraceDialog::setDefault(float min,float max,int number)
{
     _defMin = min;
     _defMax = max;
     _defNum = number;
}

void TraceDialog::addValue()
{
     QTableWidgetItem *item;
     valueWidget->setRowCount(valueWidget->rowCount()+1);
     valueWidget->setItem(valueWidget->rowCount(),0,item);  
     valueWidget->setCurrentItem(item);
}

void TraceDialog::removeValue()
{
     QTableWidgetItem *item = valueWidget->currentItem();
     if(item != NULL)
	  valueWidget->removeRow(item->row());
}

void TraceDialog::cleanAllValue()
{
     valueWidget->clearContents();
     valueWidget->setRowCount(0);
}

void TraceDialog::toDefault()
{
     startEdit->setText(QString::number(_defMin));
     endEdit->setText(QString::number(_defMax));
     stepEdit->setText(QString::number(_defNum));
     numberRadio->setChecked(true);
}

void TraceDialog::getList()
{
     float start = startEdit->text().toDouble();
     float end = endEdit->text().toDouble();
     QTableWidgetItem *item;
     float step;
     int c =0 ;
     valueWidget->clearContents();
     if(numberRadio->isChecked()){
	  _defNum = stepEdit->text().toInt();
	  step = (end - start)/_defNum;
     }
     else {
	  step = stepEdit->text().toDouble();
     }
     valueWidget->setRowCount((end - start)/step);
     while(start <= end)
     {
	  item = new QTableWidgetItem(QString::number(start));
	  valueWidget->setItem(c++,0,item);
	  start += step;
     }
}
