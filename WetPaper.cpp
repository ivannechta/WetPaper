#include <iostream>
#include "Header.h"
#include "Matrix.h"
#include "WetPaper.h"

//messagesize
#define q 4
//image size (readable pixel)
#define n 5
// writable pixel 
#define k 4 

int main()
{	
	float D_[q * n] = {
		1,1,1,0,1,
		1,0,1,1,0,
		1,0,1,1,1,
		1,1,0,1,1
	};	
	float Pix[n] = { 0,1,1,1,1 };

	float B[n] = { 1,0,0,1,1 };	
	float M[q] = { 1,1,1,1 };

	WetPaper *w=new WetPaper(n,q,B,M,Pix);	
	//w->InitD(D_);
	Matrix *res=w->BuildCode();
	res->vivod();	
	w->CheckUp(res);
}
