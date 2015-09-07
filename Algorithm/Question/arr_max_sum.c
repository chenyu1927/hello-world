#include<stdio.h>

int select_max(int *arr, int n)
{
	int i;
	int max = 0;
	int temp = 0;
	for (i = 0; i < n; ++i)
	{
		temp += arr[i];
		if (temp < 0)
			temp = 0;

		if (max < temp)
			max = temp;
	}

	return max;
}

int main(void)
{
	int a[5] = {1, -4, 3, 10, 7};
	printf("%d \n", select_max(a, 5));
	return 0;
}

