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
	vector<vector<int>> v;					//2차원공간을 만든다 0: 기술 1~m, 1~n:지원자의 기술
	for(int i = 0; i <= n; i++)
	{
		vector<int> v_t;
		v.push_back(v_t);
	}
	for (int i = 0; i < m; i++)				//0 을 기술로 채운다 (U)
		v[0].push_back(i + 1);
	for (int i = 1; i <= n; i++)			//기술자의 기술들을 입력 받는다.
	{
		do {
			cin >> x;
			v[i].push_back(x);
		} while (getc(stdin) == ' ');		//엔터를 입력받으면 멈춘다
	}

	//기술을 오름차순으로 정렬한다.
	for (int i = 1; i <= n; i++)
	{
		sort(v[i].begin(), v[i].end());
	}

	int max_size=0;							//가장 기술이 많은사람을 찾는다
	int idx;
	vector<int> select;						//선택된 사람을 담을 배열
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
	while (!v[idx].empty() && k < v[0].size())					//선택된 사람의 기술을 v[0] (=U)에서 제거
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
	while (!v[0].empty())					//위 과정 반복 (기술이 가장 많이 겹치는 사람 찾기
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
			}	//다 비교끝나면 가장 많이 겹치는 값을 찾기위해 지속갱신
			if (max_size < same_num)
			{
				max_size = same_num;
				idx = i;
			}
		}
		p = 0; q = 0;
		//일단 한번 많이 겹치는것을 찾으면 v[0]에서 제거
		select.push_back(idx); //일단 찾은거 추가
		while (q < v[idx].size() && p < v[0].size()) //U 에서 지우기
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