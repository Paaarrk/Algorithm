#include <iostream>
#include <string>

using namespace std;

template <typename T>
class handle;

template <class T>
class heap;

class schedule {
private:
	string Name;
	string property;
public:
	schedule(){}
	schedule(string n, string p) :Name(n), property(p) { }
	~schedule() { Name.~basic_string(); property.~basic_string(); }
	string name() { return Name; }
	schedule(schedule& ref):Name(ref.Name), property(ref.property){ }
};

//heap과 object를 연결
template <class T>
class handle {
friend class heap<T>;
private:
	int key;
	T* object; //object를 향한 포인터
public:
	handle() :key(0) {  object= NULL; }
	handle(int k, T& o) :key(k) { object = &o; }
	~handle() { object->~T(); }
};

//heap
template <class T>
class heap {
private:
	int size;
	int capacity;
	handle<T>** arr;
	bool isEmpty() { return (size == 0); }
	bool isFull() { return (size == capacity); }
	void extensing() { 
		handle<T>** temp = new handle<T>*[capacity + 100]; 
		for (int i = 0; i < size; i++)
			temp[i] = arr[i];
		delete arr;
		arr = temp;
		capacity += capacity;
	}
	//base_function
	int left(int i) { return ((i + 1) << 1) - 1; }
	int right(int i) { return((i + 1) << 1); }
	int parent(int i) { return ((i + 1) >> 1) - 1; }
	void max_heapify(int i);
	void build_max_heap();
public:
	heap() :size(0), capacity(100) { arr = new handle<T>*[100]; }
	~heap() { 
		for (int i = 0; i < size; i++)
			arr[i]->~handle<T>();
		delete arr; 
	}
	int Size() { return size; }

	//function
	void insert(T& object, int k);
	T& maximum() const;
	T* extract_max();
	void increase_key(T& object, int k);
	void showheap() const;
};

int main(void)
{
	schedule p1("p1", "graphic");
	schedule p2("p2", "firewall");
	schedule p3("p3", "request by com2");
	schedule p4("p4", "response to com2");
	schedule p5("p5", "kill all process");

	heap<schedule> h;
	h.insert(p1, 40);
	h.insert(p2, 50);
	h.insert(p3, 25);
	h.insert(p4, 39);
	h.insert(p5, 10);
	h.showheap();

	h.increase_key(p3, 100);
	h.showheap();
	schedule p6 = h.maximum();
	cout << p6.name() << endl;
	schedule* p7; p7 = h.extract_max();
	cout << p7->name() << endl;
	h.showheap();


	return 0;
}

//heap
//base_function
template <class T>
void heap<T>::max_heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int largest;
	if (l < size && arr[l]->key > arr[i]->key)
		largest = l;
	else
		largest = i;
	if (r<size && arr[r]->key > arr[largest]->key)
		largest = r;

	if (largest != i)
	{
		//i이면완성, i가아니면 자리바꿔야함
		handle<T>* temp;
		temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		//바꾸고 다시 검사 (largest와 i의 자리를 바꿨으니 largest에 작은값)
		max_heapify(largest);
	}
}

template <class T>
void heap<T>::build_max_heap()
{
	int n = (size >> 1) - 1;
	for (n; n >= 0; n--)
		max_heapify(n);
}


//function
template <class T>
void heap<T>::insert(T& object, int k)
{
	if (isFull())
		extensing();
	handle<T>* newH = new handle<T>(-1, object);
	arr[size] = newH; size++;
	increase_key(object, k);
}

template <class T>
void heap<T>::increase_key(T& object, int k)
{
	int i; int ke = -2;
	for (i = 0; i < size; i++)
	{
		if (arr[i]->object->name() == object.name())
		{
			ke = arr[i]->key;
			break;
		}
	}
	if (ke == -2)
	{
		cout << "없는 오브젝트" << endl;
		return;
	}

	if (ke >= k)
	{
		cout << "크지 않습니다" << endl;
		return;
	}

	arr[i]->key = k;
	while (i > 0 && arr[parent(i)]->key < arr[i]->key)
	{
		handle<T>* temp = arr[i];
		arr[i] = arr[parent(i)];
		arr[parent(i)] = temp;
		i = parent(i);
	}
}


template <class T>
void heap<T>::showheap() const
{
	cout << "힙 내용" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << "번: key: " << arr[i]->key << "   이름: " << arr[i]->object->name() << endl;
	}
	cout << "힙 용량: " << size << "  힙 전체용량: " << capacity << endl;
}

template <class T>
T& heap<T>::maximum() const
{
	return *(arr[0]->object);
}

template <class T>
T* heap<T>::extract_max()
{
	T* temp = new T(maximum());
	
	handle<T>* tempH = arr[0];
	arr[0] = arr[size - 1];
	arr[size - 1] = tempH;

	delete arr[size - 1];
	size--;

	build_max_heap();
	return temp;
}