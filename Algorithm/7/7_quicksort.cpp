#include <iostream>
using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int partition(int* arr, int p, int r) {		//p는 시작, r은 끝
// arr[r]을 기준으로 좌우를 나눈다. arr[r]보다 크거나 같으면 highside, 작으면 lowside라고 한다.
// 이 함수를 통해 arr[r]이 몇번째로 작은 수인지 알 수 있다.
// arr[r]과 같은 수가 만약 존재한다면, 서로 위치가 바뀔 수 있다. (안전성 없는 정렬)
	int x = arr[r];
	int i = p - 1;
	for (int j = p; j < r; j++) // arr[r]이 정렬의 기준(pivot)이 되기 때문
	{
		if (arr[j] <= x) { //lowside로 옮겨줘야한다.
			i++;
			swap(arr[j], arr[i]);
		}
	}
	// 여기까지 완료되면 lowside와 highside가 분류되고, i는 lowside의 가장 끝을 가리킨다.
	// 따라서 기준이 되었던 pivot arr[r]과 arr[i+1]의 자리를 바꾼다.
	swap(arr[i + 1], arr[r]);
	// arr[i+1]은 제위치를 완벽히 찾은 상태
	return i + 1;
}

void quicksort(int* arr, int p, int r) {	//p는 시작, r은 끝
	int q;
	if (p < r) {
		q = partition(arr, p, r);
		quicksort(arr, p, q - 1);
		quicksort(arr, q + 1, r);
	}
}

int hoare_partition(int* arr, int p, int r) {
	int x = arr[p];
	int i = p - 1;
	int j = r + 1;

	while (true) {
		do {
			j--;
		} while (arr[j] > x);
		do {
			i++;
		} while (arr[i] < x);

		if (i < j)
			swap(arr[i], arr[j]);
		else
			return j;
	}
}

void hoare_quicksort(int* arr, int p, int r) {
	int q;
	if (p < r) {
		q = hoare_partition(arr, p, r);
		hoare_quicksort(arr, p, q);
		hoare_quicksort(arr, q + 1, r);
	}
}

int main(void)
{
	int arr[10] = { 10, 4, 2, 5, 7, 8, 9, 1, 3, 6 };
	hoare_quicksort(arr, 0, 9);
	
	for (int i = 0; i < 10; i++)
		cout << arr[i] << ' ';
	return 0;
}