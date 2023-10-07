#include <iostream>
#include "Matrix.h"
using namespace std;

template <typename T>
void Strassen(Matrix<T>& A, Matrix<T>& B, Matrix<T>& C, int n)
{
	//Base case
	if (n == 1)
	{
		C[0][0] = C[0][0] + A[0][0] * B[0][0];
		return;
	}

	//Divide - and - Conquer
	Matrix<T> A11(n / 2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			A11[i][j] = A[i][j];
	Matrix<T> A12(n / 2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			A12[i][j] = A[i][j + n / 2];
	Matrix<T> A21(n / 2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			A21[i][j] = A[i + n / 2][j];
	Matrix<T> A22(n / 2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			A22[i][j] = A[i + n / 2][j + n / 2];

	Matrix<T> B11(n / 2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			B11[i][j] = B[i][j];
	Matrix<T> B12(n / 2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			B12[i][j] = B[i][j + n / 2];
	Matrix<T> B21(n / 2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			B21[i][j] = B[i + n / 2][j];
	Matrix<T> B22(n / 2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			B22[i][j] = B[i + n / 2][j + n / 2];

	Matrix<T> C11(n / 2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C11[i][j] = C[i][j];
	Matrix<T> C12(n / 2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C12[i][j] = C[i][j + n / 2];
	Matrix<T> C21(n / 2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C21[i][j] = C[i + n / 2][j];
	Matrix<T> C22(n / 2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C22[i][j] = C[i + n / 2][j + n / 2];

	Matrix<T> S1(n / 2, n / 2); S1 = B12 - B22;
	Matrix<T> S2(n / 2, n / 2); S2 = A11 + A12;
	Matrix<T> S3(n / 2, n / 2); S3 = A21 + A22;
	Matrix<T> S4(n / 2, n / 2); S4 = B21 - B11;
	Matrix<T> S5(n / 2, n / 2); S5 = A11 + A22;
	Matrix<T> S6(n / 2, n / 2);	S6 = B11 + B22;
	Matrix<T> S7(n / 2, n / 2);	S7 = A12 - A22;
	Matrix<T> S8(n / 2, n / 2);	S8 = B21 + B22;
	Matrix<T> S9(n / 2, n / 2);	S9 = A11 - A21;
	Matrix<T> S10(n / 2, n / 2); S10 = B11 + B12;
	
	Matrix<T> P1(n / 2, n / 2);
	Matrix<T> P2(n / 2, n / 2);
	Matrix<T> P3(n / 2, n / 2);
	Matrix<T> P4(n / 2, n / 2);
	Matrix<T> P5(n / 2, n / 2);
	Matrix<T> P6(n / 2, n / 2);
	Matrix<T> P7(n / 2, n / 2);

	Strassen(A11, S1, P1, n / 2);
	Strassen(S2, B22, P2, n / 2);
	Strassen(S3, B11, P3, n / 2);
	Strassen(A22, S4, P4, n / 2);
	Strassen(S5, S6, P5, n / 2);
	Strassen(S7, S8, P6, n / 2);
	Strassen(S9, S10, P7, n / 2);

	C11 = C11 + P5 + P4 - P2 + P6;
	C12 = C12 + P1 + P2;
	C21 = C21 + P3 + P4;
	C22 = C22 + P5 + P1 - P3 - P7;

	//Combine
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C[i][j] = C11[i][j];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C[i + n / 2][j] = C21[i][j];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C[i][j + n / 2] = C12[i][j];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C[i + n / 2][j + n / 2] = C22[i][j];
}

int main()
{
	Matrix<int> matA(4, 4);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			matA[i][j] = i + j;
	
	Matrix<int> matI(4, 4);
	for (int i = 0; i < 4; i++)
		matI[i][i] = 1;

	Matrix<int> matC(4, 4);
	Strassen(matA, matI, matC, 4);
	cout << "행렬 A" << endl;
	cout << matA;
	cout << "행렬 A * 항등행렬" << endl;
	cout << matC;

	
	Matrix<int> matB(8, 8);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			matB[i][j] = i + j;
	Matrix<int> matLI(8, 8);
	for (int i = 0; i < 8; i++)
		matLI[i][i] = 1;
	Matrix<int> matBI(8, 8);
	Strassen(matB, matLI, matBI, 8);
	cout << "행렬 B" << endl;
	cout << matB;
	cout << "행렬 B * I" << endl;
	cout << matBI;

	Matrix<int> matD(4, 4);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			matD[i][j] = i + j * i - j * j;
	cout << "행렬 C " << endl;
	cout << matD;
	
	Matrix<int> matAD(4, 4);
	Strassen(matA, matD, matAD, 4);
	cout << matAD;

	return 0;
}