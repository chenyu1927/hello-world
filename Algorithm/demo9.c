#include<stdio.h>


int sec_find(int *arr, int n, int x)
{
	int i = 0;
	int j = n-1;
	while (i <= j)
	{
		int mid = (i+j)/2;
		if (x < arr[mid])
			j = mid-1;
		else if (x > arr[mid])
			i = mid+1;
		else
			return mid;
	}

	return -1;
}

int sec_find2(int *arr, int left, int right, int x)
{
	if (left < right)
	{
		int mid = (left+right)/2;
		if (x < arr[mid])
			sec_find2(arr, left, mid-1, x);
		else if (x > arr[mid])
			sec_find2(arr, mid+1, right, x);

		else
			return mid;
	}

	return -1;
}

int get_upper(int *arr, int n, int x)
{
	int i = 0;
	int j = n-1;
	while(i < j)
	{
		int mid = (i+j+1)/2;
		if (arr[mid] <= x)
			i = mid;
		else
			j = mid -1;
	}

	return i;
}

int get_lower(int *arr, int n, int x)
{
	int i = 0;
	int j = n-1;
	while (i < j)
	{
		int mid = (i+j)/2;
		if (arr[mid] >= x)
			j = mid;
		else
			i = mid+1;
	}

	return i;
}


int main()
{
	int a[6] = {1, 2, 2, 2, 3, 5};
	int b[10] = { 1, 1, 1, 2, 2, 2, 2, 2, 2, 2};
	printf("%d\n", sec_find2(a, 0, 5, 2));

	int k = get_upper(b, 10, 2);
	int m = get_lower(b, 10, 2);
	printf("%d\n", k-m+1);
	//printf("%d, %d\n", (get_upper(b, 10, 1)-get_lower(a, 10, 1)+1),  
	//		(get_upper(b, 10, 2)-get_lower(a, 10, 2)+1));

	return 0;
}
