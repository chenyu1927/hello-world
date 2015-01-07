#include<stdio.h>

void fun(int *arr, int n)
{
	int i;
	int x = 0;
	for (i = 0; i < n; ++i)
	{
		x = x^arr[i];
	}

	int y = 1;
	while ((x & y) == 0)
	{
		y << 1;
	}

	int k = 0, m = 0;
	for (i = 0; i < n; ++i)
	{
		if ((arr[i] & y) == 0)
		{
			k ^= arr[i];
		}
		else
			m ^= arr[i];
	}

	printf("%d, %d\n", k, m);
}

int main()
{
	int a[10] = { 5, 13, 56, 7, 22, 5, 56, 13, 33, 33};
	fun(a, 10);
	return 0;
}
