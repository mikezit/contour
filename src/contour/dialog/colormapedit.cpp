#include "colormapedit.h"
#include <QColorDialog>
#include <QPainter>
#include <QDebug>
#include <QTime>


ColormapEdit::ColormapEdit(QWidget *parent)
	: QDialog(parent)
{
	lastRotate = 0;
	lastBias = 0;
	lastContrast = 0;
	rotated = biased = contrasted = false;
	setupUi(this);	
	rotateSlider->setRange(0,32);
	biasSlider->setRange(-16,16);
	contrastSlider->setRange(-32,32);

	// initial maps
	QPixmap mappix;
	mapBox->setIconSize(QSize(mapBox->width(),mapBox->height()));
	for(int i=0;i<ColorMap::mapsize;i++)
	{
	     mappix = getPixmap(ColorMap::maps[i],mapBox->width(),mapBox->height());
	     mapBox->addItem(mappix,"");
	}

	mapBox->setCurrentIndex(ColorMap::currentMap);

	connect(rotateSlider,SIGNAL(valueChanged (int)),this,SLOT(rotate(int)));
	connect(biasSlider,SIGNAL(valueChanged (int)),this,SLOT(bias(int)));
	connect(contrastSlider,SIGNAL(valueChanged (int)),this,SLOT(contrast(int)));
	connect(colorNumberButton,SIGNAL(toggled(bool)),this,SLOT( updateColormap()));
	connect(cancelButton,SIGNAL(pressed()),this,SLOT(reject()));
	connect(okButton,SIGNAL(pressed()),this,SLOT(okPressed()));
	connect(applyButton,SIGNAL(pressed()),this,SLOT(applyPressed()));;
	connect(biasResetButton,SIGNAL(pressed()),this,SLOT(biasReset()));;
	connect(rotateResetButton,SIGNAL(pressed()),this,SLOT(rotateReset()));;
	connect(contrastRestButton,SIGNAL(pressed()),this,SLOT(contrastRest()));;
	connect(mapBox,SIGNAL(activated(int)),this,SLOT(resetMap(int)));

	/*ToolButton的信号连接*/
	QToolButton *button;
	for(int i=0;i<32;i++)
	{
		button = findChild<QToolButton *>(tr("toolButton_%1").arg(i+1));
		if(button)
		{
			button->setIconSize(QSize(button->width(),button->height()));
			connect(button,SIGNAL(pressed()),this,SLOT(setColor()));
		}
	}
}


ColormapEdit::~ColormapEdit()
{

}

void ColormapEdit::setColorList(QList<QColor> colors)
{
	this->colors = colors;
	updateColormap();
}


void ColormapEdit::setColor()
{
	QToolButton *button=NULL;
	QString name;
	int index;
	QColor c ;
	button = qobject_cast<QToolButton *>(sender());
	if(button)
	{
		name = button->objectName();
	}
	index = name.split("_").last().toInt()-1;
	c = QColorDialog::getColor(colors[index], this);
	if(!c.isValid()){
	     c = colors[index];
	}
	colors.replace(index,c);
	updateColormap();
}

QPixmap ColormapEdit::getPixmap(QColor color,int width,int height,int number)
{
	static QPixmap pixmap(width,height);
	static QPainter painter(&pixmap);
	static QString text("%1");
	painter.setBrush(color);
	painter.setPen(Qt::NoPen);
	painter.drawRect(0,0,width,height);
	if(colorNumberButton->isChecked())
	{
		painter.setPen(Qt::white);
		painter.drawText(2,10,text.arg(number));
	}
	return pixmap;
}

QPixmap ColormapEdit::getPixmap(Rgb *colors,int width,int height)
{
	QPixmap pixmap(width,height);
	QPainter painter(&pixmap);
	painter.setPen(Qt::NoPen);
	qreal step = width/32;
	for(int i=0;i<32;i++)
	{
	     painter.setBrush(QColor(colors[i].red(),colors[i].green(),colors[i].blue()));
	     painter.drawRect(i*step,0,step,height);
	}
	return pixmap;
}

void ColormapEdit::rotate(int n)
{
	/*
	   向前(-->)移动n个解决方案：
	      1：删除后n个QList中的元素
		  2：将删除的后n个元素逆序插入到QList最前面
	   向后(<--)移动n个解决方案
		  1：删除前n个QList中的元素
		  2：将删除的前n个元素逆序插入到QList最后面
	*/
     biasReset();
     contrastRest();
	int num;
	num = n-lastRotate;
	lastRotate = n;

	Q_ASSERT(qAbs(n)<=colors.count());
	/*向前(-->)移动*/
	int max = colors.count()-1;
	if(num>0)
	{
		for(int i=0;i<num;i++)
		{
			colors.move(max,0);
		}
	}
	/*向后(<--)移动*/
	else
	{
		for(int i=0;i<-num;i++)
		{
			colors.move(0,max);
		}		
	}
	
	updateColormap();
	if(dynamicButton->isChecked())
		emit newColorList(colors);
	//rotated = true;
}


void ColormapEdit::bias(int n)
{

     contrastRest();
     rotateReset();

	static QList<QColor> frontColors;
	static QList<QColor> endColors;
	if(rotated | contrasted)
	{
		frontColors.clear();
		endColors.clear();
	}
	QColor color;
	qDebug()<<"bias"<<n;
	int num;
	num = n - lastBias;
	qDebug()<<"num is "<<num;
	if(num>0)
	{
		for(int i =0; i < num; i++)
		{
			if(lastBias+i<0)//收缩后回退
			{
				/*左边回退*/
				color = endColors.at(0);
				endColors.removeAt(0);
				colors.removeAt(0);
				colors.insert(15,color);

				/*右边回退*/
				color = frontColors.at(0);
				frontColors.removeAt(0);
				colors.removeAt(31);
				colors.insert(16,color);
			}

			else
			{
				/*左边压缩*/
				color = colors.at(15);
				frontColors.insert ( 0,colors.at(0));//把最前面的颜色加到frontColors列表中保存
				colors.removeAt(0);//删除第一个颜色
				colors.insert(14,color);//把中间的颜色插入到中间的前一个
				
				/*右边压缩*/
				color = colors.at(16);
				endColors.insert(0,colors.at(31));
				colors.removeAt(31);
				colors.insert(17,color);
			}
		}
	}
	if(num<0)
	{
	
		for(int i =0; i < -num; i++)
		{
			if(lastBias-i<=0)/*收缩*/
			{
				/*左边收缩*/
				color  = colors.at(0);
				endColors.insert(0,colors.at(15));
				colors.removeAt(15);//删除第一个颜色
				colors.insert(0,color);//把中间的颜色插入到中间的前一个

				/*右边收缩*/
				color = colors.at(31);
				frontColors.insert(0,colors.at(16));
				colors.removeAt(16);
				colors.insert(31,color);
			}
			else
			{
				/*左边回退*/
				color  = frontColors.at(0);
				frontColors.removeAt(0);
				colors.removeAt(15);//删除第一个颜色
				colors.insert(0,color);//把中间的颜色插入到中间的前一个

				/*右边回退*/
				color = endColors.at(0);
				endColors.removeAt(0);
				colors.removeAt(16);
				colors.insert(31,color);
			}
		}
	}
	updateColormap();	
	lastBias = n;
	if(dynamicButton->isChecked())
		emit newColorList(colors);
//	biased = true;

}


void ColormapEdit::contrast(int n)
{

     biasReset();
     rotateReset();

	static QList<QColor> frontColors;
	static QList<QColor> endColors;
	if(rotated | biased)
	{
		frontColors.clear();
		endColors.clear();
	}
	QColor color;
	int num;
	num = n - lastContrast;
	qDebug()<<"num is"<<num;
	/*整体左移*/
	if(num>0)
	{
		for(int i=0;i<num;i++)
		{		
			if(frontColors.count()==0) 
			color = colors.at(0);
			else
			{
				color = frontColors.at(0);
				frontColors.removeAt(0);
			}
			if(n>0)
				endColors.insert(0,colors.at(31));
			colors.removeAt(31);
			colors.insert(0,color);	
			qDebug()<<"frontColors:"<<frontColors.count()<<"endColors"<<endColors.count();
		}

	}
	/*整体右移*/
	if(num<0)
	{
		for(int i=0;i<-num;i++)
		{	
			if(endColors.count()==0) 
				color = colors.at(31);
			else
			{
				color = endColors.at(0);
				endColors.removeAt(0);
			}
			if(n<0)
				frontColors.insert(0,colors.at(0));
			colors.removeAt(0);
			colors.insert(31,color);	
			qDebug()<<"frontColors:"<<frontColors.count()<<"endColors"<<endColors.count();

		}
	}
	updateColormap();
	lastContrast = n;
	if(dynamicButton->isChecked())
		emit newColorList(colors);
//	contrasted = true;
}

void ColormapEdit::updateColormap()
{
	QTime time;
	time.start();
   colorFrame->setColorMap(colors);
   QToolButton *button;
   for(int i=0;i<32;i++)
   {
	   button = findChild<QToolButton *>(tr("toolButton_%1").arg(i+1));
	   if(button)
	   {
		   button->setIcon(getPixmap(colors[i],button->width(),button->height(),i+1));		   
	   }
   }
   qDebug()<<time.elapsed();
}

void ColormapEdit::resetMap(int index)
{
     rotateSlider->setValue(0);
     biasSlider->setValue(0);
     contrastSlider->setValue(0);
     setColorList(ColorMap::maps[index]);
	if(dynamicButton->isChecked())
		emit newColorList(colors);
}

void ColormapEdit::okPressed()
{
	emit newColorList(colors);
	accept();
}

void ColormapEdit::applyPressed()
{	
	emit newColorList( colors);	
}
