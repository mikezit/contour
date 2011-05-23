#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <QString>
/*
  ������������ľ�������
  ���д��2008��12��8��


  �����ʼʱ����Ԫ�ؽ�Ϊ0
*/

class Matrix 
{
 public:

  /*Ĭ�Ϲ��캯��*/
  Matrix();

  /*���쵥λ����*/
  Matrix(int n);

  Matrix(const Matrix &m);//copy constructor

  /*����һ��rows��colums�ľ���,Ĭ������ֵΪ0*/
  Matrix(int rows,int cols,double num=0);

  ~Matrix();

  inline int getRowCount()const {
    return rows;
  }

  inline int getColCount()const {
    return cols;
  }

  //�����˾�������У����ڳ��ȱ任��
  void changeRow(int row1,int row2);

  //���ش˾���������Ǿ���, numOfChangeRows ��ת��Ϊ�����Ǿ���ʱ
  //�����б任�Ĵ���
  Matrix& upperTriangle(int &numOfChangeRows);

  Matrix& upperTriangle(){
    int a;
    return upperTriangle(a);
  }

  //�������
  Matrix& inv();

  //���������ʽ
  double det();

  //����ת��
  Matrix& T();

  /*����ӷ�*/
  Matrix& operator+(const Matrix &m);

  /*�������*/
  Matrix& operator-(const Matrix &m);

  /*����˷�*/
  Matrix& operator*(const Matrix &m);

  friend std::ostream &operator<<(std::ostream&, const Matrix&);

	
  double* operator[](int col)const;

  /*���ظþ����C++ string�ַ�����ʾ*/
  std::string toString() ;

 private:
  double** matrix;//��������
  int rows,cols;//����������
};

#endif // MATRIX_H
