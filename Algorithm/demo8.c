#include<stdio.h>
#include<stdlib.h>

void quick_sort(int *arr, int left, int right)
{
	if (left < right)
	{
		int key = arr[left];
		int i = left;
		int j = right;
		while (i < j)
		{
			while (i < j && arr[j] >= key)
				--j;
			arr[i] = arr[j];

			while (i < j && arr[i] <= key)
				++i;
			arr[j] = arr[i];
		}

		arr[i] = key;

		quick_sort(arr, left, i-1);
		quick_sort(arr, i+1, right);
	}
}

void merge(int *arr, int begin, int mid, int end)
{
	int *temp =(int *)malloc((end - begin + 1)*sizeof(int));
	if (temp == NULL)
		return ;

	int i = begin;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= end )
	{
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}

	while (i <= mid)
	{
		temp[k++] = arr[i++];
	}

	while (j <= end)
	{
		temp[k++] = arr[j++];
	}

	for (k = 0, i = begin; i <= end; ++k, ++i)
	{
		arr[i] = temp[k];
	}

	free(temp);
}

void merge_sort(int *arr, int begin, int end)
{
	if (begin < end)
	{
		int mid = (begin + end)/ 2;
		merge_sort(arr, begin, mid);
		merge_sort(arr, mid+1, end);

		merge(arr, begin, mid, end);
	}
}

int main()
{
	int arr[10] = {12, 32, 33, 22, 54, 67, 54, 44, 31, 78};
//	quick_sort(arr, 0, 9);
	merge_sort(arr, 0, 9);
	int i;
	for (i = 0; i < 10; ++i)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");


	return 0;
}
