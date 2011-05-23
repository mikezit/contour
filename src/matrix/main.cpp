#include <QtGui/QApplication>
#include <QDebug>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "matrix.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
// 	Matrix w(2,2);
// 	w[0][0]=2;
// 	w[0][1]=3;
// 	w[1][0]=2;
// 	w[1][1]=3;
// 	Matrix y(2,2);
// 	y[0][0]=2;
// 	y[0][1]=3;
// 	y[1][0]=2;
// 	y[1][1]=3;
// 	Matrix x = w*y;
// 	qDebug()<<w.toString().data();
// 	qDebug()<<w.T().toString().data();
// 	qDebug()<<x.toString().data();

	srand(time(NULL));
	int num =5;
	int n=4;
	int minX = 1000;
	int maxX = 2000;
	Matrix mymatrix(num,num);
	for(int i=0;i<mymatrix.getRowCount();i++)
	  for(int j=0;j<mymatrix.getColCount();j++){
	    mymatrix[i][j]= minX + rand()/(float)RAND_MAX*(maxX - minX);
	  }

	// 	qDebug()<<mymatrix.toString().data();
// 	Matrix tri = mymatrix.upperTriangle();
// 	qDebug()<<(mymatrix.inv()).toString().data();
// 	Matrix invv = mymatrix.inv()*mymatrix;
// 	qDebug()<<invv.toString().data();
// 	qDebug()<<tri.toString().data();
	

// 	Matrix mymatrix(5,5);
// 	mymatrix[0][0] = 2;
// 	mymatrix[0][1] = -8;
// 	mymatrix[0][2] = 6;
// 	mymatrix[0][3] = 8;
// 	mymatrix[0][4] = 8;

// 	mymatrix[1][0] = 3;
// 	mymatrix[1][1] = -9;
// 	mymatrix[1][2] = 5;
// 	mymatrix[1][3] = 10;
// 	mymatrix[1][4] = 8;

// 	mymatrix[2][0] = -3;
// 	mymatrix[2][1] = 0;
// 	mymatrix[2][2] = 1;
// 	mymatrix[2][3] = -2;
// 	mymatrix[2][4] = 8;

// 	mymatrix[3][0] = 1;
// 	mymatrix[3][1] = -4;
// 	mymatrix[3][2] = 0;
// 	mymatrix[3][3] = 6;
// 	mymatrix[3][4] = 8;

// 	mymatrix[4][0] = 3;
// 	mymatrix[4][1] = 43;
// 	mymatrix[4][2] = 2;
// 	mymatrix[4][3] = 5;
// 	mymatrix[4][4] = 2;

// 	Matrix mymatrix(3,3);
// 	mymatrix[0][0] = 0;
// 	mymatrix[0][1] = 1;
// 	mymatrix[0][2] = 2;

// 	mymatrix[1][0] = 1;
// 	mymatrix[1][1] = 0;
// 	mymatrix[1][2] = 3;

// 	mymatrix[2][0] = 4;
// 	mymatrix[2][1] = -3;
// 	mymatrix[2][2] = 8;

// 	Matrix Z(num,1);
// 	for(int i=0;i<Z.getRowCount();i++)
// 	  Z[i][0]=i;


//  	qDebug()<<Z.toString().data();
	qDebug()<<mymatrix.toString().data();
	qDebug()<<mymatrix.det();
	qDebug()<<mymatrix.T().toString().data();
	//	Matrix A = (mymatrix.T()*mymatrix).inv()*mymatrix.T()*Z;
// 	qDebug()<<(mymatrix.T()*mymatrix).toString().data();
// 	qDebug()<<(mymatrix.T()*mymatrix).inv().toString().data();
// 	qDebug()<<((mymatrix.T()*mymatrix).inv()*mymatrix.T()).toString().data();
//		qDebug()<<A.toString().data();

// 	std::cout<<A.toString();
 	qDebug()<<mymatrix.inv().toString().data();
	//
        qDebug()<<(mymatrix.inv()*mymatrix).toString().data();
// //
	  //Matrix all = mymatrix*mymatrix.inv();
// 	qDebug()<<all.toString().data();
// 		Matrix tri = mymatrix.upperTriangle();
// 		qDebug()<<mymatrix.toString().data();
// 		qDebug()<<tri.toString().data();
// 		qDebug()<<mymatrix.det();
// 		Matrix oneM = Matrix(10,10,0.23);
// 		qDebug()<<oneM.toString().data();

	return a.exec();
}
