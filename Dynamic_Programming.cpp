#include <iostream>
#include <vector>

using namespace std;

struct node
{
	int d;
	int elec;
};


//Esum은 누적 전기 소모량값 전달(초기값은 전체 방 소모량합, 함수에 들어가면 start지점은 불을 껏으므로 start지점의 소모량을 빼준다.)
//예) w1+w2+w3+w4+w5 에서 시작지점이 3이면 함수에 들어오면 w1+w2+w4+w5가되고, 이 값을 기준으로 다른방 이동까지 소모되는 전력량을 누적한다.
void DP(vector<vector<vector<int>>>& vsave, vector<vector<int>> v, vector<vector<int>> v2, node* arr, int bef_start, int start, int w_sum, int Esum, bool* a, int& counts)
{
	int templ = start; //시작 위치, 왼쪽과 오른쪽을 따로 계산
	int tempr = start; //시작 위치, 왼쪽과 오른쪽을 따로 계산
	//방문 정보를 담을 배열
	bool* a1 = new bool[w_sum + 1]; //방문여부, 다음에 가야할 방을 찾기위해 사용
	bool* a2 = new bool[w_sum + 1]; //방문여부, 다음에 가야할 방을 찾기위해 사용
	for (int i = 0; i <= w_sum; i++)
	{
		a1[i] = a[i];
		a2[i] = a[i];
	}

	//움직임은 최대 강의실번 일어남 (0,0 까지)
	int left = start;
	int right = start;

	while (left != -1)
	{
		if (a[left])
			left--;
		else
			break;
	}
	while (right != w_sum + 1)
	{
		if (a[right])
			right++;
		else
			break;
	}

	int EsumL = Esum - arr[start].elec;
	int EsumR = Esum - arr[start].elec;


	//0일때 (원점옴), 바로 이전엔 (n, 0)에 값이 기록되어있음.
	if (((bef_start == 0)&&(start == 0)) || left < 0 || right > w_sum + 1)
		return;
	//leftgo : 왼쪽을 가냐 마냐를 결정
	//왼쪽을 갈지 안갈지 검사. 전부 방문하지 않았지만 0으로 온 경우에는 가면 안되므로 leftgo를 false로 바꿈
	// left == 0일 경우는 항상 마지막이여야함
	bool leftgo = true; 
	if (left == 0)
	{
		int count = 0;
		for (int i = 1; i <= w_sum; i++)
		{
			if (a[i])
				count++;
		}
		if (count != w_sum)
			leftgo = false; //전부 방문하지 않았지만 끝에 온 경우
	}

	//반복
	if ((0 <= left && left <= w_sum)&&leftgo == true)
	{
		v[start][left] = v[bef_start][start]+EsumL * (arr[start].d - arr[left].d);		//start에서 left로 가는동안 발생하는 전력 소모량
		templ = left;
		a1[templ] = true;//방문도장
		vsave.push_back(v);//현재 이동 관련정보 저장
		counts++;
		DP(vsave, vsave[counts-1], vsave[counts - 1], arr, start, templ, w_sum, EsumL, a1,counts); //누적시킨 좌표를 넘겨준다.
	}

	if (0 <= right && right <= w_sum)
	{
		v2[start][right] = v2[bef_start][start]+EsumR * (arr[right].d - arr[start].d);
		tempr = right;
		a2[tempr] = true; //방문도장
		vsave.push_back(v2);//현재 이동 관련정보 저장
		counts++;
		DP(vsave, vsave[counts-1], vsave[counts - 1], arr, start, tempr, w_sum, EsumR, a2,counts);
	}


}

int main(void)
{
	int w_num, start;
	cin >> w_num >> start;
	//방문 정보를 담을 배열
	bool* a = new bool[w_num + 1];
	for (int i = 0; i <= w_num; i++)
		a[i] = false;
	a[start] = true; //시작지점은 방문으로 치기

	//강의실 정보. 0번강의실은 원점위치, 전력소모 0
	node* arr = new node[w_num + 1];
	arr[0].d = 0; arr[0].elec = 0;
	int temp1, temp2;
	for (int i = 1; i <= w_num; i++)
	{
		cin >> temp1 >> temp2;
		arr[i].d = temp1;
		arr[i].elec = temp2;
	}

	int Esum = 0;
	for (int i = 1; i <= w_num; i++)
		Esum += arr[i].elec;

	//왼쪽, 오른쪽 이동시 소모 전력량을 저장할 v, 0으로 전부 초기화
	vector<int> v1;
	for (int i = 0; i <= w_num; i++)
		v1.push_back(0);
	vector<vector<int>> v;
	for (int i = 0; i <= w_num; i++)
		v.push_back(v1);
	//경로 저장공간
	vector<vector<vector<int>>> vsave;

	//계산 목표는 시작지점(start,start) 에서 (0,0)까지 이동하면된다.
	//(6,7) => 6에서 7로 이동 -> 후 (7,7)을 (6,7) 값으로 초기화
	//
	int count = 0;
	DP(vsave, v, v, arr, start, start, w_num, Esum, a, count); //시작은 start->start (d = 0)으로 정의

	//각 nxn테이블의 (n,0)은 n번강의실에서 0번으로 온 경우, 마지막을 의미. 이곳의 값을 전부 확인해 작은값이 최솟값

	int result = 200000000; //작은 것을 저장하기위해서 임의로 설정한 값

	//i번째 테이블의 (j,0)값만을 확인함. j->0으로 마지막 이동을 의미함.
	// (x,j) == (j, 0)이므로 가능함. (0번강의실을 소모전력을 0으로 설정했기때문에)
	for (int i = 0; i < vsave.size(); i++)
	{
		for (int j = 0; j <= w_num; j++)
		{
			if (vsave[i][j][0] != 0)
			{
				if (vsave[i][j][0] < result)
					result = vsave[i][j][0];
			}
		}
	}
	cout << result << endl;




	return 0;
}