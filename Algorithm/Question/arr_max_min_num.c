#include<stdio.h>

void search_max_min(int *arr, int n, int *max, int *min)
{
	int i;
	int max_index;
	if (n % 2 == 0)
	{
		max_index = arr[0] > arr[1] ? 0 : 1;
		*max = arr[max_index];
		*min = arr[1-max_index];
		for (i = 2; i < n; i += 2)
		{
			max_index = arr[i] > arr[i+1] ? i : i+1;
			if (arr[max_index] > *max)
				*max = arr[max_index];
			if (arr[2*i + 1 - max_index] < *min)
				*min = arr[2*i+1-max_index];
		}
	}
	else
	{
		*max = *min = arr[0];
		for (i = 1; i < n; i+=2)
		{

			max_index = arr[i] > arr[i+1] ? i : i+1;
			if (arr[max_index] > *max)
				*max = arr[max_index];
			if (arr[2*i + 1 - max_index] < *min)
				*min = arr[2*i+1-max_index];
		}
	}
	
}
