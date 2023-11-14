#include <iostream>

using namespace std;

//������
//��ĭ���� �������İ� �߿��ϴ�. ��ĭ���� �������� k�� �޴´�.

void shell_sort(int* arr, int n, int k)
{
	//�ϴܸ��� �׷������ ������ �˾ƾ��Ѵ�. 
	//�������� ����ϸ� def�� ����. ������ 2�̸� 0���ν����ϴ±׷�, 1�ν����ϴ� �׷츸 ���Ұ� �ٸ��׷캸�� 1������.
	//k1�� ���Ұ� �����׷��� �ݺ�Ƚ��, k2�� ���Ұ� �����׷��� �ݺ�Ƚ���� �д�.
	int def = n % k; 
	int k1 = (int)(n / k) + 1;
	int k2 = (int)(n / k);

	//�׷��� ����ŭ �ݺ� k�����̸� �׷���� k���̴�.(0~k-1)
	for (int j = 0; j < k; j++)
	{
		int d;
		// def����������, ������� 2���������� 0���ν����ϴ±׷�� 1�ν����ϴ±׷��̹Ƿ� k1�� ���
		if (j < def)
			d = k1;
		else
			d = k2;

		int key;
		//d���������� �������� ����
		for (int i = 1; i < d; i++)
		{
			key = arr[k * i + j];
			int s = i - 1;

			while (s >= 0 && key < arr[k * s + j])
			{
				//������ �� ũ�ϱ� �����������̵�
				arr[k * (s + 1) + j] = arr[k * s + j];
				s--;
			}

			arr[k * (s + 1)+j] = key;
		}
	}
}

int main(void) {
	//������ ���ڵ� �Է¹ޱ�
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	//������
	shell_sort(arr, n, 701);
	shell_sort(arr, n, 301);
	shell_sort(arr, n, 132);
	shell_sort(arr, n, 57);
	shell_sort(arr, n, 23);
	shell_sort(arr, n, 10);
	shell_sort(arr, n, 4);
	shell_sort(arr, n, 1);
	
	//���
	for (int i = 0; i < n; i++)
		cout << arr[i] << endl;

	return 0;
}