#include <iostream>
#include <string>
using namespace std;

class UintArray
{
private:
	int cap;				//capacity
	int idx;
	unsigned int* arr;		//����

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

	int get() { return idx; } //�ε����� ����, �ְ��� �ϳ������ϹǷ� ����� �迭�Ǳ���

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

//�迭�� �ε����� ��ȯ
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
	UintArray uar;			//�Ǻ���ġ �������� ������ �迭 ����
	uar.Push(0);			//��� ���ϰ� �ϱ����� �̸� 0, 1 ����
	uar.Push(1);		
	int idx = 2;			//�����ϱ����� ������		
	unsigned int max = 0;	//n���� ���� �Ǻ���ġ �� ���� �迭�� ����
	unsigned int usum = 0;	//ġŲ �� ������ ����
	unsigned int uleft = 0;	//���� ��
	if (n == 0 || n == 1)
		return n;

	while (1 < n && max <= n)		
	{
		uar.Push(uar[idx - 1] + uar[idx - 2]);
		max = uar[idx];
		idx++;
	}

	idx -= 2;		//���� n���� ���� �Ǻ���ġ ���� idx��
	uleft = n - uar[idx];
	if (uleft == 0)	//n�� �Ǻ���ġ �� �϶�
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

