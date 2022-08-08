#include <iostream>
#include "Matrix.h"

//messagesize
#define q 4
//image size (readable pixel)
#define n 5
// writable pixel 
#define k 4 
Matrix* CompactD(Matrix &D, float *Pix) {
	Matrix* H = new Matrix(q,k);
	for (int col = 0, j = 0; j < D.M; j++) {
		if (Pix[j] != 0) {
			for (int i = 0; i < q; i++) {
				(*H)(i, col) = D(i, j);
			}
			col++;
		}
	}
	return H;
}

Matrix* Compactv(Matrix &v, float* Pix) {
	Matrix* v_ = new Matrix(k,1);

	for (int row=0,i = 0; i < v.N; i++) {
		if (Pix[i] != 0) {
			(*v_)(row, 0) = v(i,0);			
			row++;
		}
	}	
	return v_;
}

int main()
{	
	
	
	Matrix D(q, n);
	float D_[q * n] = {
		1,1,1,0,1,
		1,0,1,1,0,
		1,0,1,1,1,
		1,1,0,1,1
	};
	D.LoadMatrix(D_, q*n);
	float Pix[n] = { 0,1,1,1,1 };// ,1,1,0,1,1 };	//Matrix pix(n, 1); pix.LoadMatrix(Pix,n);
	Matrix* H = CompactD(D, Pix);

	
	Matrix m(q,1);
	//Matrix b_(n, 1);
	
	float B[n] = { 1,0,0,1,1 };
	Matrix b(n, 1); b.LoadMatrix(B, n);
	

	float M[q] = { 1,1,1,1 };m.LoadMatrix(M, q);
	
	//read
	
	//b.vivod();	
	D.vivod();
	try {
		Matrix tmp(q, 1);
		tmp = D * b;
		tmp.vivod();
		tmp = m - tmp;
		tmp.vivod();		

		
		Matrix* v;// = Compactv(b, Pix);
		v = H->MatrixEquation(tmp,k);

		v->vivod();
	}
	catch (int error) {
		printf("Error %d",error);	
	}


		

}
