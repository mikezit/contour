#ifndef CONTOURTRACER_H
#define CONTOURTRACER_H

#include "contourstruct.h"
#include "../matrix/matrix.h"
#include <cmath>
#include <QDebug>


class ContourTracer
{
  public:
    ContourTracer();
    ~ContourTracer();

    void setGridDataInfo(CGridDataInfo& dataInfo);
    void setInput(Matrix& ppGridData);
    void setOutput(CCurveList* pCurveList);
    bool executeTracing(float value);

  private:

    struct IsoPoint
    {
	int i;
	int j;
	bool bHorV; 
	float x; 
	float y;
	IsoPoint(){	memset(this,0,sizeof(IsoPoint));}

    }previousPoint,currentPoint,nextPoint,startPoint;
	
    float **xSide;
    float **ySide; 

  private:
    CCurve::Type getCurveType(const IsoPoint &start,const IsoPoint &end);
    bool isHavingPoint(float r);  
    void allocateMemory();
    void freeMemory();
    void interpolateTracingValue(); //扫描并计算纵、横边上等值点的情况
    void tracingNextPoint(); //追踪下一个等值点


    void fromBottom2TopTracing();
    void fromLeft2RightTracing();
    void fromTop2BottomTracing();
    void fromRight2LeftTracing();


    void handlingAfterNextPointFounded(int i, int j, bool bHorizon); //当下一个等值点找到后做相应的处理
    void calcAndSaveOnePointCoord(int i, int j, bool bHorizon,float &x, float &y);//计算一个等值点的坐标并保存
	
    void tracingOneNonClosedContour(CCurve::SType type);
    void tracingNonClosedContour();
    void tracingOneClosedContour(int i, int j);
    void tracingClosedContour();
	

  private:
    //输入数据
    CGridDataInfo m_gridDataInfo;  //网格数据信息
    Matrix        m_ppGridData;    //网格数据
    float         m_valueTracing;  //当前要追踪的值
    float deltX;
    float deltY;
    float dx;
    float dy;
    bool needAllocate;


    //输出数据的存放位置(需由外部在执行追踪前设定)
    CCurveList*  m_pCurveList;      //存储追踪出来的等值线链的坐标

    //保存输出数据时的帮助变量
    CCurve*     m_currentCurveLine; //指向当前的等值线曲线

  private:
    ContourTracer(const ContourTracer& rhs); //not implimented
    ContourTracer& operator=(const ContourTracer& rhs);//not implimented
		
};

inline void ContourTracer::setInput(Matrix& ppGridData)
{
     m_ppGridData = ppGridData;
}

inline void ContourTracer::setOutput(CCurveList* pCurveList)
{//指定输出位置
    assert( pCurveList != NULL );
    m_pCurveList = pCurveList;
}

inline void ContourTracer::setGridDataInfo(CGridDataInfo& dataInfo)
{
    m_gridDataInfo = dataInfo;
    deltX = (m_gridDataInfo.xMax - m_gridDataInfo.xMin) / ( m_gridDataInfo.cols - 1 );
    deltY = (m_gridDataInfo.yMax - m_gridDataInfo.yMin) / ( m_gridDataInfo.rows - 1 );
    dx =  m_gridDataInfo.xMax-m_gridDataInfo.xMin;
    dy =  m_gridDataInfo.yMax-m_gridDataInfo.yMin;
     //1.为xSide和ySide分配内存空间
    freeMemory();
}

inline bool ContourTracer::isHavingPoint(float r)
{
    //边上是否有等值点存在
    if( r == -2.0f )
    {
	return FALSE;
    }
    else
    {
	/*r属于[0,1] (闭区间)*/
	if( r>1 || r<0)
	    return FALSE;
	else
	    return TRUE;
    }
}

inline CCurve::Type ContourTracer::getCurveType(const IsoPoint &start,const IsoPoint &end)
{

     float row = end.x - start.x;
     float col = end.y - start.y;

     if((row != 0 && fabs(col) == dy) ||
	     (col != 0 && fabs(row) == dx))
	  return CCurve::C;

     else if( ( row == 0 && (start.x == m_gridDataInfo.xMin ||  start.x == m_gridDataInfo.xMax ) && col !=0) ||
	 ( col == 0 && (start.y ==m_gridDataInfo.yMin || start.y == m_gridDataInfo.yMax ) && row !=0))
	  return CCurve::A;

     else if( (row != 0 && row !=  dx) &&
	 (col != 0 && col !=  dy))
	  return CCurve::B;


}

#endif
