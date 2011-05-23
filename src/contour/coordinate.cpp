#include "coordinate.h"
#include <QGraphicsScene>
#include <cmath>
#include <QDebug>
#include <string>
#include "../color/colormap.h"
#include <QColor>
#include <QtGui/QWidget>
#include <QList>
#include <QMap>
#include <QLineF>
#include <QTimer>

Coordinate::Coordinate(QWidget *parent/* = 0*/)
{
     _item = new CoordinateItem();
     _item->setPos(0,0);
     _scene = new QGraphicsScene;
     _scene->addItem(_item);
     setScene(_scene);
     setAlignment(Qt::AlignLeft | Qt::AlignTop);
     setBackgroundBrush(Qt::lightGray);
	/*初始化坐标图元*/
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

Coordinate::~Coordinate()
{

}

void Coordinate::setType(Type type)
{
     _item->setType(type);
}

void Coordinate::addjust(float min,float max,float basesize,float scale)
{
     if(_item->getType() == Horizonal){
	  _scene->setSceneRect(0,0,basesize*scale,height());
     }else{
	  _scene->setSceneRect(0,0,width(),basesize*scale);
     }
     _min = min;
     _max = max;
     _scale = scale;
     _baseSize = basesize;

     _item->setCoordinate(min,max,_scale);
}


///////////////////////////////////////////////////////


CoordinateItem::CoordinateItem(QGraphicsItem *parent/* = 0*/)
     :QGraphicsItem(parent)
{

}

CoordinateItem::~CoordinateItem()
{

}

void CoordinateItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option,QWidget * widget /*= 0*/)
{
     int start =0;
     int end;
     float itemWidth = scene()->width();
     float itemHeight = scene()->height();

     if(_scale > 50){
	  int ty1,ty2;	  
	  if(_type == Coordinate::Horizonal){
	       ty1 = scene()->views()[0]->mapToScene(0,0).x();
	       ty2 = scene()->views()[0]->mapToScene(scene()->views()[0]->width(),0).x();
	  }
	  else{
	       ty1 = scene()->views()[0]->mapToScene(0,0).y();
	       ty2 = scene()->views()[0]->mapToScene(0,scene()->views()[0]->height()).y();
	  }
	  start = ty1/_stepW;
	  end = ty2/_stepW;
     }else{
	  if(_type == Coordinate::Horizonal)
	       end =scene()->width()/ _stepW ; 
	  else 
	       end = scene()->height()/_stepW;
	  end ++;
     }
     // 绘制
     if(_type == Coordinate::Vertical){
	  if(start ==0 ){
	       painter->drawLine(itemWidth*9/10, 1,itemWidth,1);
	       painter->drawText(0,0,itemWidth,20,  
				 Qt::AlignHCenter,QString::number(_max,'f',2));
	       start++;
	  }

	  for(int i=start;i<=end;i++)
	  {
	       painter->drawLine(itemWidth*9/10, _stepW*i,itemWidth,_stepW*i);
	       painter->drawText(0, _stepW*i  -10,itemWidth,20,
				 Qt::AlignHCenter,QString::number(_max - i*_step,'f',2));
	  }
     }else{
	  if(start ==0 ){
	       painter->drawLine(1,0,1,itemHeight/10);
	       painter->drawText(0,0,40,itemHeight,  
				 Qt::AlignVCenter,QString::number(_min,'f',2));
	       start++;
	  }

	  for(int i=start;i<=end;i++)
	  {
	       painter->drawLine( _stepW*i,0,_stepW*i,itemHeight/10);
	       painter->drawText( _stepW*i -30,0,60,itemHeight, 
				  Qt::AlignCenter,QString::number(_min + i*_step,'f',2));
	  }

     }

}


QRectF CoordinateItem::boundingRect() const
{
	  return QRectF(0,0,scene()->width(),scene()->height());
}

QPainterPath CoordinateItem::shap() const
{
     QPainterPath path;
     path.addRect(boundingRect());
     return path;
}

void CoordinateItem::setCoordinate(float min,float max,float scale)
{
     _min = min;
     _max = max;
     _scale = scale;
     computeStep();
     if(_type == Coordinate::Horizonal)
	  _stepW = _step*scene()->width()/(_max - _min);
     else
	  _stepW = _step*scene()->height()/(_max - _min);
}



void CoordinateItem::computeStep()
{
     qreal grossStep = (_max-_min)/MixTicks/_scale;

     _step = pow(10.0,floor(log10(grossStep)));

     /*调整两个刻度之间的距离*/
     if (5 * _step < grossStep) {//5*step是5个标准刻度
	  _step *= 5;
     } else if (2 * _step < grossStep) {//2*step是2个标准刻度
	  _step *= 2;
     }
}

