#include <iostream>
using namespace std;

typedef int* intPtr;
void MATRIX_MULTIPLY_RECURSIVE(int** A, int** B, intPtr** C, int n)
{
	//Base case
	if (n == 1)
	{
		*C[0][0] = *C[0][0] + A[0][0] * B[0][0];
		return;

		delete C;
		delete A;
		delete B;
	}
	
	//Divide
	//A
	int** A11 = new int* [n / 2];
	for (int i = 0; i < n / 2; i++)
		A11[i] = new int[n / 2];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			A11[i][j] = A[i][j];

	int** A12 = new int* [n / 2];
	for (int i = 0; i < n / 2; i++)
		A12[i] = new int[n / 2];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			A12[i][j] = A[i][j + n / 2];

	int** A21 = new int* [n / 2];
	for (int i = 0; i < n / 2; i++)
		A21[i] = new int[n / 2];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			A21[i][j] = A[i + n / 2][j];

	int** A22 = new int* [n / 2];
	for (int i = 0; i < n / 2; i++)
		A22[i] = new int[n / 2];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			A22[i][j] = A[i + n / 2][j + n / 2];

	//B
	int** B11 = new int* [n / 2];
	for (int i = 0; i < n / 2; i++)
		B11[i] = new int[n / 2];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			B11[i][j] = B[i][j];

	int** B12 = new int* [n / 2];
	for (int i = 0; i < n / 2; i++)
		B12[i] = new int[n / 2];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			B12[i][j] = B[i][j + n / 2];

	int** B21 = new int* [n / 2];
	for (int i = 0; i < n / 2; i++)
		B21[i] = new int[n / 2];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			B21[i][j] = B[i + n / 2][j];

	int** B22 = new int* [n / 2];
	for (int i = 0; i < n / 2; i++)
		B22[i] = new int[n / 2];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			B22[i][j] = B[i + n / 2][j + n / 2];

	//C
	intPtr ** C11 = new intPtr* [n / 2];
	for (int i = 0; i < n / 2; i++)
		C11[i] = new intPtr[n / 2];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C11[i][j] = C[i][j];

	intPtr** C12 = new intPtr* [n / 2];
	for (int i = 0; i < n / 2; i++)
		C12[i] = new intPtr[n / 2];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C12[i][j] = C[i][j + n / 2];

	intPtr** C21 = new intPtr* [n / 2];
	for (int i = 0; i < n / 2; i++)
		C21[i] = new intPtr[n / 2];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C21[i][j] = C[i + n / 2][j];

	intPtr** C22 = new intPtr* [n / 2];
	for (int i = 0; i < n / 2; i++)
		C22[i] = new intPtr[n / 2];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C22[i][j] = C[i + n / 2][j + n / 2];
	

	//Conquer
	//C11
	MATRIX_MULTIPLY_RECURSIVE(A11, B11, C11, n / 2);
	MATRIX_MULTIPLY_RECURSIVE(A12, B21, C11, n / 2);
	//C12
	MATRIX_MULTIPLY_RECURSIVE(A11, B12, C12, n / 2);
	MATRIX_MULTIPLY_RECURSIVE(A12, B22, C12, n / 2);
	//C21
	MATRIX_MULTIPLY_RECURSIVE(A21, B11, C21, n / 2);
	MATRIX_MULTIPLY_RECURSIVE(A22, B21, C21, n / 2);
	//C22
	MATRIX_MULTIPLY_RECURSIVE(A21, B12, C22, n / 2);
	MATRIX_MULTIPLY_RECURSIVE(A22, B22, C22, n / 2);
}

int main(void)
{
	int** arrA = new int* [4];
	for (int i = 0; i < 4; i++)
		arrA[i] = new int[4];
	arrA[0][0] = 2; arrA[0][1] = 1; arrA[0][2] = 2; arrA[0][3] = 4;
	arrA[1][0] = 3; arrA[1][1] = 1; arrA[1][2] = 2; arrA[1][3] = 4;
	arrA[2][0] = 3; arrA[2][1] = 5; arrA[2][2] = 1; arrA[2][3] = 4;
	arrA[3][0] = 3; arrA[3][1] = 1; arrA[3][2] = 2; arrA[3][3] = 4;

	int** I = new int* [4];
	for (int i = 0; i < 4; i++)
		I[i] = new int[4];
	I[0][0] = 1; I[0][1] = 0; I[0][2] = 0; I[0][3] = 0;
	I[1][0] = 0; I[1][1] = 1; I[1][2] = 0; I[1][3] = 0;
	I[2][0] = 0; I[2][1] = 0; I[2][2] = 1; I[2][3] = 0;
	I[3][0] = 0; I[3][1] = 0; I[3][2] = 0; I[3][3] = 1;

	int** arrB = new int* [4];
	for (int i = 0; i < 4; i++)
		arrB[i] = new int[4];
	arrB[0][0] = 1; arrB[0][1] = 4; arrB[0][2] = 0; arrB[0][3] = 3;
	arrB[1][0] = 0; arrB[1][1] = 2; arrB[1][2] = 0; arrB[1][3] = 2;
	arrB[2][0] = 0; arrB[2][1] = 5; arrB[2][2] = 1; arrB[2][3] = 0;
	arrB[3][0] = 2; arrB[3][1] = 1; arrB[3][2] = 0; arrB[3][3] = 1;

	int** arrC = new int*[4];
	for (int i = 0; i < 4; i++)
		arrC[i] = new int[4];
	arrC[0][0] = 0; arrC[0][1] = 0; arrC[0][2] = 0; arrC[0][3] = 0;
	arrC[1][0] = 0; arrC[1][1] = 0; arrC[1][2] = 0; arrC[1][3] = 0;
	arrC[2][0] = 0; arrC[2][1] = 0; arrC[2][2] = 0; arrC[2][3] = 0;
	arrC[3][0] = 0; arrC[3][1] = 0; arrC[3][2] = 0; arrC[3][3] = 0;

	intPtr** C = new intPtr * [4];
	for (int i = 0; i < 4; i++)
		C[i] = new intPtr[4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			C[i][j] = &arrC[i][j];
		}
	}

	MATRIX_MULTIPLY_RECURSIVE(arrA, I, C, 4);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << arrC[i][j] << " ";
		cout << endl;
	}
		

	return 0;
}