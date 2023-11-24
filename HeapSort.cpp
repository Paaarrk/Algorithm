#include <iostream>
#include <vector>
using namespace std;

int parent(int i) { return ((i + 1) >> 1) - 1; }
int left(int i) { return ((i + 1) << 1) - 1; }
int right(int i) { return ((i + 1) << 1); }


//arr은 배열, i는 몇번째 원소로 시작할 것인가
void downheap(vector<int>& v, int i, int n) {
	int heapsize = n;	// 배열 사이즈
	int l = left(i);	// i의 왼쪽 자식
	int r = right(i);	// i의 오른쪽 자식
	int largest = i;	// 일단 i가 가장 크다고 가정


	// i, i 왼쪽자식, i 오른쪽자식중 누가 제일 큰지 찾음.
	if (l < heapsize && v[largest] < v[l])
		largest = l;

	if (r < heapsize && v[largest] < v[r])
		largest = r;

	// i가 largest가 아니면 부모가 바뀌어야됨
	if (largest != i)
	{
		int temp = v[i];
		v[i] = v[largest];
		v[largest] = temp;

		// l과 r이 바뀌었으므로 바뀐i가 제위치 찾을 때 까지 실행
		downheap(v, largest, n);
	}
}

void max_heap(vector<int>& v, int heapsize)
{
	for (int i = heapsize / 2 - 1; i >= 0; i--)
		downheap(v, i, heapsize);
}

void heapsort(vector<int>& v, int n)
{
	//max-heap상태라고 가정
	int heapsize = n;

	int temp;
	for (int i = 1; i < n; i++)
	{
		int largest = v[0];
		//제일 위와 아래를 바꿈
		temp = v[heapsize - 1];
		v[heapsize - 1] = largest;
		v[0] = temp;
		//제일 아래가 제일 큰원소로 확정났으니 제외하기위해 heapsize --;
		heapsize--;
		//다운힙 실행
		downheap(v, 0, heapsize);
	}
}

int main(void)
{
	vector<int> v;
	int x;
	do {
		cin >> x;
		v.push_back(x);
	} while (getc(stdin) == ' ');

	int minimum;	//최소가격
	cin >> minimum;
	int count = 0;		//섞는 횟수
	//한번 정렬을 하고
	heapsort(v, v.size());
	while (v[0] < minimum) {
		//섞어주고
		v[0] = v[0] + v[1] * 2;
		v.erase(v.begin() + 1);
		//다시 정렬하고, 카운트를 센다.
		max_heap(v, v.size());
		heapsort(v, v.size());
		count++;
	}

	cout << count;

	return 0;
}