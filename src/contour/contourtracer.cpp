#include "contourtracer.h"
#include "../matrix/2DMemAllocator.h"

#define XJUMP 1
#define YJUMP 1

ContourTracer::ContourTracer()
{
     //m_ppGridData = NULL;
     m_pCurveList = NULL;
     m_currentCurveLine = NULL;

     xSide = NULL;
     ySide = NULL;
}

ContourTracer::~ContourTracer()
{
     freeMemory();	
}



bool ContourTracer::executeTracing(float value)
{
     assert( m_gridDataInfo.cols != 0 );

     if( value < m_gridDataInfo.zMin && value > m_gridDataInfo.zMax )
     {
	  return false;
     }

     m_valueTracing = value;

     allocateMemory();

     interpolateTracingValue(); 

     tracingNonClosedContour();

     tracingClosedContour();

     return true;	
}

void ContourTracer::allocateMemory()
{
     int cols = m_gridDataInfo.cols;
     int rows = m_gridDataInfo.rows;
	
     if( xSide == NULL )
     {
	  C2DMemAllocator::AllocMemory2D(xSide,rows,cols-1/*not cols*/);
     }
	
     if( ySide == NULL )
     {
	  C2DMemAllocator::AllocMemory2D(ySide,rows-1/*not rows*/,cols);
     }
}

void ContourTracer::freeMemory()
{
	
     if( xSide != NULL )
     {
	  C2DMemAllocator::FreeMemory2D(xSide);
	  xSide = NULL;
     }
	
     if( ySide != NULL )
     {
	  C2DMemAllocator::FreeMemory2D(ySide);
	  ySide = NULL;
     }
	
}

void ContourTracer::interpolateTracingValue()
{
     assert( xSide != NULL );
     assert( ySide != NULL );
	
     int i,j;
	
     int   rows = m_gridDataInfo.rows;
     int   cols = m_gridDataInfo.cols;
     float  w   = m_valueTracing;
     Matrix pData = m_ppGridData;
	
     float H1,H2;
     float flag; 
     float shift = 0.001f;  


     for(i=0; i<rows ; i++)
     {
	  for(j=0;j<cols-1;j++)
	  {				
	       H1 = pData[i][j]; 		
	       H2 = pData[i][j+1];		

	       if( H1 == H2 )
	       {
		    xSide[i][j] = -2.0f;
	       }
	       else
	       {
		    flag = (w-H1) * (w-H2);
		    if( flag > 0 )
		    {
			 xSide[i][j] = -2.0f;
		    }
		    else if( flag < 0 )
		    {
			 xSide[i][j] = (w-H1) / (H2-H1) ; 
			 assert(xSide[i][j]>=0 && xSide[i][j]<=1.0f);
		    }
		    else if( flag == 0)
		    {
			 if( H1 == w )
			 {
			      H1 += shift;
			 }
			 else
			 {
			      H2 += shift;
			 }
					
			 xSide[i][j] = (w-H1) / (H2-H1) ; 
			
		    }
		    else
		    {
			 assert(false);
		    }

	       }
			
			


	  }
     }

     for(i=0; i<rows-1;i++)
     {
	  for(j=0; j<cols; j++)
	  {			
	       H1 = pData[i][j];            
	       H2 = pData[i+1][j];		     
                                         
	       if( H1 == H2 )               
	       {
		    ySide[i][j] = -2.0f;
	       }
	       else
	       {
		    flag = (w-H1) * (w-H2);
		    if( flag > 0 )
		    {
			 ySide[i][j] = -2.0f;
		    }
		    else if( flag < 0 )
		    {
			 ySide[i][j] = (w-H1) / (H2-H1) ; 
			 assert(ySide[i][j]>=0 && ySide[i][j]<=1.0f);
		    }
		    else if( flag == 0 )
		    {
			 if( H1 == w )
			 {
			      H1 += shift;
			 }
			 else
			 {
			      H2 += shift;
			 }
					
			 ySide[i][j] = (w-H1) / (H2-H1) ; 
		    }
		    else
		    {
			 assert(false);
		    }


	       }

	  }
     }
}

inline void ContourTracer::calcAndSaveOnePointCoord(int i, int j, bool bHorizon,float &x, float &y)
{
		
     if( bHorizon )
     {
	  x = m_gridDataInfo.xMin + ( j + xSide[i][j] ) * deltX;
	  y = m_gridDataInfo.yMin + i * deltY;		
     }
     else
     {
	  x = m_gridDataInfo.xMin + j * deltX;
	  y = m_gridDataInfo.yMin + ( i + ySide[i][j] ) * deltY;
     }


     QPointF point(x,y);
     m_currentCurveLine->data.append(point);

     if(x<m_currentCurveLine->xMin)
	  m_currentCurveLine->xMin = x;
     if(x>m_currentCurveLine->xMax)
	  m_currentCurveLine->xMax = x;

     if(y<m_currentCurveLine->yMin)
	  m_currentCurveLine->yMin = y;
     if(y>m_currentCurveLine->yMax)
	  m_currentCurveLine->yMax = y;


}


void ContourTracer::handlingAfterNextPointFounded(int i, int j, bool bHorizon)
{
//     assert( i>=0 && i<=m_gridDataInfo.rows-1 && j>=0 && j<=m_gridDataInfo.cols-1 );

     nextPoint.i = i;
     nextPoint.j = j;
     nextPoint.bHorV = bHorizon;

     calcAndSaveOnePointCoord(i,j,bHorizon,nextPoint.x,nextPoint.y);

     if( nextPoint.bHorV )
     {
	  xSide[i][j] = -2.0f; //已经追踪过
     }
     else
     {	
	  ySide[i][j] = -2.0f; //已经追踪过
     }
}

void ContourTracer::tracingNextPoint()
{

     if(currentPoint.i > previousPoint.i )
     {

	  fromBottom2TopTracing();
     }
     else if(currentPoint.j > previousPoint.j )
     {

	  fromLeft2RightTracing();
		
     }
     else if( currentPoint.bHorV == true /*curPt_Col_X < currentPoint.x*/ ) 
     {		
	  assert( currentPoint.i <= previousPoint.i &&
		  currentPoint.j <= previousPoint.j );

	  fromTop2BottomTracing();
	
     }
     else
     {
	  assert(currentPoint.bHorV==false);//在纵边上

	  assert( currentPoint.i <= previousPoint.i &&
		  currentPoint.j <= previousPoint.j );

	  fromRight2LeftTracing();
     }
	
}


void ContourTracer::fromBottom2TopTracing()
{

     assert( currentPoint.i > previousPoint.i );   //当前点的行号 > 前一点的行号
     assert( currentPoint.bHorV == true );
	

     static int i;
     i = currentPoint.i; 
     static int j;
     j = currentPoint.j;

     if( isHavingPoint(ySide[i][j]) && isHavingPoint(ySide[i][j+1]) )
     {
		
	  if( ySide[i][j] < ySide[i][j+1] )
	  {
	       handlingAfterNextPointFounded(i,j,false);//在纵边(i,j)上
	  }
	  else if( ySide[i][j] == ySide[i][j+1] )
	  {
	       float xSideIJ = (m_valueTracing - m_ppGridData[i][j]) / ( m_ppGridData[i][j+1] - m_ppGridData[i][j] );
	       if( xSideIJ <= 0.5f )
	       {
		    handlingAfterNextPointFounded(i,j,false);//在纵边(i,j)上
	       }
	       else
	       {
		    handlingAfterNextPointFounded(i,j+1,false);//在纵边(i,j+1)上
	       }

	  }
	  else
	  {
	       handlingAfterNextPointFounded(i,j+1,false);//在纵边(i,j+1)上
	  }

     }
     else
     {
	  if( isHavingPoint(ySide[i][j]) )
	  {
	       handlingAfterNextPointFounded(i,j,false);//在纵边(i,j)上
	  }
	  else if( isHavingPoint(ySide[i][j+1]) )
	  {
	       handlingAfterNextPointFounded(i,j+1,false);//在纵边(i,j+1)上
	  }
	  else if( isHavingPoint(xSide[i+1][j]) )
	  {//两纵边上都没有
	       handlingAfterNextPointFounded(i+1,j,true);//在横边(i+1,j)上
	  }
	  else
	  {//三边上都没有,数据插值出现错误
	       assert(false);
	  }
     }

}

//由左向右追踪
void ContourTracer::fromLeft2RightTracing()
{
     assert( currentPoint.j > previousPoint.j );
     assert( currentPoint.bHorV == false );

     static int i ;
     i= currentPoint.i; 
     static int j;
     j = currentPoint.j;	
     if( isHavingPoint(xSide[i][j]) && isHavingPoint(xSide[i+1][j]) )
     {
		
	  if( xSide[i][j] < xSide[i+1][j] )
	  {
	       handlingAfterNextPointFounded(i,j,true);//在横边(i,j)上
	  }
	  else if( xSide[i][j] == xSide[i+1][j] )
	  {
	       //注意:这里需要重新计算ySide[i][j]，因为在上一次已经被置为-2.0
	       float ySideIJ = ( m_valueTracing - m_ppGridData[i][j]) / ( m_ppGridData[i+1][j] - m_ppGridData[i][j] );
	       if( ySideIJ <= 0.5f )
	       {
		    handlingAfterNextPointFounded(i,j,true);//在横边(i,j)上
	       }
	       else
	       {
		    handlingAfterNextPointFounded(i+1,j,true);//在横边(i+1,j)上
	       }
			
	  }
	  else
	  {
	       handlingAfterNextPointFounded(i+1,j,true);//在横边(i+1,j)上
	  }
		
     }
     else
     {
	  if( isHavingPoint(xSide[i][j]) )
	  {
	       handlingAfterNextPointFounded(i,j,true);//在横边(i,j)上
	  }
	  else if( isHavingPoint(xSide[i+1][j]) )
	  {
	       handlingAfterNextPointFounded(i+1,j,true);//在横边(i+1,j)上
	  }
	  else if( isHavingPoint(ySide[i][j+1]) )
	  {//两横边上都没有
	       handlingAfterNextPointFounded(i,j+1,false);//在纵边(i,j+1)上
	  }
	  else
	  {//三边上都没有
	       assert(false);
	  }
     }
	
}

//由上向下
void ContourTracer::fromTop2BottomTracing()
{
     assert( currentPoint.bHorV == true );	

     static int i;
     i = currentPoint.i;
     static int j;
     j = currentPoint.j;

     if( isHavingPoint(ySide[i-1][j]) && isHavingPoint(ySide[i-1][j+1]) )
     {
		
	  if( ySide[i-1][j] < ySide[i-1][j+1] )
	  {
	       handlingAfterNextPointFounded(i-1,j,false);//在纵边(i-1,j)上
	  }
	  else if( ySide[i-1][j] == ySide[i-1][j+1] )
	  {
	       //注意:这里需要重新计算xSide[i][j]，因为在上一次已经被置为-2.0
	       float xSideIJ = ( m_valueTracing - m_ppGridData[i][j]) / ( m_ppGridData[i][j+1] - m_ppGridData[i][j] );
	       if( /*xSide[i][j]*/ xSideIJ <= 0.5f )
	       {
		    //TRACE0("xSide[i][j] <= 0.5f\n");
		    handlingAfterNextPointFounded(i-1,j,false);//在纵边(i-,j)上
	       }
	       else
	       {
		    handlingAfterNextPointFounded(i-1,j+1,false);//在纵边(i-1,j+1)上
	       }
			
	  }
	  else
	  {
	       handlingAfterNextPointFounded(i-1,j+1,false);//在纵边(i-1,j+1)上
	  }
		
     }
     else
     {
	  if( isHavingPoint(ySide[i-1][j]) )
	  {
	       handlingAfterNextPointFounded(i-1,j,false);//在纵边(i-1,j)上
	  }
	  else if( isHavingPoint(ySide[i-1][j+1]) )
	  {
	       handlingAfterNextPointFounded(i-1,j+1,false);//在纵边(i-1,j+1)上
	  }
	  else if( isHavingPoint(xSide[i-1][j]) )
	  {//两纵边上都没有
	       handlingAfterNextPointFounded(i-1,j,true);//在横边(i-1,j)上
	  }
	  else
	  {//三边上都没有
	       assert(false);
	  }
     }

}


//由右向左
void ContourTracer::fromRight2LeftTracing()
{

     assert( currentPoint.bHorV == false );
	

     static int i;
     i = currentPoint.i; 
     static int j;
     j = currentPoint.j;	

     if( isHavingPoint(xSide[i][j-1]) && isHavingPoint(xSide[i+1][j-1]) )
     {
		
	  if( xSide[i][j-1] < xSide[i+1][j-1] )
	  {
	       handlingAfterNextPointFounded(i,j-1,true);//在横边(i,j-1)上
	  }
	  else if( xSide[i][j] == xSide[i+1][j-1] )
	  {
	       //注意:这里需要重新计算ySide[i][j]，因为在上一次已经被置为-2.0
	       float ySideIJ = ( m_valueTracing - m_ppGridData[i][j]) / ( m_ppGridData[i+1][j] - m_ppGridData[i][j] );
	       if( /*ySide[i][j]*/ ySideIJ <= 0.5f )
	       {
		    handlingAfterNextPointFounded(i,j-1,true);//在横边(i,j-1)上
	       }
	       else
	       {
		    handlingAfterNextPointFounded(i+1,j-1,true);//在横边(i+1,j-1)上
	       }
			
	  }
	  else
	  {
	       handlingAfterNextPointFounded(i+1,j-1,true);//在横边(i+1,j-1)上
	  }
		
     }
     else
     {
	  if( isHavingPoint(xSide[i][j-1]) )
	  {
	       handlingAfterNextPointFounded(i,j-1,true);//在横边(i,j-1)上
	  }
	  else if( isHavingPoint(xSide[i+1][j-1]) )
	  {
	       handlingAfterNextPointFounded(i+1,j-1,true);//在横边(i+1,j-1)上
	  }
	  else if( isHavingPoint(ySide[i][j-1]) )
	  {//两横边上都没有
	       handlingAfterNextPointFounded(i,j-1,false);//在纵边(i,j-1)上
	  }
	  else
	  {//三边上都没有
	       assert(false);
	  }
     }
}


//追踪一条开等值线
void ContourTracer::tracingOneNonClosedContour(CCurve::SType type)
{
     CCurve* pCtrLine = new CCurve;
     pCtrLine->stype = type;
     m_pCurveList->append(pCtrLine);
	
     m_currentCurveLine = pCtrLine;
     m_currentCurveLine->value = m_valueTracing;
     //记录下线头所在边的i，j，横纵边标识
     int startPt_i = currentPoint.i; 
     int startPt_j = currentPoint.j;
     bool startPt_bHoriz = currentPoint.bHorV;

     //验证线头在边界上
//      assert( startPt_i == 0                     ||  /*线头在底边界上*/
// 	     startPt_i == m_gridDataInfo.rows-1 ||  /*线头在上边界上*/
// 	     startPt_j == 0                     ||  /*线头在左边界上*/
// 	     startPt_j == m_gridDataInfo.cols-1     /*线头在右边界上*/ 
// 	  );

     calcAndSaveOnePointCoord(startPt_i,startPt_j,startPt_bHoriz,currentPoint.x,currentPoint.y); //计算出线头的坐标并保存

     startPoint = currentPoint;
	
     if( startPt_bHoriz )
     {
	  xSide[startPt_i][startPt_j] = -2.0f;
     }
     else
     {
	  ySide[startPt_i][startPt_j] = -2.0f;
     }
	
     tracingNextPoint(); //追踪出nextPoint
	
     previousPoint = currentPoint;
     currentPoint = nextPoint;
	
     int cols = m_gridDataInfo.cols;
     int rows = m_gridDataInfo.rows;
	
     bool bIsFinish = (currentPoint.i == 0 && currentPoint.bHorV == true )  ||  
	  (currentPoint.i == rows-1)                            ||  
	  (currentPoint.j == 0 && currentPoint.bHorV == false ) ||  
	  (currentPoint.j == cols-1) ;     
	
     while( !bIsFinish )
     {
	  tracingNextPoint();
		
	  previousPoint = currentPoint;
	  currentPoint = nextPoint;
		
	  bIsFinish = (currentPoint.i == 0 && currentPoint.bHorV == true )  ||
	       (currentPoint.i == rows-1)                            || 
	       (currentPoint.j == 0 && currentPoint.bHorV == false ) ||
	       (currentPoint.j == cols-1) ;
	  if(bIsFinish)
	  {
	       pCtrLine->type = getCurveType(startPoint,currentPoint);
	  }		
     }
}


void ContourTracer::tracingNonClosedContour()
{//该函数的关键是找出开曲线的线头，并设置好追踪前进的方向的条件
	
     int i,j;
     int cols = m_gridDataInfo.cols;
     int rows = m_gridDataInfo.rows;	

     for(j=0; j<cols-1; j+=YJUMP)
     {
	  if( isHavingPoint(xSide[0][j]) )
	  {
	       previousPoint.i = -1;
	       previousPoint.j = j;
	       previousPoint.bHorV = true;

	       currentPoint.i = 0; 
	       currentPoint.j = j;
	       currentPoint.bHorV = true; 

	       tracingOneNonClosedContour(CCurve::Down);	
	  }
     }

     for(i=0; i<rows-1; i+=XJUMP)
     {
	  if( isHavingPoint(ySide[i][0]) )
	  {
	       previousPoint.i = i; 
	       previousPoint.j = -1; //假设前一点在-1列,使其满足左-->右的前进方向
	       previousPoint.bHorV = false;
			
	       currentPoint.i = i; 
	       currentPoint.j = 0; //左边框在第0列，所以设置线头的j为0
	       currentPoint.bHorV = false; 
			
	       tracingOneNonClosedContour(CCurve::Left);	
	  }
     }


     float curPt_Col_X = m_gridDataInfo.xMin + currentPoint.j * deltX;
	
     for(j=0; j<cols-1; j+=YJUMP)
     {
	  if( isHavingPoint(xSide[rows-1][j]) )
	  {
	       previousPoint.i = rows-1; 
	       previousPoint.j = j;
	       previousPoint.bHorV = true;
			
	       currentPoint.i = rows-1; //上边框的行号为rows-1
	       currentPoint.j = j;
	       currentPoint.bHorV = true; //使其符合第三个条件

	       tracingOneNonClosedContour(CCurve::Top);	
	  }
     }


	
     for(i=0; i<rows-1; i+=XJUMP)
     {
	  if( isHavingPoint(ySide[i][cols-1]) )
	  {
	       previousPoint.i = i; 
	       previousPoint.j = cols-1; 
	       previousPoint.bHorV = false;
			
	       currentPoint.i = i; 
	       currentPoint.j = cols-1; //右边框在第cols-1列
	       currentPoint.bHorV = false;  //使其符合第三个条件
	       tracingOneNonClosedContour(CCurve::Right);	
	  }
     }
	
}

void ContourTracer::tracingClosedContour()
{
      int cols = m_gridDataInfo.cols;
     int rows = m_gridDataInfo.rows;

     //搜索所有的除了边框外的纵边,从左到右搜索每一列上的纵边，对于一列，从下到上搜索
     for(int j=1; j<cols-1; j+=YJUMP) //j从1开始
	  for(int i=0; i<rows-1; i+=XJUMP) //i从0开始
	  {
	       if( isHavingPoint(ySide[i][j])) 
	       {
		    tracingOneClosedContour(i,j);				
	       }
			
	  }
}

//从纵边开始追踪一条封闭等值线(注：是从纵边开始搜索)
void ContourTracer::tracingOneClosedContour(int startPt_i, int startPt_j)
{//参数i,j是该闭曲线的第一个等值点的i,j

     CCurve* pCtrLine = new CCurve;
	
     m_pCurveList->append(pCtrLine);
     m_currentCurveLine = pCtrLine;
     m_currentCurveLine->type = CCurve::D;
     m_currentCurveLine->value = m_valueTracing;
     //虚设前一等值点的i,j，让其满足从左向右追踪的条件
     previousPoint.i = startPt_i;
     previousPoint.j = 0;
     previousPoint.bHorV = false;
	
     currentPoint.i = startPt_i;
     currentPoint.j = startPt_j;
     currentPoint.bHorV = false;   //是false，因为是在纵边上
	
	
	
	
     //	float startPt_x;
     //	float startPt_y;
     calcAndSaveOnePointCoord(startPt_i,startPt_j,false/*线头在纵边上*/,currentPoint.x,currentPoint.y);
	
     tracingNextPoint();
	
     previousPoint = currentPoint;
     currentPoint = nextPoint;
	
     bool bColsed = false;
	
     while(!bColsed) 
     {
	  tracingNextPoint();
		
	  previousPoint = currentPoint;
	  currentPoint = nextPoint;
		
	  bColsed = ( currentPoint.i == startPt_i ) && 
	       ( currentPoint.j == startPt_j ) && 
	       ( currentPoint.bHorV == false );
     }
     ySide[startPt_i][startPt_j] = -2.0f; //已经追踪过
}

