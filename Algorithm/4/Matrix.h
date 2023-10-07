
#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <iostream>
using namespace std;

template <class T>
class Array
{
private:
	int cap;
	T* arr;
public:
	//Init&Destroy
	Array(int n);
	Array(Array<T>& ref);
	//Array(Array<T> temp);
	~Array();
	//Overload
	friend ostream& operator<<(ostream& os, const Array<T>& ref)
	{
		for (int i = 0; i < ref.cap; i++)
			os << ref.arr[i] << ' ';
		os << "\n";
		return os;
	}
	T& operator[](int idx);
	Array<T>& operator=(const Array<T>& ref);
	Array<T> operator+(Array<T>& arr2);
	Array<T> operator-(Array<T>& arr2);
};


template <typename T>
using Arrayptr = Array<T>*;

template <typename T>
class Matrix
{
private:
	int rows, cols;
	Arrayptr<T>* mat;
public:
	//Init & Destroy
	Matrix(int r, int c);
	Matrix(Matrix<T>& ref);
	~Matrix();

	//Overload
	friend ostream& operator<<(ostream& os, const Matrix<T>& ref)
	{
		for (int i = 0; i < ref.rows; i++)
		{
			os << *ref.mat[i];
		}
		os << "\n";
		return os;
	}
	Array<T>& operator[](int r);
	Matrix<T>& operator=(const Matrix<T>& ref);
	Matrix<T> operator+(Matrix<T>& ref);
	Matrix<T> operator-(Matrix<T>& ref);
};


//Matrix
//Init& Destroy
template <class T>
Matrix<T>::Matrix(int r, int c):rows(r), cols(c)
{
	if (r < 0 || c < 0)
	{
		cout << "error" << endl;
		exit(1);
	}
	mat = new Arrayptr<T>[rows];
	for (int i = 0; i < rows; i++)
	{
		mat[i] = new Array<T>(cols);
	}
}

template <class T>
Matrix<T>::Matrix(Matrix<T>& ref) :rows(ref.rows), cols(ref.cols)
{
	mat = new Arrayptr<T>[rows];
	for (int i = 0; i < rows; i++)
	{
		mat[i] = new Array<T>(cols);
	}

}

template <class T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < cols; i++)
		delete mat[i];
	delete[] mat;
}

//Overload
template <class T>
Array<T>& Matrix<T>::operator[](int r)
{
	if (r < 0 || r >= rows)
	{
		cout << "Bounds of row execption" << endl;
		exit(1);
	}
	
	return *mat[r];
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& ref)
{
	if (ref.rows != rows || ref.cols != cols)
	{
		cout << "Bounds of matricies are not same!" << endl;
		exit(1);
	}
	for (int i = 0; i < rows; i++)
		*mat[i] = *ref.mat[i];
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& ref)
{
	if (ref.rows != rows || ref.cols != cols)
	{
		cout << "Bounds of matricies are not same!" << endl;
		exit(1);
	}
	Matrix<T> newMat(rows, cols);
	for (int i = 0; i < rows; i++)
		*newMat.mat[i] = *ref.mat[i] + *mat[i];
	return newMat;
}

template <class T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& ref)
{
	if (ref.rows != rows || ref.cols != cols)
	{
		cout << "Bounds of matricies are not same!" << endl;
		exit(1);
	}
	Matrix<T> newMat(rows, cols);
	for (int i = 0; i < rows; i++)
		*newMat.mat[i] = *mat[i] - *ref.mat[i];
	return newMat;
}
//Array
//Init& Destroy
template <class T>
Array<T>::Array(int n) :cap(n)
{
	arr = new T[cap];
	for (int i = 0; i < cap; i++)
		arr[i] = 0;
}

template <class T>
Array<T>::Array(Array<T>& ref) :cap(ref.cap)
{
	arr = new T[cap];
	for (int i = 0; i < cap; i++)
		arr[i] = ref.arr[i];
}


template <class T>
Array<T>:: ~Array()
{
	delete[] arr;
}

//Overload
template <class T>
T& Array<T>::operator[](int idx)
{
	if (idx < 0 || idx >= cap)
	{
		cout << "Arrays of Bound exception" << endl;
		exit(1);
	}
	
	return arr[idx];
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& ref)
{
	if (ref.cap != cap)
	{
		cout << "Bound of array is different" << endl;
		exit(1);
	}
	for (int i = 0; i < cap; i++)
		arr[i] = ref.arr[i];
}

template <class T>
Array<T> Array<T>::operator+(Array<T>& arr2)
{
	if (arr2.cap != cap)
	{
		cout << "Bounds of arrays are different" << endl;
		exit(1);
	}
	Array<T> newArr(cap);
	for (int i = 0; i < cap; i++)
		newArr.arr[i] = arr[i] + arr2.arr[i];
	
	return newArr;
}

template <class T>
Array<T> Array<T>::operator-(Array<T>& arr2)
{
	if (arr2.cap != cap)
	{
		cout << "Bounds of arrays are different" << endl;
		exit(1);
	}
	Array<T> newArr(cap);
	for (int i = 0; i < cap; i++)
		newArr.arr[i] = arr[i] - arr2.arr[i];

	return newArr;
}



#endif