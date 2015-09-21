#include<stdio.h>

int is_even(int x)
{
//	return x % 2;
	return x & 1;
}

void reorder(int *arr, int n)
{
	if (NULL == arr)
		return;

	int *p_begin = arr;
	int *p_end = arr+n-1;
	int temp = 0;
	while (p_begin < p_end)
	{
		while (p_begin < p_end && is_even(*p_begin))
			++p_begin;

		while (p_begin < p_end && !is_even(*p_end))
			--p_end;
		
		if (p_begin < p_end)
		{
			temp = *p_begin;
			*p_begin = *p_end;
			*p_end = temp;
		}
	}
}

void reorder2(int *arr, int n)
{
	if (NULL == arr)
		return ;

	int *p_begin = arr;
	int *p_end = arr + n - 1;
	int temp = 0;

	while (p_begin < p_end)
	{
		if (is_even(*p_begin))
		{
			++p_begin;
			continue ;
		}

		if (!is_even(*p_end))
		{
			--p_end;
			continue ;
		}

		temp = *p_begin;
		*p_begin = *p_end;
		*p_end = temp;
	}
}

int main(void)
{
	int arr[11] = {22, 28,15, 7, 79, 64, 53, 39, 82, 13, 42};
	int i;

	reorder2(arr, 11);
	for (i = 0; i < 11; ++i)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
	return 0;
}
