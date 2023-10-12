#include <iostream>
#include <string>
using namespace std;

class UintArray
{
private:
	int cap;				//capacity
	int idx;
	unsigned int* arr;		//저장

	void Extensing()
	{
		unsigned int* temp = new unsigned int[cap * 2];
		cap *= 2;
		for (int i = 0; i < cap; i++)
		{
			temp[i] = arr[i];
		}
		delete[]arr;
		arr = temp;
	}

public:
	UintArray(int n = 30):cap(n), idx(0)
	{
		arr = new unsigned int[30];
	}
	~UintArray()
	{
		delete[]arr;
	}

	int get() { return idx; } //인덱스값 리턴, 넣고나면 하나증가하므로 저장된 배열의길이

	unsigned int operator[](int n)
	{
		if (n > cap)
		{
			cout << "Out of Index" << endl;
			return -1;
		}
		return arr[n];
	}
	
	friend ostream& operator<<(ostream& os, UintArray& arr);

	void Push(unsigned int n)
	{
		if (idx == cap)
		{
			Extensing();
		}
		arr[idx] = n;
		idx++;
	}
	
};

ostream& operator<<(ostream& os, UintArray& arr)
{
	for (int i = 0; i < arr.idx; i++)
		os << arr[i] << " ";
	return os;
}

//배열의 인덱스를 반환
int BinarySearch(UintArray& uar, int idx, unsigned int find)
{
	if (find == 1)
	{
		return 2;
	}
	int mid = idx / 2;
	while (!(uar[mid] <= find && find < uar[mid + 1]))
	{
		if (find > uar[mid])
		{
			mid = (mid + idx) / 2;
		}
		else {
			idx = mid;
			mid = mid / 2;
		}
	}

	return mid;
}

unsigned int FChicken(unsigned int n)
{
	UintArray uar;			//피보나치 수열값을 저장할 배열 생성
	uar.Push(0);			//계산 편하게 하기위해 미리 0, 1 저장
	uar.Push(1);		
	int idx = 2;			//저장하기위한 포인터		
	unsigned int max = 0;	//n보다 작은 피보나치 수 까지 배열에 저장
	unsigned int usum = 0;	//치킨 값 저장할 변수
	unsigned int uleft = 0;	//남은 양
	if (n == 0 || n == 1)
		return n;

	while (1 < n && max <= n)		
	{
		uar.Push(uar[idx - 1] + uar[idx - 2]);
		max = uar[idx];
		idx++;
	}

	idx -= 2;		//실제 n보다 작은 피보나치 수의 idx값
	uleft = n - uar[idx];
	if (uleft == 0)	//n이 피보나치 수 일때
		usum = uar[idx];
	else
		usum = uar[idx - 1];

	int point = 0;
	while (uleft != 0)
	{
		point = BinarySearch(uar, idx, uleft);
		uleft -= uar[point];
		usum += uar[point - 1];
	}
	
	
	return usum;
}


int main()
{
	string pNum;
	cin >> pNum;
	unsigned int n = stoul(pNum);	//string -> uint

	cout<<FChicken(n);
	

	return 0;
}

