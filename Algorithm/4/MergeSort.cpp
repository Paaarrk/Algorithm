#include <iostream>
using namespace std;

void Merge(int* A, int p, int q, int r)
{
	int length_L = q - p + 1; //���ʹ迭�� ����
	int length_R = r - q; //������ �迭�� ����

	int* L = new int[length_L]; //���ʹ迭 �����ϱ����� ����
	int* R = new int[length_R]; //�����ʹ迭 �����ϱ����� ����

	//����
	for (int i = 0; i < length_L; i++)
		L[i] = A[p + i];
	for (int i = 0; i < length_R; i++)
		R[i] = A[q + 1 + i];

	int i = 0, j = 0;
	int k = p; //�迭 A�� �����ϱ� ���� ����
	//��ü
	while (i < length_L && j < length_R)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else {
			A[k] = R[j];
			j++;
		}
		k++;
	}
	// ������ �ֱ�
	while (i < length_L)
	{
		A[k] = L[i];
		k++; i++;
	}
	while (j < length_R)
	{
		A[k] = R[j];
		k++; j++;
	}
	//�� �־����� �޸� �Ҵ� ����
	delete []L;
	delete []R;
}

void MergeSort(int* A, int p, int r)
{
	// p >= r �̸� ���Ұ� 1�� �����̹Ƿ� base case
	if (p >= r)
		return; 
	int q = (p + r) / 2;
	MergeSort(A, p, q); //��������� ��� ���� (���Ұ� 1�����ϰ� �� �� ����)
	MergeSort(A, q + 1, r); //��������� ��� ���� (���Ұ� 1�� ���ϰ� �� �� ����)

	Merge(A, p, q, r); //

}

int main(void)
{
	/* 
	//*�迭 �Է� �޴¿�*
	int n;
	int* arr;
	cin >> n;
	arr = new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	MergeSort(arr, 0, n - 1);
	for (int i = 0; i < n; i++)
		cout << arr[i] << endl;
	*/
	
	int arr[] = {3,8,55,36,7,3225,746,32,34,1};
	MergeSort(arr, 0, 9);
	for (int i = 0; i < 10; i++)
		cout << arr[i] << ' ';
	return 0;
	
}