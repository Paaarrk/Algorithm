#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct sd {
	long long s;
	long long d;
};

sd calc_sd(long long n) {
	//짝수검사는 Miller_Rabin에서 하고들어오기 때문에 n은 항상 홀수
	sd result;
	long long s = 0;
	n--;
	while (n % 2 == 0) {
		n = n / 2;
		s++;
	}
	result.s = s;
	result.d = n;
	return result;
}

//원래의 수 n-1 = 2^s*d
//0<=r<=s-1
//test 할 수는 a = 2, 7, 61.
//2^r*d < 2^s*d < n
//필요한 함수는 x^n mod m 이다.
//n(= d) < 500,000,000인 정수이다.

long long mod(long long a, long long n, long long m) {
	long long count = 1;
	long long max = a;
	//a^count 가 m보다 클때 멈춤 (a^count mod m = countmod < m)
	while (max <= m && count < n) {
		max = max * a;	
		count++;
	}
	long long countmod = max % m;

	if (max < m && count <= n)
		return countmod; //max가 m보다 작고 count가 n과 같거나 작으면 이미 계산 완료되었으므로 종료

	//n = count * num + alpha로 표현 ( a ^ alpha는 항상 m보다 작음 하지만 (countmod ^ num)의 mod m이 그만큼 클 수 있으므로 그대로 곱할수는 없음)
	long long num;
	long long alpha;
	num = n / count;
	alpha = n % count;
	
	//우리가 구하는 mod = (countmod ^ num * a ^ alpha) mod m
	//countmod ^ num 역시 타입을 넘어갈 수 있기 때문에 이것도 재계산 필요
	//구한 countmod ^ num 값에 a를 한번씩 곱하고 mod m을 구해야함 (a를 총 alpha번 곱해야함)
	long long nonalpha_modm = mod(countmod, num, m);
	long long result;
	result = nonalpha_modm;
	while (alpha != 0) {
		result = (result * a) % m;
		alpha--;
	}
	return result;
}

void setTester(vector<long long>& a, long long n) {
	if (n > 1000000000) {
		cout << "10억 이하의 수만 가능합니다." << endl;
		exit(0);
	}
	if (n < 1373653) {
		a.push_back(2);		a.push_back(3);
	}
	else if (n < 9080191) {
		a.push_back(31);	a.push_back(73);
	}
	else {
		a.push_back(2);		a.push_back(7);		a.push_back(61);
	}
}

//2의 지수승
long long exp(long long r, long long d) {
	long long result = 1;
	while (r != 0) {
		result = result * 2;
		r--;
	}
	result = result * d;
	return result;
}

//false이면 소수
bool Miller_Rabin(long long n) {
	if (n % 2 == 0)
		return false;
	
	bool result = false;
	vector<long long> a;
	setTester(a, n);
	sd sd = calc_sd(n);
	while (a.size() != 0) {
		if (mod(a[0], sd.d, n) != 1)
			result = true;
		else
			result = false;

		for (long long r = 0; r < sd.s; r++) {
			long long modcalc = mod(a[0], exp(r, sd.d), n);
			if ( modcalc != n - 1)
				result = result & true;
			else
				result = result & false;
		}

		a.erase(a.begin());
		if(result == true)
			return result; //한번이라도 true가나오면 3,4 조건을 만족한 것이므로 종료
	}
	
	return result;
}

int main(void)
{
	long long n;
	cin >> n;
	
	bool x = Miller_Rabin(n);
	if (x == true)
		cout << "0";
	else
		cout << "1";


	return 0;
}