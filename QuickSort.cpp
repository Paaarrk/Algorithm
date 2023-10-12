#include <iostream>


void QuickSort(int arr[], int left, int right)
{
	/* ù��, �߰���, ���� ���ؼ� �Ǻ� ���ϱ� (�� ������ �����ϴ�)
	if (right - left > 3)
	{
		if ((arr[(left + right) / 2] < arr[left] && arr[left] < arr[right]) || (arr[(left + right) / 2] > arr[left] && arr[left] > arr[right]))
		{

		}
		else if ((arr[left] < arr[right] && arr[right] < arr[(left + right) / 2]) || (arr[left] > arr[right] && arr[right] > arr[(left + right) / 2])) {
			int temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
		}
		else
		{
			int temp = arr[left];
			arr[left] = arr[(left + right) / 2];
			arr[(left + right) / 2] = temp;
		}
	}
	*/

	int pivot = arr[left];
	int low = left + 1;
	int high = right;
	int temp;
	if (left < right) // left == right�ų�(���Ұ�1��), left>right(0��)�� �ƹ� �۾����� �ʵ���
	{
		if (low == high) //����Ʈ�� ���� ���ڰ� �ΰ��� ���
		{
			if (pivot < arr[high])
				high--;
		}
		else 
		{
			while (high >= low) //�ݺ��۾��ϴٰ� low == high�� �Ǿ��� ��� while���� ������ ���ؼ�
			{
				//�ٲ�� �Ұ��� ���ö����� low�� high�ű�� (�� �������� �ʵ���)
				while (arr[low] <= pivot && low<high)
				{
					low++;
				}
				while (arr[high] >= pivot && low<high)
				{
					high--;
				}


				if (low == high) //������ high�� �ϳ� ���� (high�� �����ϱ����ؼ� high�� low������ ����)
				{
					if (pivot <= arr[high])
						high--;
					break;
				}
				else if (low < high) //���� �ȸ������� ��� �۾�, ���� �����Ǿ��� ��� while�� Ż��ǰ�, high�� ��ġ�� low������ �̵���
				{
					temp = arr[low];
					arr[low] = arr[high];
					arr[high] = temp;
					low++; high--;
				}
			}
		}

		//high�� ��ġ�� �ִ� ���Ҵ� �׻� low�����̹Ƿ� pivot�� �ٲ۴�
		temp = arr[high];
		arr[high] = arr[left];
		arr[left] = temp;
		//�Ǻ��� �����ϰ� QuickSort�� �����Ѵ�.
		QuickSort(arr, left, high - 1);
		QuickSort(arr, high + 1, right);	
	}

}




int main(void)
{
	int n;
	int* arr;

	scanf_s("%d", &n);

	arr = new int[n];
	for (int i = 0; i < n; i++)
		scanf_s("%d", &arr[i]);

	QuickSort(arr, 0, n - 1);

	for (int j = 0; j < n; j++)
		printf_s("%d\n", arr[j]);

}
