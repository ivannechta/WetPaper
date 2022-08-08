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
		

	}
	void InitD(float* D_) {
		D = new Matrix(q, n);
		D->LoadMatrix(D_, q * n);
	}

	Matrix* BuildCode() {		
		H = D->CompactD(Pix, q, k);		
		D->vivod();
		try {
			Matrix tmp(q, 1);
			tmp = *D * *b;
			tmp.vivod();
			tmp = (*m) - tmp;
			tmp.vivod();


			Matrix* v;			
			v = H->MatrixEquation(tmp, k);
			v->vivod();
			Matrix* res = new Matrix(n,1);
			for (int t=0,i = 0; i < n; i++) {
				if (Pix[i] == 0) {
					(*res)(i, 0) = (*b)(i,0);
				}
				else {
					(*res)(i, 0) = (*v)(t,0);
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
