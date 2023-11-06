#include <iostream>

using namespace std;

template <class T>
class heap
{
private:
	int heapsize;
	T* arr;
public:
	heap() :heapsize(0) { arr = NULL; }
	heap(int size);
	~heap() { delete[] arr; }

	//Overload
	T& operator[](int idx);
	friend ostream& operator<<(ostream& os, heap<T>& heap)
	{
		os << "[ ";
		for (int i = 0; i < heap.heapsize - 1; i++)
			os << heap.arr[i] << ", ";
		os << heap.arr[heap.heapsize - 1] << " ]" << endl;
		return os;
	}

	inline int PARENT(int i) { return ((i + 1) >> 1) - 1; }
	inline int LEFT(int i) { return ((i + 1) << 1) - 1; }
	inline int RIGHT(int i) { return ((i + 1) << 1); }

	void MAX_HEAPIFY(int i);
	void BUILD_MAX_HEAP();
};

int main(void)
{
	heap<int> h(10);
	for (int i = 0; i < 10; i++)
		h[i] = i + 1;
	cout << h;
	h.MAX_HEAPIFY(0);
	cout << h;
	h.BUILD_MAX_HEAP();
	cout << h;
	return 0;
}



template <class T>
heap<T>::heap(int size):heapsize(size)
{
	arr = new T[size];
}

template <class T>
T& heap<T>::operator[](int idx)
{
	if (idx < 0 || idx >= heapsize)
	{
		exit(0);
	}
	return arr[idx];
}

template <class T>
void heap<T>::MAX_HEAPIFY(int i)
{
	int l = LEFT(i);
	int r = RIGHT(i);
	int largest;
	if (l < heapsize && arr[l] > arr[i])
		largest = l;
	else
		largest = i;

	if (r < heapsize && arr[r] > arr[largest])
		largest = r;

	if (largest != i)
	{
		//바꾸기
		T temp = arr[largest];
		arr[largest] = arr[i];
		arr[i] = temp;
		MAX_HEAPIFY(largest);
	}
}

template <class T>
void heap<T>::BUILD_MAX_HEAP()
{
	int n = heapsize;
	for (int i = (n >> 1); i > 0; i--)
		MAX_HEAPIFY(i - 1); //i는 n부터 1까지여서 n-1부터 0으로 맞추기 위해
}

