#include<stdio.h>

void heapAdjust(int *arr, int i, int n)
{
	int child = 2*i;
	if (child >= n)
		return ;

	if (child+1 < n && arr[child] > arr[child + 1])
		child = 2*i + 1;

	int temp;
	if (arr[i] > arr[child])
	{
		temp = arr[i];
		arr[i] = arr[child];
		arr[child] = temp;
		healAdjust(arr, child, n);
	}
}

void heap_adjust(int *arr, int i, int n)
{
	int max = arr[i];
	int last = arr[n-1];

	int child;
	for (; 2 * i < n; i = child)
	{
		child = 2 * i;
		if (arr[child-1] < arr[child])
			child++;
		if (arr[i-1] < arr[child])
			arr[i-1] = arr[child - 1];
		else
			break;
	}
	arr[i] = last;
}

void k_min(int *arr, int k, int n)
{
	int i;
	for (i = k/2; i >= 0; --i)
	{
		heapAdjust(arr, i, k);
	}
	
	int min;
	for (i = k; i < n; ++i)
	{
		if (arr[i] < arr[0])
		{
			heap_adjust(arr, 0, k);
		}

	}

}

int main(void)
{
	return 0;
}
