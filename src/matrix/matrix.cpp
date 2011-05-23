#include "matrix.h"
#include "assert.h"
#include <cmath>
#include <QDebug>
#include <algorithm>
#include <string>
#include "2DMemAllocator.h"


Matrix::Matrix(int rows,int cols,double num/*=0*/)
{
  if(!C2DMemAllocator::AllocMemory2D(matrix,rows,cols)){
    std::cout<<"false to allocate memory!"<<std::endl;
  }
  for(int i=0;i<rows;i++)
     for(int j=0;j<cols;j++){
	matrix[i][j] = num;
     }
  this->cols = cols;
  this->rows = rows;
}

Matrix::Matrix(const Matrix &m)
{
  cols = m.getColCount();
  rows = m.getRowCount();
  if(!C2DMemAllocator::AllocMemory2D(matrix,rows,cols)){
    std::cout<<"false to allocate memory!"<<std::endl;
  }
  for(int i=0;i<rows;i++)
     for(int j=0;j<cols;j++){
	matrix[i][j] = m[i][j];
     }
}

Matrix::Matrix(int n)
{
  rows = cols = n;
  if(!C2DMemAllocator::AllocMemory2D(matrix,rows,cols)){
	std::cout<<"false to allocate memory!"<<std::endl;
  }

  for(int i=0;i<rows;i++)
    for(int j=0;j<cols;j++){
      if(i==j)
	matrix[i][j] = 1;
      else 
	matrix[i][j] = 0;
  }


}

Matrix::Matrix()
{
	matrix = NULL;
}

Matrix::~Matrix()
{
	C2DMemAllocator::FreeMemory2D(matrix);
}

double Matrix::det()
{
  double tDet=1;
  int numberOfChangeRow;
  Matrix upperMatrix = upperTriangle(numberOfChangeRow);
  for(int i=0;i<rows;i++)
      tDet *= upperMatrix[i][i];
  return tDet*pow(-1.0,numberOfChangeRow);
}

Matrix& Matrix::T()
{

  Matrix &tmatrix = *(new Matrix(cols,rows));

  for(int i=0;i<cols;i++){
    for(int j=0;j<rows;j++)
      tmatrix[i][j] = matrix[j][i];
  }
    return tmatrix;

}

Matrix& Matrix::inv()
{
  assert(rows == cols);//Ϊ����
  assert(det() != 0);//����ʽ��Ϊ0
  Matrix &invMatrix =  *(new Matrix(rows));

  /*
  ��������㷨
  
  *���ö���:
  
      n*n����A�ǿ����,���ҽ���A�еȼ��ڽ�Ϊn�ĵ�λ����,��ʱ����A��Ϊ��
    Ϊn�ĵ�λ�����һϵ�г��ȱ任ͬʱ�ѽ�Ϊn�ĵ�λ�����ΪA����

    *�����ǽ�����Aת��Ϊ��λ������㷨:
    
    1:  i=0
    2:  �ж�A[i][i]�Ƿ�Ϊ0���������:��3�������:���������A[i+k][j]�н���,�ٵ�3��
    3:  ��n = 1/A[i][i]���� k = [i...cols-1],��A[i][k] = A[i][k]*n��
    4:  ��r = [0...rows-1],����r ����i����,��n = A[r][i],�� k = [i...cols-1]��
        ��A[r][k]-=n*A[i][k]��
    5:  ���i = cols��1��������ɣ�����i��i+1,��2��

  */
  Matrix &tmatrix =  *(new Matrix(*this));
  for(int i=0;i<rows;i++){
      //2
      if(tmatrix[i][i]==0){

	int next = i+1;

	for(next=i+1;next<rows;next++){
	  if(tmatrix[next][i]!=0){
	  tmatrix.changeRow(i,next);
	  invMatrix.changeRow(i,next);
	  break;
	  }

	}
	if(next == rows)
	  break;
      }
      //3

      double n = 1/tmatrix[i][i];//��A[i][i]��ת��Ϊ1
      for(int k = i;k < cols;k++){
	tmatrix[i][k] = tmatrix[i][k]*n;
      }

      for(int k = 0;k < cols;k++){
	invMatrix[i][k] = invMatrix[i][k]*n;
      }


      //4
      for(int r=0;r<rows;r++){
	if(r != i){
	  n = tmatrix[r][i];
          for(int k = i;k < cols;k++){
	    tmatrix[r][k]-=n*tmatrix[i][k];
	  }

          for(int k = 0;k < cols;k++){
	    invMatrix[r][k]-=n*invMatrix[i][k];
	  }
	}
      }
      
    }

    return invMatrix;
}

void Matrix::changeRow(int row1,int row2)
{
  for(int i=0;i<cols;i++)
    std::swap(matrix[row1][i],matrix[row2][i]);
}

Matrix& Matrix::upperTriangle(int &numOfChangeRows)
{
  assert(rows == cols);

  Matrix &tmatrix =  *(new Matrix(*this));
  numOfChangeRows = 0;

  for(int i=0;i<rows;i++)
    for(int j=i+1;j<rows;j++){
      /*���������Ϊ0��Ӧ������*/
      if(tmatrix[i][i]==0){
	int next = i+1;
	for(next=i+1;next<rows;next++){
	  if(tmatrix[next][i]!=0){
	  tmatrix.changeRow(i,next);
	  numOfChangeRows++;
	  break;
	  }
	}
	if(next == rows)
	  break;       
      }

      double k = tmatrix[j][i]/tmatrix[i][i];
      tmatrix[j][i]=0;
      for(int n=i+1;n<cols;n++)
	tmatrix[j][n] = tmatrix[j][n] - k*tmatrix[i][n];
    }

  return tmatrix;

}

Matrix& Matrix::operator+(const Matrix &m)
{
  assert(this->rows == m.getRowCount() && this->cols == m.getColCount());

  Matrix &tmatrix =  *(new Matrix(rows,cols));
  for(int i=0;i<rows;i++)
    for(int j=0;j<cols;j++){
      tmatrix[i][j] = matrix[i][j] + m[i][j];
    }
  return  tmatrix;
}

Matrix& Matrix::operator-(const Matrix &m)
{
  assert(this->rows == m.getRowCount() && this->cols == m.getColCount());

  Matrix &tmatrix =  *(new Matrix(rows,cols));
  for(int i=0;i<rows;i++)
    for(int j=0;j<cols;j++)
      tmatrix[i][j] = matrix[i][j] - m[i][j];
  return tmatrix;
}

Matrix& Matrix::operator*(const Matrix &m)
{
  assert( this->cols == m.getRowCount());

  Matrix &tmatrix = *(new Matrix(rows,m.getColCount()));
  for(int i=0;i<rows;i++)
    for(int j=0;j<m.getColCount();j++){
      tmatrix[i][j] = 0;
      for(int k=0;k<cols;k++)
	tmatrix[i][j] += matrix[i][k]*m[k][j];
    }
  return tmatrix;
}

double * Matrix::operator[](int row) const
{
  return matrix[row];
}

std::string  Matrix::toString() 
{

   std::string output="";
   char tmpNum[10];
   sprintf(tmpNum,"<%d ",rows);
   output+=strcat(tmpNum,",");
   sprintf(tmpNum," %d>",cols);
   output+=strcat(tmpNum,"\n");
   for(int i=0;i<rows;i++)
     for(int j=0;j<cols;j++){

       sprintf(tmpNum,"%f ",matrix[i][j]);
       output += tmpNum;
       if(j == (cols-1))
         output += "\n";

   }
  
   return output;
}

std::ostream & operator<<(std::ostream& output, const Matrix& m)
{
  //  std::string a  = m.toString();
  // output<<m.toString();a=
  return output;
}
