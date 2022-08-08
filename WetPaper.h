#pragma once
#include "Header.h"
#include "Matrix.h"

class WetPaper {
private:
	uint q, n, k;
	Matrix *D; // ramdom matrix (q*n dimention)
	Matrix *b; // parity bits of empty container
	float *Pix; // map of wetpixels. 0 - wet, 1 - dry 
	Matrix* m; // secret message
	Matrix* H; // reduced matrix from D (q*k dimension)
public:
	WetPaper(uint parityArraySize, uint messageSize, float* parityBitsArray, float* secretMessage,float *MapWetPixels) {
		n = parityArraySize;
		q = messageSize;
		k = 0;
		Pix = MapWetPixels;
		for (uint i = 0; i < n; i++) {
			if (Pix[i] == 1)k++;
		}
		b=new Matrix(n, 1); b->LoadMatrix(parityBitsArray, n);
		m = new Matrix(q, 1); m->LoadMatrix(secretMessage, q);
		D = new Matrix(q, n);

		int attempt = 0;		
		do {
			D->GenRand();
			H = D->CompactD(Pix, q, k);
			attempt++;
		} while (((int)(*H) != q) && (attempt < maxAttemptRank));
		if ((int)*H!=q) { printf("Error rank of H is not enouth. I try %d times but not found good matrix D\n", maxAttemptRank); }		
	}
	void InitD(float* D_) { // you can manually init D matrix if need.
		D = new Matrix(q, n);
		D->LoadMatrix(D_, q * n);
		H = D->CompactD(Pix, q, k);		
	}
	void CheckUp(Matrix *res) {
		Matrix receivedMessage(q, 1);
		receivedMessage = (*D) * (*res);
		receivedMessage.vivod();
	}

	Matrix* BuildCode() {						
		Matrix tmp(q, 1);
		Matrix* res = new Matrix(n, 1);
		Matrix* v;
		try {			
			tmp = *D * *b;			
			tmp = (*m) - tmp;							
			v = H->MatrixEquation(tmp, k);			
			
			for (uint t=0,i = 0; i < n; i++){ //repair from v' to v
				if (Pix[i] == 0) {
					(*res)(i, 0) = (*b)(i,0);
				}
				else {
					(*res)(i, 0) = (float)((int)( (*b)(i, 0) + (*v)(t, 0) )%2);
					t++;
				}				
			}			
		}
		catch (int error) {
			printf("Error %d", error);
		}
		return res;
	}
};
