#include <iostream>

using namespace std;

//쉘정렬
//몇칸으로 나누느냐가 중요하다. 몇칸으로 나눌지를 k에 받는다.

void shell_sort(int* arr, int n, int k)
{
	//일단먼저 그룹원소의 개수를 알아야한다. 
	//나머지를 계산하면 def에 저장. 예를들어서 2이면 0으로시작하는그룹, 1로시작하는 그룹만 원소가 다른그룹보다 1개많다.
	//k1을 원소가 많은그룹의 반복횟수, k2를 원소가 적은그룹의 반복횟수로 둔다.
	int def = n % k; 
	int k1 = (int)(n / k) + 1;
	int k2 = (int)(n / k);

	//그룹의 수만큼 반복 k간격이면 그룹수는 k개이다.(0~k-1)
	for (int j = 0; j < k; j++)
	{
		int d;
		// def보다작으면, 예를들어 2보다작으면 0으로시작하는그룹과 1로시작하는그룹이므로 k1을 사용
		if (j < def)
			d = k1;
		else
			d = k2;

		int key;
		//d가정해지면 삽입정렬 시작
		for (int i = 1; i < d; i++)
		{
			key = arr[k * i + j];
			int s = i - 1;

			while (s >= 0 && key < arr[k * s + j])
			{
				//왼쪽이 더 크니까 오른쪽으로이동
				arr[k * (s + 1) + j] = arr[k * s + j];
				s--;
			}

			arr[k * (s + 1)+j] = key;
		}
	}
}

int main(void) {
	//정렬할 숫자들 입력받기
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	//쉘정렬
	shell_sort(arr, n, 701);
	shell_sort(arr, n, 301);
	shell_sort(arr, n, 132);
	shell_sort(arr, n, 57);
	shell_sort(arr, n, 23);
	shell_sort(arr, n, 10);
	shell_sort(arr, n, 4);
	shell_sort(arr, n, 1);
	
	//출력
	for (int i = 0; i < n; i++)
		cout << arr[i] << endl;

	return 0;
}