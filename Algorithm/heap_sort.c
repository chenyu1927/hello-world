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
