#include<stdio.h>

int find(int *arr, int n)
{
	if (arr == NULL)
		return 0;

	int cand = 0, times = 0, i;
	for (i = 0; i < n; ++i)
	{
		if (cand != arr[i])
		{
			if (times == 0)
				cand = arr[i];
			else
				times--;
		}
		else
			times++;
	}

	return cand;
}

int main(void)
{
	int arr[7] = { 5, 2, 4, 5, 5, 6, 5};
	printf("%d \n", find(arr, 7));
	return 0;
}
