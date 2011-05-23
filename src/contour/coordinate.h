#ifndef COORDINATE_H
#define COORDINATE_H

#include <QGraphicsView>
#include <QGraphicsItem>

class QGraphicsScene;
class CoordinateItem;

#define MixTicks 10


class Coordinate:public QGraphicsView
{

Q_OBJECT

public:
     enum Type{Horizonal,Vertical};

     Coordinate(QWidget *parent = 0);

     void setType(Type type);

     ~Coordinate();

public slots:
     void addjust(float min,float max,float baseSize,float scale);

private:

     CoordinateItem* _item;
     QGraphicsScene *_scene;
     float _min,_max;
     float _baseSize;
     float _scale;
};

//////////////////////////////////////////////////////////////////

class CoordinateItem : public QGraphicsItem
{
     enum {Type = UserType +18};
public:
     CoordinateItem(QGraphicsItem *parent = 0);

     ~CoordinateItem();

     QRectF boundingRect() const;

     QPainterPath shap() const;

     int type() const
     {return Type;}

     void setType(Coordinate::Type type) 
     { _type = type;  }

     Coordinate::Type  getType() const
     {return _type;}

     void setCoordinate(float min,float max,float scale);

private:

     void paint(QPainter * painter, const QStyleOptionGraphicsItem * option,QWidget * widget = 0);

     void computeStep();

     float _min,_max;
     float _p1,_p2;//屏幕起始和结束点值
     float _step;
     float _scale;
     float _stepW;
     Coordinate::Type _type;
};

#endif
