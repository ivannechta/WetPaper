#include <iostream>
#include "Header.h"
#include "Matrix.h"
#include "WetPaper.h"

//messageSize
#define q 4
//image size (readable pixel or size of parity array)
#define n 5
// writable pixel (size of dry pixels)
#define k 4 

int main()
{	
	
	float Pix[n] = { 0,1,1,1,1 };

	float B[n] = { 1,0,0,1,1 };	
	float M[q] = { 1,1,1,1 };

	WetPaper *w=new WetPaper(n,q,B,M,Pix);	
	/*you may manually Init D array, not random
	float D_[q * n] = {
		1,1,1,0,1,
		1,0,1,1,0,
		1,0,1,1,1,
		1,1,0,1,1
	};
		w->InitD(D_); 
	*/
	Matrix *res=w->BuildCode();
	printf("This is parity bits to embed\n");
	res->vivod();		
	printf("Receiver read the message\n");
	w->CheckUp(res);	
}
