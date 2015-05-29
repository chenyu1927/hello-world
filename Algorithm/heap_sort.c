#include<stdio.h>

void heap_adjust(int *a, int i, int n)
{
	int max = i;
	int lchild = i*2;
	int rchild = i*2 + 1;
	if (i <= n/2)
	{
		if (lchild < size && a[lchild] < a[max])
			max = lchild;

		if (rchild < size && a[rchild] < a[max])
			max = rchild;

		if (i != max)
		{
			swap(a[i], a[max]);
			heap_adjust(a, max, n);
		}
	} 
}

#define LEFT_CHILD(i) (2 * (i))
#define RIGHT_CHILD(i) (2 * (i) + 1)

void perc_down(int *arr, int i, int n)
{
	int child;
	int temp;

	for (temp = arr[i]; LEFT_CHILD(i) < n; i = child)
	{
		child = LEFT_CHILD(i);
		if (child < n-1 && arr[child] < arr[child+1])
			++child;

		if (temp < arr[child])
			arr[i] = arr[child];
		else
			break;
	}
	arr[i] = temp; 
}

void heap_sort(int *arr, int n)
{
	int i;
	for (i = n/2; i >= 0; --i)
		prec_down(arr, i, n);

	for (i = n-1; i >= 0; --i)
	{
		swap(arr[0], arr[n-1]);
		perc_down(arr, 0, n);
	}
}
