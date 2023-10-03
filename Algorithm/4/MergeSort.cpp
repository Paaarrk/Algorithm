#include <iostream>
using namespace std;

void Merge(int* A, int p, int q, int r)
{
	int length_L = q - p + 1; //왼쪽배열의 길이
	int length_R = r - q; //오른쪽 배열의 길이

	int* L = new int[length_L]; //왼쪽배열 복사하기위한 공간
	int* R = new int[length_R]; //오른쪽배열 복사하기위한 공간

	//복사
	for (int i = 0; i < length_L; i++)
		L[i] = A[p + i];
	for (int i = 0; i < length_R; i++)
		R[i] = A[q + 1 + i];

	int i = 0, j = 0;
	int k = p; //배열 A를 조작하기 위한 변수
	//합체
	while (i < length_L && j < length_R)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else {
			A[k] = R[j];
			j++;
		}
		k++;
	}
	// 남은거 넣기
	while (i < length_L)
	{
		A[k] = L[i];
		k++; i++;
	}
	while (j < length_R)
	{
		A[k] = R[j];
		k++; j++;
	}
	//다 넣었으니 메모리 할당 종료
	delete []L;
	delete []R;
}

void MergeSort(int* A, int p, int r)
{
	// p >= r 이면 원소가 1개 이하이므로 base case
	if (p >= r)
		return; 
	int q = (p + r) / 2;
	MergeSort(A, p, q); //재귀적으로 계속 나눔 (원소가 1개이하가 될 때 까지)
	MergeSort(A, q + 1, r); //재귀적으로 계속 나눔 (원소가 1개 이하가 될 때 까지)

	Merge(A, p, q, r); //

}

int main(void)
{
	/* 
	//*배열 입력 받는용*
	int n;
	int* arr;
	cin >> n;
	arr = new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	MergeSort(arr, 0, n - 1);
	for (int i = 0; i < n; i++)
		cout << arr[i] << endl;
	*/
	
	int arr[] = {3,8,55,36,7,3225,746,32,34,1};
	MergeSort(arr, 0, 9);
	for (int i = 0; i < 10; i++)
		cout << arr[i] << ' ';
	return 0;
	
}