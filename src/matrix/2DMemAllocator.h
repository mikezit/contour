#ifndef C2DMEMALLOCATOR_H
#define C2DMEMALLOCATOR_H


/***********************************************************************
//        C2DMemAllocator    
//
//        分配函数:
//        AllocMemory2D(T ** &p,int rows,int columns)
//        释放函数:
//        FreeMemory2D(T **&pp)        
//
***********************************************************************/



class C2DMemAllocator  
{
public:
	C2DMemAllocator();

	~C2DMemAllocator();

	static bool AllocMemory2D(double ** &p,int rows,int cols);

	static bool AllocMemory2D(float ** &p,int rows,int cols);

	static void FreeMemory2D(double **&pp);

	static void FreeMemory2D(float **&pp);

};

#endif // !defined(C2DMEMALLOCATOR_H_INCLUDED_)
