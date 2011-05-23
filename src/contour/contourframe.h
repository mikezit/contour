#ifndef CONTOURFRAME_H
#define CONTOURFRAME_H

#include "contourview.h"
#include "../scatterdata/scatterdata.h"
#include "ui_contourframe.h"
#include <QFrame>
#include <QVector>
#include <QObject>
#include <QKeyEvent>

class ContourFrame : public QFrame ,public Ui::CFrame
{
   Q_OBJECT
public:

     ContourFrame(QFrame * parent = 0, Qt::WindowFlags f = 0 );

     ~ContourFrame();


public slots:

     void importGridFile();

     void importScatterFile();

     void randContour();

     void setRandInfo();

     void saveRandData();

     void saveGridData();

     void setTraceValue();

     void setLabel(int i,int j);

     void editColorMap();

     void newColorMap(QList<QColor> colors);

     inline void setFillColor(bool isFillOn);

     inline void setGrid(bool isGridOn);

     inline void setPointShow(bool isPointOn);

private slots:

     void setHorizonBar();

     void setVerticalBar();

public:
     bool _isRand;
     bool _showGrid;
     bool _fillColor;
     bool _showPoint;

private:

     void initial();

     void tracing();

     GridData _gridData;
     Matrix *_scatterData;
     Matrix *_out;
     ContourTracer *tracer;
     ScatterData _op;
     bool _hasShowGrid;//是否已经进行了网格显示
     bool _hasShowColor;//是否已经进行了颜色填充
     CGridDataInfo _randInfo;
     QVector<float> _valueList;
     int _randNum;
     int _traceNum;
};


inline  void ContourFrame::setFillColor(bool isFillOn)
{
     if(_fillColor|isFillOn){//changed
	  if(isFillOn){
	       if(!_hasShowColor){
		    view->fillColor();
		    _hasShowColor = true;
	       }
	       else 
		    view->setShowColor(true);
	  }
	  else 
	       view->setShowColor(false);
     }
     _fillColor = isFillOn;
}

inline  void ContourFrame::setGrid(bool isGridOn)
{
     if(_showGrid|isGridOn)
     {
	  if(isGridOn){
	       if(!_hasShowGrid){
		    view->drawGrid();
		    _hasShowGrid = true;
	       }
	       else
		    view->setShowGrid(true);
	  }
	  else 
	       view->setShowGrid(false);
     }
     _showGrid=isGridOn;
}

inline void ContourFrame::setPointShow(bool isPointOn)
{
     if(!_isRand)
	  return;
     if(isPointOn)
	  view->drawScatterPoints(_scatterData);
     else
	  view->removePoints();
     _showPoint=isPointOn;
}

#endif
