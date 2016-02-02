#include<stdio.h>
#include<stdlib.h>
//求数组中两数之差的最小值
#define INT_MAX 1111111
//先排序，然后求最小差
void quick_sort(int *arr, int left, int right)
{
	if (left < right)
	{
		int key = arr[left];
		int lh = left;
		int rh = right;

		while(left < right)
		{
			while (left < right && arr[right] >= key)
				-- right;
			arr[left] = arr[right];

			while (left < right && arr[left] <= key)
				++ left;
			arr[right] = arr[left];
		}
		arr[left] = key;

		quick_sort(arr, lh, left-1);
		quick_sort(arr, right+1, rh);
	}
}

int arr_min_sub(int *arr, int n)
{
	int i ;
	int min_sub = arr[n-1];
	for (i = 1; i < n; ++ i)
	{
		if ((arr[i] - arr[i-1]) < min_sub)
		{
			min_sub = arr[i] - arr[i-1];
		}
	}

	return min_sub;
}

//这道题其实是连续子序列之和的一个变形
int arr_min_sub_2(int *arr, int n)
{
	int temp[n-1];
	int i;
	for (i = 0; i < n-1; ++ i)
	{
		temp[i] = arr[i] - arr[i+1];
	}

	int min_sub = INT_MAX;
	int temp_sub = 0;
	for (i = 0; i < n-1; ++ i)
	{
		temp_sub += temp[i];
		if (abs(temp_sub) < abs(min_sub))
			min_sub = abs(temp_sub);

		if (i + 1 < n-1)
		{
			if (temp_sub * temp[i+1] > 0)
				temp_sub = 0;
		}
	}

	return min_sub;
}

int main(void)
{
	int arr[10] = {23, 767, 90, 77, 42, 435, 114, 555, 234, 11};
	printf("%d\n", arr_min_sub_2(arr, 10));
	quick_sort(arr, 0, 9);
	int i;
	for (i = 0; i < 10; ++ i)
		printf("%d ", arr[i]);
	printf("\n");

	printf("%d\n", arr_min_sub(arr, 10));
	return 0;
}
