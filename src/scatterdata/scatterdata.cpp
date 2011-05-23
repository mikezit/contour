#include "scatterdata.h"
#include "../contour/contourstruct.h"
#include <cstdlib>
#include <fstream>
#include <QDebug>
#include <ctime>

ScatterData::ScatterData()
{
     slipH = slipV =100;//默认的网格数为100
}

ScatterData::ScatterData(Matrix &data)
{
     slipH = slipV =100;//默认的网格数为100
     setScatterData(data);
}

ScatterData::~ScatterData()
{

}


void ScatterData::setScatterData(Matrix &data)
{
     scatterData = &data;
     minX = maxX = data[0][0];	
     minY = maxY = data[0][1];	
     minZ = maxZ = data[0][2];
     //找出离散数据中的最大最小值
     for(int i=0;i<data.getRowCount();i++){ 
	  if(minX > data[i][0])
	       minX = data[i][0];
	  else if(data[i][0]>maxX)
	       maxX = data[i][0];

	  if(minY > data[i][1])
	       minY = data[i][1];
	  else if(maxY < data[i][1])
	       maxY = data[i][1];

	  if(minZ > data[i][2])	
	       minZ = data[i][2];
	  else if(maxZ < data[i][2])
	       maxZ = data[i][2];
     }
     width = maxX -minX;
     height = maxY - minY;
    
     /*适当的调整范围*/
     //minX = minX - width/100;
     //maxX = maxX + width/100;
     //minY = minY - height/100;
     //maxY = maxY + height/100;
     width = maxX -minX;
     height = maxY - minY;
}

void ScatterData::setGridding(int horizontal,int vertical)
{
     slipH = horizontal;
     slipV = vertical;
}

Matrix& ScatterData::getGridding(double &pminX,double &pmaxX,double &pminY,double &pmaxY)
{

     Matrix X((*scatterData).getRowCount(),10);
     Matrix Z((*scatterData).getRowCount(),1);
     griddingData =  new Matrix(slipH,slipV);
     double x,y;
     for(int i=0;i<(*scatterData).getRowCount();i++)
     {
	  x = (*scatterData)[i][0];
	  y = (*scatterData)[i][1];
	  Z[i][0] = (*scatterData)[i][2];

	  X[i][0] = 1; 
	  X[i][1] = x;
	  X[i][2] = y;
	  X[i][3] = x*x;
	  X[i][4] = x*y;
	  X[i][5] = y*y;
	  X[i][6] = X[i][3]*x;
	  X[i][7] = X[i][3]*y;
	  X[i][8] = x*X[i][5];
	  X[i][9] = X[i][5]*y;
     }
     //得到参数矩阵
     Matrix A =  ((X.T())*X).inv()*(X.T())*Z;
     //Matrix A =  X.inv()*Z;
     for(int i=0;i<(*scatterData).getRowCount();i++)
     {
	  x = (*scatterData)[i][0];
	  y = (*scatterData)[i][1];
	  double zz = (*scatterData)[i][2];
	  double ww  = A[0][0] + A[1][0]*x + A[2][0]*y + A[3][0]*x*x
	       + A[4][0]*x*y + A[5][0]*y*y + A[6][0]*x*x*x +A[7][0]*x*x*y
	       + A[8][0]*x*y*y + A[9][0]*y*y*y;
     }

     double stepX = width/slipH;
     double stepY = height/slipV;
     for(int i=0;i<(*griddingData).getRowCount();i++)
     {
	  y = minY + i*stepY;
	  for(int j=0;j<(*griddingData).getColCount();j++)
	  {
	       x = minX + j*stepX;
	       (*griddingData)[i][j] = A[0][0] + A[1][0]*x + A[2][0]*y + A[3][0]*x*x
		    + A[4][0]*x*y + A[5][0]*y*y + A[6][0]*x*x*x +A[7][0]*x*x*y
		    + A[8][0]*x*y*y + A[9][0]*y*y*y;
	  }
     }
     pminX = this->minX;
     pmaxX = this->maxX;
     pminY = this->minY;
     pmaxY = this->maxY;
     qDebug()<<griddingData->toString().data();
     return (*griddingData);
}

Matrix& ScatterData::getGridding()
{
     double a,b,c,d;
     return getGridding(a,b,c,d);
}


void ScatterData::getRange(double &pminX,double &pmaxX,double &pminY,double &pmaxY)
{
     pminX = this->minX;
     pmaxX = this->maxX;
     pminY = this->minY;
     pmaxY = this->maxY;
}


Matrix& ScatterData::randScatterData(double pminX,double pmaxX,double pminY,double pmaxY,
				     double pminZ,double pmaxZ ,int n)
{  
     srand(time(NULL));
     Matrix &tmatrix = *(new Matrix(n,3));
     for(int i=0;i<n;i++)
     { 
	  tmatrix[i][0] = pminX + rand()/(float)RAND_MAX*(pmaxX - pminX);
	  tmatrix[i][1] = pminY + rand()/(float)RAND_MAX*(pmaxY - pminY);
	  tmatrix[i][2] = pminZ + rand()/(float)RAND_MAX*(pmaxZ - pminZ);
     }
     return tmatrix; 
}

void ScatterData::toGridFile(std::string name)
{
     std::ofstream file(name.c_str());
     if(!file){
	  std::cerr<<"can not open file:"<<name<<" for writting.";
     }
     file<<"DSAA\n";
     file<<slipV<<" "<<slipH<<"\n";
     file<<minX<<" "<<maxX<<"\n";
     file<<minY<<" "<<maxY<<"\n";
     file<<minZ<<" "<<maxZ<<"\n";
     int n=1;
     for(int i=0;i<griddingData->getRowCount();i++)
	  for(int j=0;j<griddingData->getColCount();j++,n++)
	  {
	       file<<(*griddingData)[i][j]<<" ";
	       if(n%10 == 0)
		    file<<"\n";
	  }
     file.close();
}
void ScatterData::toScatterFile(std::string name)
{
     std::ofstream file(name.c_str());
     if(!file){
	  std::cerr<<"can not open file:"<<name<<" for writting.";
     }
     file<<"SSAA\n";
     file<<scatterData->getRowCount()<<"\n";

     for(int j=0;j<scatterData->getRowCount();j++)
     {
	  file<<(*scatterData)[j][0]<<" "<<
	       (*scatterData)[j][1]<<" "<<(*scatterData)[j][2]<<"\n";
     }
     file.close();
}

bool ScatterData::readScatterFile(char* name,Matrix **data)
{
     std::ifstream file(name);
     if(!file){
	  std::cerr<<"can not open file:"<<name<<" for writting.";
	  return false;
     }
     std::string type;
     file>>type;
     if(type != "SSAA"){
	  std::cerr<<"this is not a grd file!,return forced.";
	  return false;
     }
     int row;
     file >> row;
     *data = new Matrix(row,3);
     for(int i =0;i<row;i++)
     {
	  file >> (**data)[i][0];
	  file >> (**data)[i][1];
	  file >> (**data)[i][2];
     }
     file.close();
     return true;
}

bool ScatterData::readGridFile(char* name,GridData &data)
{
     setlocale(LC_ALL,"Chinese-simplified");//设置中文环境
     std::ifstream file(name);
     if(!file){
	  std::cerr<<"can not open file:"<<name<<" for writting.";
	  return false;
     }
     std::string type;
     file>>type;
     if(type != "DSAA"){
	  std::cerr<<"this is not a grd file!,return forced.";
	  return false;
     }
     CGridDataInfo info;
     Matrix *mat;
     file>>info.cols;
     file>>info.rows;
     if(info.rows>0 && info.cols>0)
	  mat = new Matrix(info.rows,info.cols);
     file>>info.xMin;
     file>>info.xMax;
     file>>info.yMin;
     file>>info.yMax;
     file>>info.zMin;
     file>>info.zMax;
     for(int i=0;i<info.rows;i++)
	  for(int j=0;j<info.cols;j++)
	  {
	       file>> (*mat)[i][j];
	  }
     file.close();
     data.data = mat;
     data.info = info;
     return true;
}


