#include<stdio.h>

int binary_search(int *arr, int n, int value)
{
	int left = 0;
	int right = n - 1;
	int mid;
	while (left <= right)
	{
		mid = left + ((right - left) >> 1);
		if (arr[mid] > value)
			right = mid - 1;
		else if (arr[mid] < value)
			left = mid + 1;
		else
			return mid;
	}

	return -1;
}

int main(void)
{
	int arr[7] = { 1, 5, 17, 25, 47, 89, 90};
	printf("%d \n", binary_search(arr, 7, 90));
	return 0;
}
