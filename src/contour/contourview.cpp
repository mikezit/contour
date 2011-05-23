#include <QTime>
#include <QMapIterator>
#include <cstdlib>
#include "contourview.h"
#include "contourscene.h"
#include "../matrix/matrix.h"
#include "curveitem.h"
#include <QColor>
#include <QMapIterator>
#include <QLineF>
#include <QRectF>
#include <QDebug>
#include <QScrollBar>
#include <QPaintEvent>

#define GRGB(Rgb) (qRgb(Rgb.red(),Rgb.green(),Rgb.blue())

bool lessThan(const CCurve* s1, const CCurve* s2)
{
     if(s1->type == CCurve::A || s1->type == CCurve::B )
     {
	  return s1->getCurveWidth() < s2->getCurveWidth();
     }
     else if(s1->type == CCurve::C)
     {
	  qreal w = fabs(s1->data[0].x() - s1->data[s1->data.count()-1].x());
	  if(fabs(w-SCENEWIDTH)<=0.0001)
	       return s1->data[0].y() > s2->data[0].y();
	  else
	       return s1->data[0].x() < s2->data[0].x();
     }
     else if(s1->type == CCurve::D)
     {
	  return s1->data[0].x() < s2->data[0].x();
     }
     else {
	  std::cout<<"bad!";
     }
}


ContourView::ContourView(QWidget * parent)
     : QGraphicsView(parent)
{
     setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
     _scene=new ContourScene;
     setScene(_scene);	
     setSceneRect(0,0,SCENEWIDTH,SCENEHEIGHT);
     setAlignment(Qt::AlignLeft|Qt::AlignTop);
     time.start();

     colorMap=new ColorMap;
     colorMap->useMapOf(0);
     colorMap->setRange(0,1);
     colorMap->interpose(INTERPOSE_NUM);
}

ContourView::~ContourView()
{

}


void ContourView::setGridData(CCurveList curveList ,CGridDataInfo dataInfo)
{
     _curveList = curveList;
     CCurve *curve;


     for(int i=0;i<_curveList.count();i++)
     {
	  curve = _curveList[i];
	  for(int j = 0;j<curve->data.count();j++) 
	  {
	       curve->data[j] = ConversePos::pos2scene(curve->data[j],&dataInfo);
	  }
	  QPointF min = ConversePos::pos2scene(curve->xMin,curve->yMin,&dataInfo);
	  QPointF max = ConversePos::pos2scene(curve->xMax,curve->yMax,&dataInfo);
	  curve->xMin = min.x();
	  curve->xMax = max.x();
	  curve->yMax = min.y();
	  curve->yMin = max.y();
     }

     _info = dataInfo;
     srotCurve();
}

void ContourView::drawData()
{
     CurveItem *item;
     for(int i=0;i<_curveList.count();i++)
     {
	  item = new CurveItem;
	  item->setCurve(_curveList[i]);
	  _scene->addItem(item);
     }
}

void ContourView::cleanData()
{
     QList<QGraphicsItem*> its =_scene->items(); 
     int count = its.count();
     for(int i=0;i<count;i++)
     {
	  if(its[i]->type() ==  CurveItem::Type || 
	     its[i]->type() == QGraphicsPathItem::Type||
	     its[i]->type() == QGraphicsLineItem::Type||
	     its[i]->type() == QGraphicsEllipseItem::Type)
	       _scene->removeItem(its[i]);
     }
}

void ContourView::cleanColor()
{
     for(int i=0;i<_fillItems.count();i++)
     {
	  _scene->removeItem(_fillItems[i]);	
     }
}

void ContourView::setShowColor(bool show)
{
     for(int i=0;i<_fillItems.count();i++)
     {
	  _fillItems[i]->setVisible(show);
     }
}

void ContourView::setShowGrid(bool show)
{
     for(int i=0;i<_gridItems.count();i++)
     {
	  _gridItems[i]->setVisible(show);
     }
}

void ContourView::removePoints()
{
     for(int i=0;i<_pointsItems.count();i++)
     {
	  _scene->removeItem(_pointsItems[i]);
     }
}

void ContourView::fillColor()
{
     _fillItems.clear();

     bool last = true;
     int zvalue = 20;

     if(typeC.count() !=0)
     {
	  last = false;
	  fillCurve(typeC[0],zvalue++,true);
	  for(int i=1;i<typeC.count()-1;i++){
	       fillCurve(typeC[i],zvalue++);
	  }
     }

     if(typeB.count() !=0)
     {
	  if(last)
	  {
	       last = false;
	       fillCurve(typeB[typeB.count()-1],zvalue++,true);
	  }
	  else
	  {
	       fillCurve(typeB[typeB.count()-1],zvalue++);
	  }
	  for(int i=typeB.count()-1;i>=0;i--)
	       fillCurve(typeB[i],zvalue++);
     }

     if(typeA.count() !=0)
     {
	  for(int i=typeA.count()-1;i>=0;i--)
	  {
	       fillCurve(typeA[i],zvalue++);
	  }
     }

     if(typeD.count() !=0)
     {
	  for(int i=0;i<typeD.count();i++)
	       fillCurve(typeD[i],zvalue++);
     }
}

void ContourView::fillCurve(CCurve *curve,int zvalue,bool twoSide)
{
     QGraphicsPathItem *item = new QGraphicsPathItem;
     QPainterPath  path;
     if(twoSide)
     {
	  //全部填充
	  path.moveTo(0,0);
	  path.addRect(_scene->sceneRect());
     }
     else
     {
	  path.moveTo(curve->data[0]);
	  for(int i=1;i<=curve->data.count()-1;i++)
	       path.lineTo(curve->data[i]);

	  if(curve->type == CCurve::B)
	  {
	       QPointF *pos;
	       CCurve::Corner cor = curve->getCorner();
	       if(cor == CCurve::topLeft)
		    pos = new QPointF(0,0);
	       else if(cor == CCurve::topRight)
		    pos = new QPointF(SCENEWIDTH,0);
	       else if(cor == CCurve::bottomLeft)
		    pos = new QPointF(0,SCENEHEIGHT);
	       else if(cor == CCurve::bottomRight)
		    pos = new QPointF(SCENEWIDTH,SCENEHEIGHT);
	       path.lineTo(*pos);
	       path.lineTo(curve->data[0]);
	  }
	  else if(curve->type == CCurve::C)
	  {
	       qreal w = fabs(curve->data[0].x() - curve->data[curve->data.count()-1].x());
	       if(w==SCENEWIDTH)//横向(向上填充)
	       {
		    if(curve->data[0].x() <=0.0001)//起点在左
		    {
			 path.lineTo(SCENEWIDTH,0);
			 path.lineTo(0,0);
		    }else
		    {
			 path.lineTo(0,0);
			 path.lineTo(SCENEWIDTH,0);
		    }
		    path.lineTo(curve->data[0]);
	       }
	       else
	       {
		    if(curve->data[0].y()<=0.001) // 起点在上
		    {
			 path.lineTo(SCENEWIDTH,SCENEHEIGHT);
			 path.lineTo(SCENEWIDTH,0);
		    }
		    else{
			 path.lineTo(SCENEWIDTH,0);
			 path.lineTo(SCENEWIDTH,SCENEHEIGHT);
		    }
		    path.lineTo(curve->data[0]);
	       }
	  }
     }
     Rgb c;
     c = colorMap->findIndex((curve->value-_info.zMin)/(_info.zMax-_info.zMin));
     item->setPath(path);
     item->setBrush( QColor(qRgb(c.red(),c.green(),c.blue())));
     item->setPen(Qt::NoPen);
     item->setZValue(zvalue);
     _scene->addItem(item);
     _fillItems<<(item);
}

void ContourView::drawGrid()
{
     double  step;
     QPointF p1,p2;
     QGraphicsLineItem *itemLine;
     int gridValue = 300;
     QColor gridColor ;
     QPen gridPen;
     gridPen.setColor(Qt::black);
     gridPen.setStyle(Qt::DotLine);
     _gridItems.clear();

     // 先画出横向
     step = (_info.xMax - _info.xMin)/(_info.cols-1);
     for(int i=0;i<_info.cols;i++)
     {
	  p1 = ConversePos::pos2scene(_info.xMin + i*step,_info.yMin,&_info);
	  p2 = ConversePos::pos2scene(_info.xMin + i*step,_info.yMax,&_info);
	  itemLine = new QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y());
	  itemLine->setZValue(gridValue);
	  itemLine->setPen(gridPen);
	  _scene->addItem(itemLine);
	  _gridItems<<itemLine;
     }

     // 先画出纵向
     step = (_info.yMax - _info.yMin)/(_info.rows-1);
     for(int i=0;i<_info.rows;i++)
     {
	  p1 = ConversePos::pos2scene(_info.xMin,_info.yMin + i*step,&_info);
	  p2 = ConversePos::pos2scene(_info.xMax,_info.yMin + i*step,&_info);
	  itemLine = new QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y());
	  itemLine->setZValue(gridValue);
	  itemLine->setPen(gridPen);
	  _scene->addItem(itemLine);
	  _gridItems<<itemLine;
     }

}

void ContourView::drawScatterPoints(Matrix* data)
{
     _pointsItems.clear();
     QGraphicsEllipseItem *item;
     QPointF p1;
     for(int i=0;i<data->getRowCount();i++)
     {
	  p1 = ConversePos::pos2scene((*data)[i][0],(*data)[i][1],&_info);
	  item = new QGraphicsEllipseItem(0,0,10,10);
	  item->setPos(p1);
	  Rgb c;
	  c =  colorMap->findIndex(((*data)[i][2]-_info.zMin)/(_info.zMax-_info.zMin));
	  item->setBrush( QColor(qRgb(c.red(),c.green(),c.blue())));
	  item->setZValue(550);
	  item->setToolTip(
	       "X:"+ QString::number((*data)[i][0])+
	       " Y:"+QString::number((*data)[i][1])+
	       " Z:"+QString::number((*data)[i][2]));
	  _scene->addItem(item);
	  _pointsItems<<item;
     }
}

void ContourView::srotCurve()
{
     typeA.clear();
     typeB.clear();
     typeC.clear();
     typeD.clear();

     CCurve *curve;
     // 分类
     for(int i=0;i<_curveList.count();i++)
     {
	  curve = _curveList[i];
	  if(curve->type == CCurve::A)
	       typeA<<curve;
 	  else if(curve->type == CCurve::B)
  	       typeB<<curve;
	  else if(curve->type == CCurve::C)
	       typeC<<curve; 
  	  else if(curve->type == CCurve::D)
  	       typeD<<curve;
     }
     // 排序
     if(typeA.count() != 0)
     {
	  qSort(typeA.begin(),typeA.end(),lessThan);
     }
     if(typeB.count() != 0)
     {
	  qSort(typeB.begin(),typeB.end(),lessThan);
     }
     if(typeC.count() != 0)
     {
	  qSort(typeC.begin(),typeC.end(),lessThan);
     }
     if(typeD.count() != 0)
     {
	  qSort(typeD.begin(),typeD.end(),lessThan);
     }
}

void ContourView::mousePressEvent ( QMouseEvent * event )
{
     QGraphicsView::mousePressEvent(event);

     if((event->buttons() & Qt::MidButton)!=0)
     {
	  qobject_cast<ContourScene *>(scene())->setScaleRectLeftTopPos(mapToScene(event->pos()));
     }
}


void ContourView::mouseMoveEvent( QMouseEvent * event )
{	
     QGraphicsView::mouseMoveEvent(event);
     if((event->buttons() & Qt::MidButton)!=0)
     {	
	  qobject_cast<ContourScene *>(scene())->setScaleRectRightBottomPos(mapToScene(event->pos()));
	  qobject_cast<ContourScene *>(scene())->showScaleRect();
     }
     else{
	  // show grid's z value
	  QPointF sp = mapToScene(event->pos());
	  int i = _info.cols*(sp.x()/_scene->width());
	  int j = _info.rows - _info.rows*(sp.y()/_scene->height());
	  emit indexChanged(i,j);
     }
}

void ContourView::mouseReleaseEvent ( QMouseEvent * event )
{
     QGraphicsView::mouseReleaseEvent(event);
     QRectF f;
     QRect r;
     if(event->button()==Qt::MidButton)
     {
	  f=qobject_cast<ContourScene *>(scene())->scaleRect();
	  r=mapFromScene(f).boundingRect();
	  if(r.width()<=2 || r.height()<=2){
	       fitInView(sceneRect(),Qt::IgnoreAspectRatio);
	  }
	  else
	       fitInView(f,Qt::IgnoreAspectRatio);
	  /*比例可以这样计算出来*/
	  scaleX=matrix().m11();
	  scaleY=matrix().m22();	
	  qobject_cast<ContourScene *>(scene())->hideScaleRect();
	  emit setVCoordinate(_info.yMin,_info.yMax,_scene->height(),scaleY);
	  emit setHCoordinate(_info.xMin,_info.xMax,_scene->width(),scaleX);
     }
}
     
