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
			{
				cand = arr[i];
				times++;
			}
			else
				times--;
		}
		else
			times++;
	}

	return cand;
}

int find2(int *arr, int n)
{
	if (NULL == arr)
		return 0;

	int cand1, cand2;
	int times1, times2, i;
	for (i = times1 = times2 = 0; i < n; ++i)
	{
		if (times1 == 0)
		{
			cand1 = arr[i];
			times1++;
		}
		else if (times2 == 0 && cand1 != arr[i])
		{
			cand2 = arr[i];
			times2++;
		}
		else
		{
			if (cand1 == arr[i])
				times1++;
			else if (cand2 == arr[i])
				times2++;
			else
			{
				--times1;
				--times2;
			}
		}
	}

	return times1 > times2 ? cand1 : cand2;
}

int main(void)
{
	int arr[4] = {0, 1, 2, 1};
	printf("%d \n", find(arr, 4));
	printf("%d \n", find2(arr, 4));
	return 0;
}
