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
    void interpolateTracingValue(); //ɨ�貢�����ݡ�����ϵ�ֵ������
    void tracingNextPoint(); //׷����һ����ֵ��


    void fromBottom2TopTracing();
    void fromLeft2RightTracing();
    void fromTop2BottomTracing();
    void fromRight2LeftTracing();


    void handlingAfterNextPointFounded(int i, int j, bool bHorizon); //����һ����ֵ���ҵ�������Ӧ�Ĵ���
    void calcAndSaveOnePointCoord(int i, int j, bool bHorizon,float &x, float &y);//����һ����ֵ������겢����
	
    void tracingOneNonClosedContour(CCurve::SType type);
    void tracingNonClosedContour();
    void tracingOneClosedContour(int i, int j);
    void tracingClosedContour();
	

  private:
    //��������
    CGridDataInfo m_gridDataInfo;  //����������Ϣ
    Matrix        m_ppGridData;    //��������
    float         m_valueTracing;  //��ǰҪ׷�ٵ�ֵ
    float deltX;
    float deltY;
    float dx;
    float dy;
    bool needAllocate;


    //������ݵĴ��λ��(�����ⲿ��ִ��׷��ǰ�趨)
    CCurveList*  m_pCurveList;      //�洢׷�ٳ����ĵ�ֵ����������

    //�����������ʱ�İ�������
    CCurve*     m_currentCurveLine; //ָ��ǰ�ĵ�ֵ������

  private:
    ContourTracer(const ContourTracer& rhs); //not implimented
    ContourTracer& operator=(const ContourTracer& rhs);//not implimented
		
};

inline void ContourTracer::setInput(Matrix& ppGridData)
{
     m_ppGridData = ppGridData;
}

inline void ContourTracer::setOutput(CCurveList* pCurveList)
{//ָ�����λ��
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
     //1.ΪxSide��ySide�����ڴ�ռ�
    freeMemory();
}

inline bool ContourTracer::isHavingPoint(float r)
{
    //�����Ƿ��е�ֵ�����
    if( r == -2.0f )
    {
	return FALSE;
    }
    else
    {
	/*r����[0,1] (������)*/
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
