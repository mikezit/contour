#include "contourscene.h"
ContourScene::ContourScene()
{
	QGraphicsRectItem *i1=new QGraphicsRectItem(QRectF(0,0,100,100));
	QGraphicsRectItem *i2=new QGraphicsRectItem(QRectF(0,0,100,100));
	i1->setZValue(1000);
	i2->setZValue(1000);
	i1->setFlag(QGraphicsItem::ItemIsMovable);
	i2->setFlag(QGraphicsItem::ItemIsMovable);
	_scaleRect.setPen(QPen(QColor(Qt::black)));
	_scaleRect.setZValue(1000);
	addItem(&_scaleRect);
	hideScaleRect();
}

ContourScene::~ContourScene()
{

}
