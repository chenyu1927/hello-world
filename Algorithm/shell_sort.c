#include<stdio.h>

void shell_insert(int *arrp, int d, int size)
{
	int i;
	for (i = d; i < size; i += 1)
	{
		int j = i - d;
		int temp = arrp[i];
		while (j >= 0 && arrp[j] > temp)
		{
			arrp[j+d] = arrp[j];
			j -= d;
		}
		
		if (j != i -d )
		{
			arrp[j + d] = temp;
		}
	}
}

void shell_sort(int *arrp, int size)
{
	int d = size/2;
	while(d >= 1)
	{
		shell_insert(arrp, d, size);
		d /= 2;
	}
}

int main()
{
	int arr[10] = {54, 67, 21, 23, 11, 44, 54, 91, 85, 57};

	shell_sort(arr, 10);
	int i;
	for (i = 0; i < 10; ++i)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
	return 0;
}
