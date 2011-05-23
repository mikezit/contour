#ifndef CURVEITEM_H
#define CURVEITEM_H

#include "contourstruct.h"
#include <QGraphicsItem>
  void drawGridPoints(GridData* data);


class CurveItem :public QGraphicsItem
{
public:
     enum {Type = UserType +3};

     CurveItem(QGraphicsItem* parent=0);

     ~CurveItem();

     void setCurve(CCurve *curve);

     int type() const {
	  return Type;
     }

     QRectF boundingRect() const;

     QPainterPath shap() const;

     void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
private:

     CCurve *_curve;
};

#endif


