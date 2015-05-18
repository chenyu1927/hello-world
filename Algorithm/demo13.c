#include<stdio.h>

int demo(int *arr, int n)
{
	int i;
	int j;
	int min_data = -1;
	for (i = 0; i < n; ++i)
	{
		for (j = i+1; j < n; ++j)
		{
			int data = arr[i] - arr[j];
			if (data < 0)
				data *= -1;
			
			if (min_data == -1 || data < min_data)
				min_data = data;
		}
	}

	return min_data;
}

int demo2(int *arr, int n)
{
	/*排序*/
	/一次循环*/ 
	return 0;
}


int main(void)
{
	int arr[8] = {54, 11, 32, 21, 22, 36, 44, 46};
	printf("%d\n", demo(arr, 8));
	return 0;
}
