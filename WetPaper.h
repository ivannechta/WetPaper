#pragma once
#include "Header.h"
#include "Matrix.h"

class WetPaper {
private:
	uint q, n, k;
	Matrix *D;
	Matrix *b;
	float *Pix;
	Matrix* m;
	Matrix* H;
public:
	WetPaper(uint image_size, uint message_size, float* image_parity, float* message,float *WetPix) {
		n = image_size;
		q = message_size;
		k = 0;
		Pix = WetPix;
		for (int i = 0; i < n; i++) {
			if (WetPix[i] == 1)k++;
		}
		b=new Matrix(n, 1); b->LoadMatrix(image_parity, n);
		m = new Matrix(q, 1); m->LoadMatrix(message, q);
		D = new Matrix(q, n);

		int attempt = 0;		
		do {
			D->GenRand();
			H = D->CompactD(Pix, q, k);
			attempt++;
		} while (((int)(*H) != q) && (attempt < maxAttemptRank));
		H->vivod();
		printf("rank1=%d\n", (int)*H);
		if ((int)*H!=q) { printf("Error rank of H is not enouth. I try %d times but not found good matrix D\n", maxAttemptRank); }
		H->vivod();
	}
	void InitD(float* D_) { // you can manually init D matrix if need.
		D = new Matrix(q, n);
		D->LoadMatrix(D_, q * n);
		H = D->CompactD(Pix, q, k);
		printf("rank=%d\n",(int)*H);
		H->vivod();
	}
	void CheckUp(Matrix *res) {
		Matrix receivedMessage(q, 1);
		receivedMessage = (*D) * (*res);
		receivedMessage.vivod();
	}

	Matrix* BuildCode() {				
		D->vivod();
		try {
			Matrix tmp(q, 1);
			tmp = *D * *b;
			tmp.vivod();
			tmp = (*m) - tmp;
			printf("m-D*b\n");
			tmp.vivod();

			Matrix* v;			
			H->vivod();
			v = H->MatrixEquation(tmp, k);
			printf("Root v'\n");
			v->vivod();
			Matrix* res = new Matrix(n,1);
			for (int t=0,i = 0; i < n; i++) {
				if (Pix[i] == 0) {
					(*res)(i, 0) = (*b)(i,0);
				}
				else {
					(*res)(i, 0) = (float)((int)( (*b)(i, 0) + (*v)(t, 0) )%2);
					t++;
				}				
			}
			return res;
		}
		catch (int error) {
			printf("Error %d", error);
		}
	}
};
