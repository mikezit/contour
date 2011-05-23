#include "curveitem.h"  
#include <QPainter>
#include <QDebug>
#include <vector>

CurveItem::CurveItem(QGraphicsItem* parent)
     :QGraphicsItem(parent)
{
     setFlag(QGraphicsItem::ItemIsSelectable, true); 
     setZValue(3);
}


CurveItem::~CurveItem()
{

}


void CurveItem::setCurve(CCurve *curve)
{
     _curve = curve;
}


QRectF CurveItem::boundingRect() const
{
       return QRectF(_curve->xMin,_curve->yMin,
  		   _curve->xMax - _curve->xMin,_curve->yMax - _curve->yMin);
}

QPainterPath CurveItem::shap() const
{
     QPainterPath path;
     path.addRect(boundingRect());
     return path;
}


void CurveItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
     int count = _curve->data.count();
     for(int i=0;i<count-1;i++)
     {
	  painter->drawLine(_curve->data[i],_curve->data[i+1]);
     }
}
