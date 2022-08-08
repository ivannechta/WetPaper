#pragma once
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>



class Matrix {
public:
	bool Error;
	float ** data;
	uint N;
	uint M;
public:
#pragma region Constructor
	Matrix(uint n,uint m) {
		Error = false;
		N = n; M = m;
		data= new float * [N];
		for (int i = 0; i < N; i++) {
			data[i] = new float[M];
		}
	}
	~Matrix() {
		N = M = 0;		
		for (int i = 0; i < N; i++) {
			delete data[i];
		}
		delete data;
	}
#pragma endregion
#pragma region Aux
	int ConvertGalua(float x) {
		if (x < 0)x = -x;
		return (int)x % 2;
	}
	bool GetError() {
		return Error;
	}
	void SetError() {
		Error = true;
	}
	uint GetN(){
		return N;
	}
	uint GetM() {
		return M;
	}
	void LoadMatrix(float *S,int len) {
		if (len != M * N) throw 1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {				
				data[i][j] = S[i * M + j];
			}
		}	
	}
	void GenRand() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				data[i][j]=rand()%2;
			}			
		}	
	}
	void vivod() {
		printf("-------\n");
		for (int i = 0; i < N; i++) {			
			for (int j = 0; j < M; j++) {
				printf("%.2f ",data[i][j]);
			}
			printf("\n");
		}	
	}
	Matrix* MathEquation() { //kramer
		float det_0,det_1;
		Matrix* x = new Matrix(N,1); 
		Matrix reduced(N, M);
		Matrix tmp(N, M-1);
		reduced = *this;
		reduced.M--; //extended -- to normal;		

		det_0 = (float)reduced;
		if (det_0 == 0) { x->SetError(); return x; }
		for (int i = 0; i < N; i++) {
			tmp = reduced;
			for (int j = 0; j < N; j++) {
				tmp(j,i)= data[j][M - 1];
			}
			det_1 = (float)tmp;
			(*x)(i,0) = det_1 / det_0;
			if (GF_2) {
				(*x)(i, 0) = (float)ConvertGalua((*x)(i, 0));
			}
		}
		return x;
	}
	Matrix* MatrixEquation(Matrix &b,int size) {
		int X_size = min(N,size);
		Matrix* t = new Matrix(X_size,X_size+1);
		Matrix* x = new Matrix(X_size, 1);
		for (int i = 0; i < X_size; i++) {
			for (int j = 0; j < X_size; j++) {
				(*t)(i, j) = data[i][j];
			}
			(*t)(i, X_size) = b(i,0);
		}
		x = t->MathEquation();
		delete t;
		return x;
	}
#pragma endregion
#pragma region Operators
	operator float() { //calc Determinant				
		if (N != M) { Error = true; throw 2; return 0; }
		if (N == 2) {
			return data[0][0] * data[1][1] - data[0][1] * data[1][0];
		}
		if (N == 1) {
			return data[0][0];
		}

		int znak = -1;
		float det=0;
		Matrix sub(N-1, M-1);
		
		for (int t = 0; t < N; t++) {
			znak = -znak;

			//form minor			
			for (int i = 1; i < N; i++) {
				for (int tmp=0,j = 0; j < M; j++) {
					if (t == j) { continue; }
					sub(i-1,tmp) = data[i][j];
					tmp++;
				}
			}
			det += (float)znak * data[0][t] * (float)sub;
		}
		return det;
	}
	operator int() { //Rank of matrix

		return 666;
	}
	Matrix &operator =(Matrix &m) {		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				data[i][j]=m(i,j);
			}			
		}
		Error = m.GetError();
		return *this;
	}
	Matrix& operator =(Matrix *m) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				data[i][j] = (*m)(i, j);
			}
		}
		Error = m->GetError();
		return *this;
	}
	Matrix *operator ~() {
		Matrix *m=new Matrix(N, M+M);
		if ((float)*this == 0)throw 0; //det =0, inverse m. is not exist
		//add E matrix at left
		m->M -= M;
		*m = *this;
		m->M += M;		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				(*m)(i, M+j) = (float)(i==j)?1:0;
			}
		}
		//convert to left-triangle matrix
		float tmp; 	int row=0;
		for (int t = 0; t < (*m).N; t++){
			tmp = (*m)(t, t);
			if (tmp == 0) { //change colomns where no 0
				for (int i= t + 1; i < (*m).N; i++) {
					if ((*m)(i, t) != 0) { row = i; i = (*m).N; }
				}
				//exchange
				for (int j = 0; j < (*m).M; j++) {
					tmp = (*m)(t, j);
					(*m)(t, j) = (*m)(row, j);
					(*m)(row, j) = tmp;
				}			
				tmp = (*m)(t, t);
			}
			
				for (int j = 0; j < (*m).M; j++) {
					(*m)(t, j) = (*m)(t, j) / tmp;
					if (GF_2) {
						(*m)(t, j) = (float)ConvertGalua((*m)(t, j));
					}
				}
				float q, w;
				for (int i = 0; i < (*m).N; i++) {
					tmp = (*m)(i, t);
					for (int j = 0; j < (*m).M; j++) {
						if (i != t) {
							q = (*m)(i, j);
							w = (*m)(t, j);
							(*m)(i, j) = q - tmp * w;
							if (GF_2) {
								(*m)(i, j) = (float)ConvertGalua((*m)(i, j));
							}
						}
					}				
				}			
		}
		// extend to normal
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				(*m)(i, j) = (*m)(i, j+M);
			}
		}
		m->M = M;	
		return m;
	}
	Matrix* operator *(Matrix &b) {		
		if (M != b.N) throw 3; //wrong matrix size
		Matrix* c = new Matrix(N, b.M);
		int q, w;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < b.M; j++) {
				(*c)(i, j) = 0;
				for (int tmp = 0; tmp < M; tmp++) {					
					(*c)(i,j) += (data[i][tmp] * b(tmp, j));
					if (GF_2) {
						(*c)(i, j) = (float)ConvertGalua((*c)(i, j));
					}
					
				}
			}
		}
		return c;
	}
	Matrix* operator -(Matrix& b) {
		if (M != b.M) throw 3; //wrong matrix size
		if (N != b.N) throw 3; //wrong matrix size
		Matrix* c = new Matrix(N, M);
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < b.M; j++) {
					(*c)(i, j) =data[i][j]-b(i,j);						
					if (GF_2) {
							(*c)(i, j) = (float)ConvertGalua((*c)(i, j));
					}
			}
		}
		return c;
	}
	Matrix* operator +(Matrix& b) {
		if (M != b.M) throw 3; //wrong matrix size
		if (N != b.N) throw 3; //wrong matrix size
		Matrix* c = new Matrix(N, M);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < b.M; j++) {
				(*c)(i, j) = data[i][j] + b(i, j);				
				if (GF_2) {
					(*c)(i, j) = (float)ConvertGalua((*c)(i, j));
				}
			}
		}
		return c;
	}
	/*Matrix* operator <<(uint n) { //delete column		
		Matrix* c = new Matrix(N, M-1);		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {				
				
			}
		}
		return c;
	}*/
	bool operator ==(Matrix& b) {
		if (M != b.M) throw 3; //wrong matrix size
		if (N != b.N) throw 3; //wrong matrix size		

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (fabs(data[i][j]-b(i, j))>EPS) { return false; }
			}
		}
		return true;
	}
	float operator ()(uint i,uint j)const { 
		return data[i][j];
	}
	float &operator ()(uint i, uint j) {
		return data[i][j];
	}
#pragma endregion	

};
