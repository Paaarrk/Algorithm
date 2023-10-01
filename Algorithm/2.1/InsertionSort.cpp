#include <iostream>
using namespace std;

void ShowArray(int* A, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

void INSERTION_SORT(int* A, int n)
{
	int key, j;
	for (int i = 1; i < n; i++)
	{
		key = A[i];
		cout << "now key: A[" << i << "] = " << A[i] << endl;
		//현재 배열상태
		cout << "현재 배열상태: ";
		ShowArray(A, n);
		//Insert A[i] into the sorted subArray A[1 : i-1]
		j = i - 1;
		while (j >= 0 && A[j] > key)
		{
			A[j + 1] = A[j];
			j--;
			ShowArray(A, n);
		}
		A[j + 1] = key;
		ShowArray(A, n);
	}
}



int main(void)
{
	int arr[] = {8, 6, 3, 1, 4, 5};

	INSERTION_SORT(arr, 6);
	
	cout << "최종 정렬: ";
	ShowArray(arr, 6);
	return 0;
}