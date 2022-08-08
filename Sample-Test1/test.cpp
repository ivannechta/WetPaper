#include "pch.h"
#include "..\Matrix.h"
#include "..\Header.h"
TEST(Determinant, Size1) {
	Matrix m(1, 1);
	m(0, 0) = 5;
  EXPECT_EQ((float)m, 5);
}
TEST(Determinant, Size2) {
	Matrix m(2, 2);
	float s[] = {
		1,2,
		3,-1
	};
	m.LoadMatrix(s,4);
	EXPECT_EQ((float)m, -7);
}
TEST(Determinant, Size3) {
	Matrix m(3, 3);
	float s[] = {
		1,	0, -2,
		3,	2,	1,
		1,	2,-2
	};
	m.LoadMatrix(s, 9);
	EXPECT_EQ((float)m, -14);
}
TEST(Determinant, Size4) {
	Matrix m(4, 4);
	float s[] = {
		1,2,3,4,
		5,9,0,7,
		5,6,78,9,
		5,9,-5,6
	};
	m.LoadMatrix(s, 16);
	EXPECT_EQ((float)m, -82);
}

TEST(MathEquation, Kramer3_4) {
	if (GF_2 == true) { EXPECT_TRUE(true); return; }
	Matrix a(3, 4);
	Matrix b(3, 1),res(3,1);
	float A[] = {
		1,0,2,2,
		-2,2,1,5,
		-3,1,4,1
	};
	float B[] = {
		4.0f / 3.0f,
		11.0f / 3.0f,
		1.0f / 3.0f,
	};
	a.LoadMatrix(A, 12);
	res.LoadMatrix(B, 3);	
	b = a.MathEquation();
	EXPECT_TRUE((b==res)&&(b.GetError()==false));
}
TEST(MathEquation, Kramer3_4_no1) {
	Matrix a(3, 4);
	Matrix b(3, 1), res(3, 1);
	float A[] = {
		1,2,3,4,
		5,6,7,8,
		9,10,11,12
	};
	float B[] = {
		4.0f / 3.0f,
		11.0f / 3.0f,
		1.0f / 3.0f,
	};
	a.LoadMatrix(A, 12);
	res.LoadMatrix(B, 3);
	b = a.MathEquation();
	EXPECT_TRUE(b.GetError() == true);
}

TEST(MathEquation, Kramer3_4_no2) {
	Matrix a(3, 4);
	Matrix b(3, 1), res(3, 1);
	float A[] = {
		1,2,3,1000,
		5,6,7,-8,
		9,10,11,12
	};
	float B[] = {
		4.0f / 3.0f,
		11.0f / 3.0f,
		1.0f / 3.0f,
	};
	a.LoadMatrix(A, 12);
	res.LoadMatrix(B, 3);
	b = a.MathEquation();
	EXPECT_TRUE(b.GetError() == true);
}

TEST(Inverse, Size4_1) {
	if (GF_2 == true) { EXPECT_TRUE(true); return; }	

	Matrix a(4, 4);
	Matrix b(4, 4);
	Matrix res(4, 4);
	
	float A[] = {
		7, 2,10 , 1,
		-2,4,-10, 4,
		2, 1,10 , -2,
		4, 8,-6 , 1
	};
	float R[] = {
		7.0f / 61,  -10.0f / 61,   -14.0f / 61, 5.0f / 61,
		-4.0f / 61, 83.0f / 793,   165.0f / 793,50.0f / 793,
		1.0f / 61,  111.0f / 1586, 96.0f / 793, -43.0f / 793,
		10.0f / 61, 189.0f / 793,  -16.0f / 793,-125.0f / 793
	};	
	a.LoadMatrix(A, 16);
	res.LoadMatrix(R, 16);
	b = ~a;
	EXPECT_TRUE(b == res);
	EXPECT_TRUE(b.GetError() == false);

	
}

TEST(Inverse, Size4_2) {
	Matrix a(4, 4);
	Matrix b(4, 4);
	Matrix res(4, 4);

	float A[] = {
		1, 1,1 , 0,
		1,0,1, 1,
		1, 0,0 , 1,
		0, 0,1 , 0
	};

	float R[] = {
		1,1,-1,-2,
		0,-1,1,1,
		0,0,0,1,
		-1,0,0,1
	};

	a.LoadMatrix(A, 16);	
	EXPECT_THROW(b = ~a, int);
}


TEST(Inverse, Size4_3) {

	if (GF_2 != true) { EXPECT_TRUE(true); return; }

	Matrix a(4, 4);
	Matrix b(4, 4);
	Matrix res(4, 4);

	float A[] = {
		1, 1,1 , 0,
		1,0,1, 1,
		1, 1,0 , 1,
		0, 0,1 , 0
	};

	float R[] = {
		1,1,1,0,
		0,1,1,1,
		0,0,0,1,
		1,0,1,1
	};

	a.LoadMatrix(A, 16);
	res.LoadMatrix(R, 16);
	b = ~a;
	EXPECT_TRUE(b == res);
	EXPECT_TRUE(b.GetError() == false);
}

TEST(MatrixEq, Size_3_1) {

	if (GF_2 == true) { EXPECT_TRUE(true); return; }
	Matrix a(3, 2);
	Matrix* x;
	Matrix b(3, 1), res(2, 1);
	float A[] = {
		1,2,
		3,4,
		-1,0
	};
	float B[] = {
		6,16,-4
	};
	float Res[] = {
		4,1
	};
	a.LoadMatrix(A, 6);
	b.LoadMatrix(B, 3);
	res.LoadMatrix(Res, 2);

	x=a.MatrixEquation(b,2);
	EXPECT_TRUE(*x==res);
}

TEST(MatrixEq, Size_4_1) {

	if (GF_2 == true) { EXPECT_TRUE(true); return; }
	Matrix a(4, 4);
	Matrix* x;
	Matrix b(4, 1), res(4, 1);
	float A[] = {
		0,0,1,0,
		1,0,0,1,
		0,1,0,1,
		1,1,1,0
	};
	float B[] = {
		1,0,1,0
	};
	float Res[] = {
		1,0,1,1
	};
	a.LoadMatrix(A, 16);
	b.LoadMatrix(B, 4);
	res.LoadMatrix(Res, 4);

	x = a.MatrixEquation(b, 4);
	EXPECT_TRUE(*x == res);
}
TEST(WetCode, Size4_5_4__1) {
	if (GF_2 != true) { EXPECT_TRUE(true); return; }
	// q=4, n=4, k=4
	Matrix res(4,1);
	float Res[] = {1,1,0,1};
	res.LoadMatrix(Res,4);

	Matrix D(4, 5);
	float D_[4 * 5] = {
		1,1,1,0,1,
		1,0,1,1,0,
		1,0,1,1,1,
		1,1,0,1,1
	};
	D.LoadMatrix(D_, 4 * 5);
	float Pix[5] = { 0,1,1,1,1 };
	Matrix* H = D.CompactD(Pix,4,4);

	Matrix m(4, 1);	

	float B[5] = { 1,0,0,1,1 };
	Matrix b(5, 1); b.LoadMatrix(B, 5);


	float M[4] = { 1,1,1,1 }; m.LoadMatrix(M, 4);

	//read	
		Matrix tmp(4, 1);
		tmp = D * b;
		tmp.vivod();
		tmp = m - tmp;
		tmp.vivod();
		Matrix* v;
		v = H->MatrixEquation(tmp, 4);
		EXPECT_TRUE(*v==res);	
}







