#include <iostream>
#include <vector>
using namespace std;

//
void sort(vector<int>::iterator start, vector<int>::iterator end)
{
	int key, j;
	bool x = false;
	vector<int>::iterator ptr1;
	vector<int>::iterator ptr2;
	for (ptr1 = start+1; ptr1 != end; ptr1++)
	{
		key = *ptr1;
		ptr2 = ptr1 - 1;
		while (*ptr2 != NULL && *ptr2 > key)
		{
			*(ptr2 + 1) = *ptr2;
			if (ptr2 == start)
			{
				x = true;
				break;
			}
			ptr2--;
		}
		if (x)
		{
			x = false;
			*ptr2 = key;
		}
		else
			*(ptr2 + 1) = key;
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	int x;
	vector<vector<int>> v;					//2���������� ����� 0: ��� 1~m, 1~n:�������� ���
	for(int i = 0; i <= n; i++)
	{
		vector<int> v_t;
		v.push_back(v_t);
	}
	for (int i = 0; i < m; i++)				//0 �� ����� ä��� (U)
		v[0].push_back(i + 1);
	for (int i = 1; i <= n; i++)			//������� ������� �Է� �޴´�.
	{
		do {
			cin >> x;
			v[i].push_back(x);
		} while (getc(stdin) == ' ');		//���͸� �Է¹����� �����
	}

	//����� ������������ �����Ѵ�.
	for (int i = 1; i <= n; i++)
	{
		sort(v[i].begin(), v[i].end());
	}

	int max_size=0;							//���� ����� ��������� ã�´�
	int idx;
	vector<int> select;						//���õ� ����� ���� �迭
	for (int i = 1; i <= n; i++)
	{
		if (v[i].size() > max_size)
		{
			max_size = v[i].size();
			idx = i;
		}
	}
	select.push_back(idx);
	int k = 0;
	while (!v[idx].empty() && k < v[0].size())					//���õ� ����� ����� v[0] (=U)���� ����
	{
		if (v[idx].front() == v[0][k])
		{
			v[0].erase(v[0].begin()+k);
			v[idx].erase(v[idx].begin());
		}
		else
			k++;
	}

	int p=0, q=0;
	max_size = 0;	idx = 0;
	int same_num;
	while (!v[0].empty())					//�� ���� �ݺ� (����� ���� ���� ��ġ�� ��� ã��
	{
		max_size = 0; idx = 0;
		for (int i = 1; i <= n; i++)
		{
			p = 0; q = 0; same_num = 0;
			while (p < v[0].size() && q < v[i].size())
			{
				if (v[0][p] == v[i][q])
				{
					same_num++; p++; q++;
				}
				else if (v[0][p] > v[i][q])
					q++;
				else
					p++;
			}	//�� �񱳳����� ���� ���� ��ġ�� ���� ã������ ���Ӱ���
			if (max_size < same_num)
			{
				max_size = same_num;
				idx = i;
			}
		}
		p = 0; q = 0;
		//�ϴ� �ѹ� ���� ��ġ�°��� ã���� v[0]���� ����
		select.push_back(idx); //�ϴ� ã���� �߰�
		while (q < v[idx].size() && p < v[0].size()) //U ���� �����
		{
			if (v[0][p] == v[idx][q])
			{
				v[0].erase(v[0].begin() + p);
				v[idx].erase(v[idx].begin() + q);
			}
			else if (v[0][p] > v[idx][q])
				q++;
			else
				p++;
		}
		v[idx].erase(v[idx].begin(), v[idx].end());
	}

	sort(select.begin(), select.end());

	
	for (int i = 0; i < select.size(); i++)
	{
		cout << select[i] <<' ';
	}
	



	return 0;
}