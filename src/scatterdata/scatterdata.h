#ifndef SCATTERDATA_H
#define SCATTERDATA_H
/*
  此类将离散数据转换为网格数据
  简均:2009-1-14
 */
#include "../matrix/matrix.h"
#include <string>

struct GridData;

class ScatterData
{
 public:
  /****************************************
    离散数据以矩阵形式传入:
    matrix 为n*3的矩阵
    |          |
    | x1 y1 z1 |
    | x2 y2 z2 |
    | .  .  .  |
    | .  .  .  |
    | xn yn zn |
    |	       |
     	         
  *****************************************/         
  ScatterData(Matrix &data);

  /*默认构造函数*/
  ScatterData();

  ~ScatterData();

  /*设置离散数据*/
  void setScatterData(Matrix &data);

  /*设置网格的垂直等分和水平等分 */
  void setGridding(int horizontal,int vertical);


  /*****************************************

   得到网格矩阵，矩阵中全为z直
                       (maxX,maxY)
          |                 |
          | z11 z12 ... z1h |
          | z21 z22 ... z2h |
          | .   .   ... .   |
          | .   .   ... .   |
          | .   .   ... .   |
          | zv1 zv2 ... zvh |
          |                 |
     (minX,minY)

     minX,maxX,minY,maxY是网格数据坐标的范围

  *******************************************/ 		     
  Matrix& getGridding(double &pminX,double &pmaxX,double &pminY,double &pmaxY);

  Matrix& getGridding();

  void getRange(double &pminX,double &pmaxX,double &pminY,double &pmaxY);


  /*
    指定（x，y）坐标范围，Z值范围，随机生成n对离散数据
  */
  static Matrix& randScatterData(double pminX,double pmaxX,double pminY,double pmaxY,
                          double pminZ,double pmaxZ,int n);

  /*生成DSAA格式文件*/
  void toGridFile(std::string name);

  void toScatterFile(std::string name);

  static bool readGridFile(char* name,GridData &data);

  static bool readScatterFile(char* name,Matrix **data);

 private:


  Matrix *scatterData;//scater data
  Matrix *griddingData;//网格数据
  int slipH;
  int slipV;//水平和垂直网格数
  /*坐标范围*/
  double minX;
  double maxX;
  double minY;
  double maxY;
  double minZ;
  double maxZ;
  double width;
  double height;
};
#endif
