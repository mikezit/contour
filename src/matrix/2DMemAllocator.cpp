#include "2DMemAllocator.h"
#include "string.h"
#include <QDebug>

C2DMemAllocator::C2DMemAllocator()
{

}

C2DMemAllocator::~C2DMemAllocator()
{

}

void C2DMemAllocator::FreeMemory2D(double **&pp)
{
	//TRACE("in FreeMemory2D\n");
	if(pp)
	{//释放顺序::一维指针-->二维指针
		
		delete []pp[0];
		pp[0]=NULL;
		
		delete []pp;
		pp=NULL;
	}
}


bool C2DMemAllocator::AllocMemory2D(double ** &p,int rows,int columns)
{

	double **pp;
	pp=NULL;
	pp=new double*[rows];
	if (!pp)
	{
	     return false;
	}
	
	pp[0]=new double [rows*columns];//allocate a big block
	if (!pp[0])
	{
	     return false;
	}
	for(int i=1;i<rows;i++)
	{
	     pp[i]=pp[0]+(long)columns*i;
	}

	p = pp;
	
	return true;
}

void C2DMemAllocator::FreeMemory2D(float **&pp)
{
	//TRACE("in FreeMemory2D\n");
	if(pp)
	{//释放顺序::一维指针-->二维指针
		
		delete []pp[0];
		pp[0]=NULL;
		
		delete []pp;
		pp=NULL;
	}
}


bool C2DMemAllocator::AllocMemory2D(float ** &p,int rows,int columns)
{

	float **pp;
	pp=NULL;
	pp=new float*[rows];
	if (!pp)
	{
	  qDebug()<<"false";
		return false;
	}
	
	pp[0]=new float [rows*columns];//allocate a big block
	if (!pp[0])
	{
	  qDebug()<<"false";
		return false;
	}
	for(int i=1;i<rows;i++)
	{
		pp[i]=pp[0]+(long)columns*i;
	}

	p = pp;
	
	return true;
}
