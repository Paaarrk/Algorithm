#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

static double minimum;

bool compareX(pair<int, int>& p1, pair<int, int>& p2)
{
	return p1.first < p2.first;
}
bool compareY(pair<int, int>& p1, pair<int, int>& p2)
{
	return p1.second < p2.second;
}

double dist(pair<int, int>& p1, pair<int, int>& p2)
{
	return sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
}


void distMin(vector<pair<int, int>>& v, int left, int right)
{
	if (left < 0 || right < 0 || left >= v.size() || right >= v.size() || left >= right)
		return;
	if (right - left == 2)
	{
		if (minimum > dist(v[left], v[right]))
			minimum = dist(v[left], v[right]);
		return;
	}
	if (right - left == 3)
	{
		if (minimum > dist(v[left], v[right]))
			minimum = dist(v[left], v[right]);
		if (minimum = dist(v[left + 1], v[right]))
			minimum = dist(v[left + 1], v[right]);
		if (minimum = dist(v[left], v[right - 1]))
			minimum = dist(v[left], v[right - 1]);
		return;
	}

	int mid = (left + right) / 2;
	distMin(v, left, mid);
	distMin(v, mid + 1, right);

	int d = (int)minimum + 1;
	int vleft = v[mid].first - d;
	int vright = v[mid + 1].first + d;
	int low = mid;
	int high = mid + 1;
	while (left < low)
	{
		if (v[low].first >= vleft)
			low--;
		else
			break;
	}
	while (right > high)
	{
		if (v[high].first <= vright)
			high++;
		else
			break;
	}

	vector<pair<int, int>> temp(high - low + 1);
	for (int i = 0; i < temp.size(); i++)
	{
		temp[i] = v[i + low];
	}
	sort(temp.begin(), temp.end(), compareY);

	for (int i = 0; i < temp.size(); i++)
		cout << '[' << temp[i].first << ", " << temp[i].second << "] ";
	cout << endl;

	for (int i = 0; i < temp.size(); i++)
	{
		for (int j = i+1; j < temp.size(); j++)
		{
			if (temp[j].second - temp[i].second > d)
				break;
			else
			{
				if (dist(temp[i], temp[j]) < minimum)
					minimum = dist(temp[i], temp[j]);
			}
		}
	}

}

int main(void)
{
	int cap;
	cin >> cap;
	vector<pair<int, int>> arr(cap);

	string s;
	string str;
	int x, y;
	for (int i = 0; i < cap; i++)
	{
		cin >> str >> y;
		s = str.substr(0, str.find(','));
		x = stoi(s);
		arr[i].first = x;
		arr[i].second = y;
	}

	sort(arr.begin(), arr.end(), compareX);

	minimum = dist(arr[0], arr[1]);
	distMin(arr, 0, cap - 1);
	
	double min = minimum;
	for (int i = 0; i < cap; i++)
	{
		for (int j = i + 1; j < cap; j++)
		{
			if (dist(arr[i], arr[j]) < min)
				min = dist(arr[i], arr[j]);
		}
	}
	
	cout<<fixed;
	cout.precision(6);
	cout << minimum;
	cout << endl;
	cout << min;
}