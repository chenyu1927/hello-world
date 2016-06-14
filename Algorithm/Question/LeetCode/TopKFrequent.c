
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// quick_sort
// >= k

//O(n) < n*log(n)
void TopKFrequent(int *arr, int n, int k)
{
	int maxNum = 0;
	int i;
	for (i = 0; i < n; ++ i)
	{
		if (arr[i] > maxNum)
			maxNum = arr[i];
	}

	int *space = (int *)malloc(sizeof (int) * (maxNum+1));
	memset(space,0, maxNum+1 );
	for (i = 0; i < n; ++ i)
	{
		space[arr[i]] += 1;
	}

	for (i = 0; i < n; ++ i)
	{
		if (space[arr[i]] >= k)
			printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(void)
{
	int arr[15] = {3,3,3,3, 5,5 ,78, 4, 14,14,14,14, 7, 8, 3};

	TopKFrequent(arr, 15, 5);
	return 0;
}
