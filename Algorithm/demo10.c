#include<stdio.h>

/* O(n) */
int max_sum(int *arr, int n)
{
	int this_sum, max_sum;
	int i;
	this_sum = max_sum = 0;
	for (i = 0; i < n; ++i)
	{
		this_sum += arr[i];
		if (this_sum > max_sum)
			max_sum = this_sum;

		if (this_sum < 0)
			this_sum = 0;
	}

	return max_sum;
}

/* O(n^2) */
int max_sum2(int *arr, int n)
{
	int max_sum = 0;
	int this_sum = 0;
	int i;
	int j;
	for (i = 0; i < n; ++i)
	{
		this_sum = arr[i];
		for (j = i+1; j < n; ++j)
		{
			this_sum += arr[j];
			if (this_sum > max_sum)
				max_sum = this_sum;
		}
	}

	return max_sum;
}

int max_sum3(int *arr, int n)
{

}

int main()
{
	int arr[8] = {1, -2, 3, 10, -4, 7, 2, -5};
	printf("max_sum: %d\n", max_sum2(arr, 8));

	return 0;
}
