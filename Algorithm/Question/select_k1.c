#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
	*a = *a^*b;
	*b = *a^*b;
	*a = *a^*b;
}
void max_heap(int *arr, int i, int n)
{
	if (NULL == arr)
		return;

	int child = 2*i;

	if (child+1 <= n && arr[child] < arr[child+1])
		child += 1;
	if (child <= n && arr[i] < arr[child])
	{
		swap(arr+i, arr+child);
		max_heap(arr, child, n);
	}
}

void build_heap(int *arr, int n)
{
	if (NULL == arr)
		return;

	int i;
	for (i = n/2; i >= 1; --i)
	{
		max_heap(arr, i, n);
	}
}

int main()
{
	int k = 4;
	int a[13] = {834, 485, 65907, 234, 12, 435, 56, 76, 2434, 546, 54687, 234345, 5456767};
	int *arr = (int *)malloc((k+1)*sizeof(int));
	int i;
	for (i = 1; i <= k; ++i)
	{
		arr[i] = a[i-1];
	}
	build_heap(arr, k);
	for (; i < 13; ++i)
	{
		if (a[i-1] < arr[1])
		{
			arr[1] = a[i-1];
			max_heap(arr, 1, k);
		}
	}
	
	for (i = 1; i <= k; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
