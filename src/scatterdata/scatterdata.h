#ifndef SCATTERDATA_H
#define SCATTERDATA_H
/*
  ���ཫ��ɢ����ת��Ϊ��������
  ���:2009-1-14
 */
#include "../matrix/matrix.h"
#include <string>

struct GridData;

class ScatterData
{
 public:
  /****************************************
    ��ɢ�����Ծ�����ʽ����:
    matrix Ϊn*3�ľ���
    |          |
    | x1 y1 z1 |
    | x2 y2 z2 |
    | .  .  .  |
    | .  .  .  |
    | xn yn zn |
    |	       |
     	         
  *****************************************/         
  ScatterData(Matrix &data);

  /*Ĭ�Ϲ��캯��*/
  ScatterData();

  ~ScatterData();

  /*������ɢ����*/
  void setScatterData(Matrix &data);

  /*��������Ĵ�ֱ�ȷֺ�ˮƽ�ȷ� */
  void setGridding(int horizontal,int vertical);


  /*****************************************

   �õ�������󣬾�����ȫΪzֱ
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

     minX,maxX,minY,maxY��������������ķ�Χ

  *******************************************/ 		     
  Matrix& getGridding(double &pminX,double &pmaxX,double &pminY,double &pmaxY);

  Matrix& getGridding();

  void getRange(double &pminX,double &pmaxX,double &pminY,double &pmaxY);


  /*
    ָ����x��y�����귶Χ��Zֵ��Χ���������n����ɢ����
  */
  static Matrix& randScatterData(double pminX,double pmaxX,double pminY,double pmaxY,
                          double pminZ,double pmaxZ,int n);

  /*����DSAA��ʽ�ļ�*/
  void toGridFile(std::string name);

  void toScatterFile(std::string name);

  static bool readGridFile(char* name,GridData &data);

  static bool readScatterFile(char* name,Matrix **data);

 private:


  Matrix *scatterData;//scater data
  Matrix *griddingData;//��������
  int slipH;
  int slipV;//ˮƽ�ʹ�ֱ������
  /*���귶Χ*/
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
