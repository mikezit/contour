#include "contourframe.h"
#include "dialog/randsetdialog.h"
#include "dialog/tracesetdialog.h"
#include "dialog/colormapedit.h"
#include "../color/colormap.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QTime>
#include <QDebug>

ContourFrame::ContourFrame(QFrame* parent /*= 0*/, Qt::WindowFlags f/* = 0*/)
     :QFrame(parent,f)
{
     setupUi(this);
     setWindowTitle("Contour Tracing");
     ycoordinate->setType(Coordinate::Vertical);
     xcoordinate->setType(Coordinate::Horizonal);
     _scatterData = NULL;
     _out = NULL;
     _fillColor = true;
     _showGrid = true;
     _isRand = false;
     _showPoint = false;
     _hasShowGrid = false;
     _hasShowGrid = false;
     _traceNum = 50;
	 tracer = new ContourTracer;
     initial();
     view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

     connect(horizontalScrollBar,SIGNAL(valueChanged(int)),view->horizontalScrollBar(),
	     SLOT(setValue(int)));
     connect(verticalScrollBar,SIGNAL(valueChanged(int)),view->verticalScrollBar(),
	     SLOT(setValue(int)));
     connect(view->horizontalScrollBar(),SIGNAL(valueChanged(int)),horizontalScrollBar,
	     SLOT(setValue(int)));
     connect(view->verticalScrollBar(),SIGNAL(valueChanged(int)),verticalScrollBar,
	     SLOT(setValue(int)));
     connect(view->horizontalScrollBar(),SIGNAL(rangeChanged(int,int)),this,
	     SLOT(setHorizonBar()));
     connect(view->verticalScrollBar(),SIGNAL(rangeChanged(int,int)),this,
	     SLOT(setVerticalBar()));
     
     connect(view->horizontalScrollBar(),SIGNAL(valueChanged(int)),
	     xcoordinate->horizontalScrollBar(),SLOT(setValue(int)));
     connect(view->verticalScrollBar(),SIGNAL(valueChanged(int)),
	     ycoordinate->verticalScrollBar(),SLOT(setValue(int)));

     connect(view,SIGNAL(setVCoordinate(float,float,float,float)),ycoordinate
	     ,SLOT(addjust(float,float,float,float))); 
     connect(view,SIGNAL(setHCoordinate(float,float,float,float)),xcoordinate
	     ,SLOT(addjust(float,float,float,float))); 
     connect(view,SIGNAL(indexChanged(int,int)),this,SLOT(setLabel(int,int)));
}

ContourFrame::~ContourFrame()
{
}

void ContourFrame::randContour()
{
     delete _scatterData;
     _isRand = true;


     _scatterData  = &(ScatterData::randScatterData(_randInfo.xMin,_randInfo.xMax,
						    _randInfo.yMin,_randInfo.yMax,
						    _randInfo.zMin,_randInfo.zMax,_randNum));
     CGridDataInfo info;
     info.zMin = _randInfo.zMin;
     info.zMax = _randInfo.zMax;
     info.cols = _randInfo.cols;
     info.rows = _randInfo.rows;
   
     _op.setScatterData(*_scatterData);
     _op.setGridding(_randInfo.rows,_randInfo.cols);

     double xMin , xMax ,yMin,yMax;
     if(_out != NULL )
	   delete _out;
     _out = &(_op.getGridding(xMin,xMax,yMin,yMax));

     info.xMin = xMin;
     info.xMax = xMax;
     info.yMin = yMin;
     info.yMax = yMax;
     _gridData.data = _out;
     _gridData.info = info;
     _valueList.clear();
     tracing();
}

void ContourFrame::tracing()
{
     QTime tm;
     tm.start();
     CCurveList  *pCurveList = new CCurveList ;
     tracer->setGridDataInfo(_gridData.info);
     tracer->setInput(*(_gridData.data));
     if(_valueList.count() == 0)
     {
	  float step = (_gridData.info.zMax - _gridData.info.zMin)/_traceNum;
	  for(int i=0;i<_traceNum;i++)
	       _valueList<<_gridData.info.zMin + i*step;
     }
     for(int i=0;i<_valueList.count();i++)
     {
	  tracer->setOutput(pCurveList);
	  tracer->executeTracing(_valueList[i]);
     }
     qDebug()<<"time:traing:"<<tm.elapsed();tm.restart();
     view->cleanData();
    qDebug()<<"time:clean:"<<tm.elapsed();tm.restart();
     view->setGridData(*pCurveList,_gridData.info);
     view->drawData();
     qDebug()<<"time:draw:"<<tm.elapsed();tm.restart();
     _hasShowGrid = false;	// 重新绘制网格
     _hasShowColor = false;	// 重新填充颜色
      if(_fillColor)
	  setFillColor(true);
     qDebug()<<"time:fill:"<<tm.elapsed();tm.restart();
      if(_showGrid)
        setGrid(true);
     qDebug()<<"time:grid:"<<tm.elapsed();tm.restart(); 
      if(_showPoint&_isRand)
	  view->drawScatterPoints(_scatterData);
      colorFrame->setRange(_gridData.info.zMin,_gridData.info.zMax);

}

void ContourFrame::setHorizonBar()
{
     horizontalScrollBar->setRange(view->horizontalScrollBar()->minimum(),
				   view->horizontalScrollBar()->maximum());
     horizontalScrollBar->setPageStep(view->horizontalScrollBar()->pageStep());
}

void ContourFrame::setVerticalBar()
{
     verticalScrollBar->setRange(view->verticalScrollBar()->minimum(),
				 view->verticalScrollBar()->maximum());
     verticalScrollBar->setPageStep(view->verticalScrollBar()->pageStep());
}

void ContourFrame::setLabel(int i,int j)
{
     if(i>=0&& i<=_gridData.info.cols -1&&j>=0&& j<=_gridData.info.rows -1 )
     {
	  iLabel->setText("j: "+QString::number(j));
	  jLabel->setText("i: "+QString::number(i));
	  if(_gridData.data != NULL){
	       zLabel->setText(QString::number((*_gridData.data)[j][i]));
	  }
     }
}

void ContourFrame::importGridFile()
{
     _isRand = false;
	 QString fileName  =QFileDialog::getOpenFileName(this,tr("open file"),QDir::homePath(),
		 tr("Grid Data Files (*.grd)"));

     if(fileName=="") return;
     if(_gridData.data != NULL)
     {
	  delete _gridData.data;
	  _out = NULL;
     }

     QTime tm;
     tm.start();
     if(!ScatterData::readGridFile(QFile::encodeName ( fileName ).data(),_gridData)){
	  QMessageBox::warning(this,"warning","Open file error,the file"
			       " may be is not a right file!");
	  return;
     }
     qDebug()<<"time:reading:"<<tm.elapsed();
     _valueList.clear();
     tracing();
}

void ContourFrame::importScatterFile()
{
     _isRand = true;
	 QString fileName = QFileDialog::getOpenFileName(this,tr("open file"),QDir::homePath(),
		 tr("Scatter Data Files (*.srd)"));
     if(fileName=="") return;
     if(_scatterData != NULL)
	  delete _scatterData;
     if(!ScatterData::readScatterFile(QFile::encodeName ( fileName ).data(),&_scatterData)){
	  QMessageBox::warning(this,"warning","Open file error,the file"
			       " may be is not a right file!");
	  return;
     }

     CGridDataInfo info;
     float f;
     info.zMax = info.zMin = (*_scatterData)[0][2];
     for(int i=0;i<_scatterData->getRowCount();i++)
     {
	  f = (*_scatterData)[i][2];
	  if( f > info.zMax)
	       info.zMax = f;
	  else if(f <info.zMin)
	       info.zMin = f;
     }

   
     _op.setScatterData(*_scatterData);
     _op.setGridding(_randInfo.cols,_randInfo.rows);

     double xMin , xMax ,yMin,yMax;
     Matrix out = _op.getGridding(xMin,xMax,yMin,yMax);
     info.xMin = xMin;
     info.xMax = xMax;
     info.yMin = yMin;
     info.yMax = yMax;
     info.rows = _randInfo.rows;
     info.cols = _randInfo.cols;

     _gridData.data = &out;
     _gridData.info = info;
     _valueList.clear();
     tracing();
}


void ContourFrame::saveRandData()
{
     QString fileName = QFileDialog::getSaveFileName(this);
     if(fileName =="") return;
     _op.toScatterFile(fileName.toStdString()); 
}

void ContourFrame::saveGridData()
{
     QString fileName = QFileDialog::getSaveFileName(this);
     if(fileName =="") return;
     _op.toGridFile(fileName.toStdString()); 
}

void ContourFrame::setRandInfo()
{
     RandSetDialog *dialog = new RandSetDialog;
     dialog->initialInfo(_randInfo,_randNum);
     if(dialog->exec()){
	  dialog->getInfo(_randInfo,_randNum); 
     }
}


void ContourFrame::initial()
{
     _randInfo.xMin = 0;
     _randInfo.xMax = 9;
     _randInfo.yMin = 10;
     _randInfo.yMax = 15;
     _randInfo.zMin = 50;
     _randInfo.zMax = 100;
     _randInfo.cols = 50;
     _randInfo.rows = 50;
     _randNum = 15;
     QList<QColor> colors;
     Rgb* sc = view->colorMap->getColors();//ColorMap::getColors();
     for(int i=0;i<32;i++)
	  colors<<QColor(sc[i].r,sc[i].g,sc[i].b);
     colorFrame->setColorMap(colors);
}



void ContourFrame::setTraceValue()
{
     TraceDialog dialog;
     dialog.setTraceValue(_valueList);
     if(_isRand)
	  dialog.setDefault(_randInfo.zMin,_randInfo.zMax,_traceNum);
     else
	  dialog.setDefault(_gridData.info.zMin,_gridData.info.zMax,_traceNum);
     if(dialog.exec())
     {
	  _valueList = dialog.getTraceValue();
	  _traceNum = dialog.getTraceNumber();
	  tracing();
     }
}

void ContourFrame::editColorMap()
{
     ColormapEdit *edit = new ColormapEdit(this);
     connect(edit,SIGNAL(newColorList(QList<QColor>)),this,SLOT(newColorMap(QList<QColor>)));
     Rgb* color = view->colorMap->getColors();
     edit->setColorList(color);
     edit->show();
}

void ContourFrame::newColorMap(QList<QColor> colors)
{
	QTime a;
	static int t1;
	static int t2;
	static int t3;
	static int t4;

     Rgb myColors[32];
     for(int i=0;i<32;i++)
	  myColors[i] = Rgb(colors[i].red(),colors[i].green(),colors[i].blue());
     view->colorMap->clear();
     view->colorMap->setColor(myColors);
	 a.start();
     view->colorMap->setRange(0,1);
     view->colorMap->interpose(INTERPOSE_NUM);
	 t1+=a.elapsed();
	 qDebug()<<"interpose:"<<t1;a.restart();
     colorFrame->setColorMap(colors);
	 t2+=a.elapsed();
	 qDebug()<<"setColorMap:"<<(t2);a.restart();
     view->cleanColor();
	 t3+=a.elapsed();
	 qDebug()<<"cleanColor:"<<(t3);a.restart();
     view->fillColor();
	 t4+=a.elapsed();
	 qDebug()<<"fillColor:"<<(t4);a.restart();
}
