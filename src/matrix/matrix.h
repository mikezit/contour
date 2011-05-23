#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <QString>
/*
  此类包括基本的矩阵运算
  简均写于2008年12月8日


  矩阵初始时所有元素皆为0
*/

class Matrix 
{
 public:

  /*默认构造函数*/
  Matrix();

  /*构造单位矩阵*/
  Matrix(int n);

  Matrix(const Matrix &m);//copy constructor

  /*构造一个rows×colums的矩阵,默认所有值为0*/
  Matrix(int rows,int cols,double num=0);

  ~Matrix();

  inline int getRowCount()const {
    return rows;
  }

  inline int getColCount()const {
    return cols;
  }

  //交换此矩阵的两行（用于初等变换）
  void changeRow(int row1,int row2);

  //返回此矩阵的上三角矩阵, numOfChangeRows 是转换为上三角矩阵时
  //所用行变换的次数
  Matrix& upperTriangle(int &numOfChangeRows);

  Matrix& upperTriangle(){
    int a;
    return upperTriangle(a);
  }

  //矩阵的逆
  Matrix& inv();

  //矩阵的行列式
  double det();

  //矩阵转置
  Matrix& T();

  /*矩阵加法*/
  Matrix& operator+(const Matrix &m);

  /*矩阵减法*/
  Matrix& operator-(const Matrix &m);

  /*矩阵乘法*/
  Matrix& operator*(const Matrix &m);

  friend std::ostream &operator<<(std::ostream&, const Matrix&);

	
  double* operator[](int col)const;

  /*返回该矩阵的C++ string字符串表示*/
  std::string toString() ;

 private:
  double** matrix;//矩阵数据
  int rows,cols;//矩阵行列数
};

#endif // MATRIX_H
