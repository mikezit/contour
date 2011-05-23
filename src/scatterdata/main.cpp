#include <QtGui/QApplication>
#include <cstdlib>
#include <QDebug>
#include "../matrix/matrix.h"
#include "scatterdata.h"


int main(int argc,char *argv[])
{
  QApplication a(argc, argv);

  Matrix sd  = ScatterData::randScatterData(80,100,20,40,300,500,15);
  qDebug()<<sd.toString().data();
  ScatterData op;
  op.setScatterData(sd);
  op.setGridding(10,10);

  double minX,maxX,minY,maxY;

  Matrix out = op.getGridding(minX,maxX,minY,maxY);
  qDebug()<<out.toString().data();
  op.toFile("/root/op.grd");
  return a.exec();
}
