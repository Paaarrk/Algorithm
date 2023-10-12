#include <iostream>


void QuickSort(int arr[], int left, int right)
{
	/* 첫값, 중간값, 끝값 비교해서 피봇 정하기 (더 느려서 뺐습니다)
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
	if (left < right) // left == right거나(원소가1개), left>right(0개)면 아무 작업하지 않도록
	{
		if (low == high) //퀵소트에 들어온 문자가 두개일 경우
		{
			if (pivot < arr[high])
				high--;
		}
		else 
		{
			while (high >= low) //반복작업하다가 low == high가 되었을 경우 while문을 나가기 위해서
			{
				//바꿔야 할곳이 나올때까지 low와 high옮기기 (단 역전되지 않도록)
				while (arr[low] <= pivot && low<high)
				{
					low++;
				}
				while (arr[high] >= pivot && low<high)
				{
					high--;
				}


				if (low == high) //같으면 high를 하나 내림 (high로 조작하기위해서 high를 low범위로 보냄)
				{
					if (pivot <= arr[high])
						high--;
					break;
				}
				else if (low < high) //아직 안만났으니 계속 작업, 만약 역전되었을 경우 while문 탈출되고, high의 위치도 low범위로 이동됨
				{
					temp = arr[low];
					arr[low] = arr[high];
					arr[high] = temp;
					low++; high--;
				}
			}
		}

		//high의 위치에 있는 원소는 항상 low범위이므로 pivot과 바꾼다
		temp = arr[high];
		arr[high] = arr[left];
		arr[left] = temp;
		//피봇을 제외하고 QuickSort를 진행한다.
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
