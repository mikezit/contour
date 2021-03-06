/******************************************************
  contourView： 用来画出等值线的类
*****************************************************/

#ifndef CONTOURVIEW_H
#define CONTOURVIEW_H


#include "contourtracer.h"
#include "../color/colormap.h"
#include <QGraphicsView>
#include <QObject>
#include <QMap>
#include <QTime>
#include <QList>

class ContourScene;

class ContourView : public QGraphicsView
{
   Q_OBJECT

public:

  ContourView(QWidget * parent = 0);

  ~ContourView();

  void setGridData(CCurveList curveList ,CGridDataInfo dataInfo);

  void cleanData();
 
  void cleanColor();

  void drawData();

  void drawGrid();

  void drawScatterPoints(Matrix* data);

  void fillColor();

  void showGrid(bool isShow );

  void setShowColor(bool show);

  void setShowGrid(bool show);

  void removePoints();

signals:
  void setVCoordinate(float min,float max,float baseSize,float scale);
  void setHCoordinate(float min,float max,float baseSize,float scale);
  void indexChanged(int x,int y);

public:
  ColorMap *colorMap;

protected:
  void mouseMoveEvent ( QMouseEvent * event );
  void mousePressEvent ( QMouseEvent * event );
  void mouseReleaseEvent ( QMouseEvent * event );


 private:
  void fillCurve(CCurve *curve,int zvalue,bool twoSide=false);
  void srotCurve();

  ContourScene *_scene;
  qreal scaleX,scaleY;
  CCurveList _curveList;
  CCurveList typeA;
  CCurveList typeB;
  CCurveList typeC;
  CCurveList typeD;
  CGridDataInfo _info;

  QList<QGraphicsPathItem*> _fillItems;
  QList<QGraphicsLineItem*> _gridItems;
  QList<QGraphicsEllipseItem*> _pointsItems;
  QTime time;
};

#endif 
