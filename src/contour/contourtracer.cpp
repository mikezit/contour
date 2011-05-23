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
	  xSide[i][j] = -2.0f; //�Ѿ�׷�ٹ�
     }
     else
     {	
	  ySide[i][j] = -2.0f; //�Ѿ�׷�ٹ�
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
	  assert(currentPoint.bHorV==false);//���ݱ���

	  assert( currentPoint.i <= previousPoint.i &&
		  currentPoint.j <= previousPoint.j );

	  fromRight2LeftTracing();
     }
	
}


void ContourTracer::fromBottom2TopTracing()
{

     assert( currentPoint.i > previousPoint.i );   //��ǰ����к� > ǰһ����к�
     assert( currentPoint.bHorV == true );
	

     static int i;
     i = currentPoint.i; 
     static int j;
     j = currentPoint.j;

     if( isHavingPoint(ySide[i][j]) && isHavingPoint(ySide[i][j+1]) )
     {
		
	  if( ySide[i][j] < ySide[i][j+1] )
	  {
	       handlingAfterNextPointFounded(i,j,false);//���ݱ�(i,j)��
	  }
	  else if( ySide[i][j] == ySide[i][j+1] )
	  {
	       float xSideIJ = (m_valueTracing - m_ppGridData[i][j]) / ( m_ppGridData[i][j+1] - m_ppGridData[i][j] );
	       if( xSideIJ <= 0.5f )
	       {
		    handlingAfterNextPointFounded(i,j,false);//���ݱ�(i,j)��
	       }
	       else
	       {
		    handlingAfterNextPointFounded(i,j+1,false);//���ݱ�(i,j+1)��
	       }

	  }
	  else
	  {
	       handlingAfterNextPointFounded(i,j+1,false);//���ݱ�(i,j+1)��
	  }

     }
     else
     {
	  if( isHavingPoint(ySide[i][j]) )
	  {
	       handlingAfterNextPointFounded(i,j,false);//���ݱ�(i,j)��
	  }
	  else if( isHavingPoint(ySide[i][j+1]) )
	  {
	       handlingAfterNextPointFounded(i,j+1,false);//���ݱ�(i,j+1)��
	  }
	  else if( isHavingPoint(xSide[i+1][j]) )
	  {//���ݱ��϶�û��
	       handlingAfterNextPointFounded(i+1,j,true);//�ں��(i+1,j)��
	  }
	  else
	  {//�����϶�û��,���ݲ�ֵ���ִ���
	       assert(false);
	  }
     }

}

//��������׷��
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
	       handlingAfterNextPointFounded(i,j,true);//�ں��(i,j)��
	  }
	  else if( xSide[i][j] == xSide[i+1][j] )
	  {
	       //ע��:������Ҫ���¼���ySide[i][j]����Ϊ����һ���Ѿ�����Ϊ-2.0
	       float ySideIJ = ( m_valueTracing - m_ppGridData[i][j]) / ( m_ppGridData[i+1][j] - m_ppGridData[i][j] );
	       if( ySideIJ <= 0.5f )
	       {
		    handlingAfterNextPointFounded(i,j,true);//�ں��(i,j)��
	       }
	       else
	       {
		    handlingAfterNextPointFounded(i+1,j,true);//�ں��(i+1,j)��
	       }
			
	  }
	  else
	  {
	       handlingAfterNextPointFounded(i+1,j,true);//�ں��(i+1,j)��
	  }
		
     }
     else
     {
	  if( isHavingPoint(xSide[i][j]) )
	  {
	       handlingAfterNextPointFounded(i,j,true);//�ں��(i,j)��
	  }
	  else if( isHavingPoint(xSide[i+1][j]) )
	  {
	       handlingAfterNextPointFounded(i+1,j,true);//�ں��(i+1,j)��
	  }
	  else if( isHavingPoint(ySide[i][j+1]) )
	  {//������϶�û��
	       handlingAfterNextPointFounded(i,j+1,false);//���ݱ�(i,j+1)��
	  }
	  else
	  {//�����϶�û��
	       assert(false);
	  }
     }
	
}

//��������
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
	       handlingAfterNextPointFounded(i-1,j,false);//���ݱ�(i-1,j)��
	  }
	  else if( ySide[i-1][j] == ySide[i-1][j+1] )
	  {
	       //ע��:������Ҫ���¼���xSide[i][j]����Ϊ����һ���Ѿ�����Ϊ-2.0
	       float xSideIJ = ( m_valueTracing - m_ppGridData[i][j]) / ( m_ppGridData[i][j+1] - m_ppGridData[i][j] );
	       if( /*xSide[i][j]*/ xSideIJ <= 0.5f )
	       {
		    //TRACE0("xSide[i][j] <= 0.5f\n");
		    handlingAfterNextPointFounded(i-1,j,false);//���ݱ�(i-,j)��
	       }
	       else
	       {
		    handlingAfterNextPointFounded(i-1,j+1,false);//���ݱ�(i-1,j+1)��
	       }
			
	  }
	  else
	  {
	       handlingAfterNextPointFounded(i-1,j+1,false);//���ݱ�(i-1,j+1)��
	  }
		
     }
     else
     {
	  if( isHavingPoint(ySide[i-1][j]) )
	  {
	       handlingAfterNextPointFounded(i-1,j,false);//���ݱ�(i-1,j)��
	  }
	  else if( isHavingPoint(ySide[i-1][j+1]) )
	  {
	       handlingAfterNextPointFounded(i-1,j+1,false);//���ݱ�(i-1,j+1)��
	  }
	  else if( isHavingPoint(xSide[i-1][j]) )
	  {//���ݱ��϶�û��
	       handlingAfterNextPointFounded(i-1,j,true);//�ں��(i-1,j)��
	  }
	  else
	  {//�����϶�û��
	       assert(false);
	  }
     }

}


//��������
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
	       handlingAfterNextPointFounded(i,j-1,true);//�ں��(i,j-1)��
	  }
	  else if( xSide[i][j] == xSide[i+1][j-1] )
	  {
	       //ע��:������Ҫ���¼���ySide[i][j]����Ϊ����һ���Ѿ�����Ϊ-2.0
	       float ySideIJ = ( m_valueTracing - m_ppGridData[i][j]) / ( m_ppGridData[i+1][j] - m_ppGridData[i][j] );
	       if( /*ySide[i][j]*/ ySideIJ <= 0.5f )
	       {
		    handlingAfterNextPointFounded(i,j-1,true);//�ں��(i,j-1)��
	       }
	       else
	       {
		    handlingAfterNextPointFounded(i+1,j-1,true);//�ں��(i+1,j-1)��
	       }
			
	  }
	  else
	  {
	       handlingAfterNextPointFounded(i+1,j-1,true);//�ں��(i+1,j-1)��
	  }
		
     }
     else
     {
	  if( isHavingPoint(xSide[i][j-1]) )
	  {
	       handlingAfterNextPointFounded(i,j-1,true);//�ں��(i,j-1)��
	  }
	  else if( isHavingPoint(xSide[i+1][j-1]) )
	  {
	       handlingAfterNextPointFounded(i+1,j-1,true);//�ں��(i+1,j-1)��
	  }
	  else if( isHavingPoint(ySide[i][j-1]) )
	  {//������϶�û��
	       handlingAfterNextPointFounded(i,j-1,false);//���ݱ�(i,j-1)��
	  }
	  else
	  {//�����϶�û��
	       assert(false);
	  }
     }
}


//׷��һ������ֵ��
void ContourTracer::tracingOneNonClosedContour(CCurve::SType type)
{
     CCurve* pCtrLine = new CCurve;
     pCtrLine->stype = type;
     m_pCurveList->append(pCtrLine);
	
     m_currentCurveLine = pCtrLine;
     m_currentCurveLine->value = m_valueTracing;
     //��¼����ͷ���ڱߵ�i��j�����ݱ߱�ʶ
     int startPt_i = currentPoint.i; 
     int startPt_j = currentPoint.j;
     bool startPt_bHoriz = currentPoint.bHorV;

     //��֤��ͷ�ڱ߽���
//      assert( startPt_i == 0                     ||  /*��ͷ�ڵױ߽���*/
// 	     startPt_i == m_gridDataInfo.rows-1 ||  /*��ͷ���ϱ߽���*/
// 	     startPt_j == 0                     ||  /*��ͷ����߽���*/
// 	     startPt_j == m_gridDataInfo.cols-1     /*��ͷ���ұ߽���*/ 
// 	  );

     calcAndSaveOnePointCoord(startPt_i,startPt_j,startPt_bHoriz,currentPoint.x,currentPoint.y); //�������ͷ�����겢����

     startPoint = currentPoint;
	
     if( startPt_bHoriz )
     {
	  xSide[startPt_i][startPt_j] = -2.0f;
     }
     else
     {
	  ySide[startPt_i][startPt_j] = -2.0f;
     }
	
     tracingNextPoint(); //׷�ٳ�nextPoint
	
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
{//�ú����Ĺؼ����ҳ������ߵ���ͷ�������ú�׷��ǰ���ķ��������
	
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
	       previousPoint.j = -1; //����ǰһ����-1��,ʹ��������-->�ҵ�ǰ������
	       previousPoint.bHorV = false;
			
	       currentPoint.i = i; 
	       currentPoint.j = 0; //��߿��ڵ�0�У�����������ͷ��jΪ0
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
			
	       currentPoint.i = rows-1; //�ϱ߿���к�Ϊrows-1
	       currentPoint.j = j;
	       currentPoint.bHorV = true; //ʹ����ϵ���������

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
	       currentPoint.j = cols-1; //�ұ߿��ڵ�cols-1��
	       currentPoint.bHorV = false;  //ʹ����ϵ���������
	       tracingOneNonClosedContour(CCurve::Right);	
	  }
     }
	
}

void ContourTracer::tracingClosedContour()
{
      int cols = m_gridDataInfo.cols;
     int rows = m_gridDataInfo.rows;

     //�������еĳ��˱߿�����ݱ�,����������ÿһ���ϵ��ݱߣ�����һ�У����µ�������
     for(int j=1; j<cols-1; j+=YJUMP) //j��1��ʼ
	  for(int i=0; i<rows-1; i+=XJUMP) //i��0��ʼ
	  {
	       if( isHavingPoint(ySide[i][j])) 
	       {
		    tracingOneClosedContour(i,j);				
	       }
			
	  }
}

//���ݱ߿�ʼ׷��һ����յ�ֵ��(ע���Ǵ��ݱ߿�ʼ����)
void ContourTracer::tracingOneClosedContour(int startPt_i, int startPt_j)
{//����i,j�Ǹñ����ߵĵ�һ����ֵ���i,j

     CCurve* pCtrLine = new CCurve;
	
     m_pCurveList->append(pCtrLine);
     m_currentCurveLine = pCtrLine;
     m_currentCurveLine->type = CCurve::D;
     m_currentCurveLine->value = m_valueTracing;
     //����ǰһ��ֵ���i,j�����������������׷�ٵ�����
     previousPoint.i = startPt_i;
     previousPoint.j = 0;
     previousPoint.bHorV = false;
	
     currentPoint.i = startPt_i;
     currentPoint.j = startPt_j;
     currentPoint.bHorV = false;   //��false����Ϊ�����ݱ���
	
	
	
	
     //	float startPt_x;
     //	float startPt_y;
     calcAndSaveOnePointCoord(startPt_i,startPt_j,false/*��ͷ���ݱ���*/,currentPoint.x,currentPoint.y);
	
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
     ySide[startPt_i][startPt_j] = -2.0f; //�Ѿ�׷�ٹ�
}

