#include<stdio.h>

int sum[5000010];

int main(void)
{
	/*init*/
	int i;
	int j;
	for (i = 0; i <= 5000000; ++i)
		sum[i] = 1;

	/*预处理*/
	for (i = 2; (i + i) <= 5000000; ++i)
	{
		j = i + i;
		while (j <= 5000000)
		{
			sum[j] += i;
			j += i;
		}
	}

	for (i = 220; i <= 5000000; ++i)
	{
		if (sum[i] > i && sum[i] <= 5000000 && sum[sum[i]] == i)
		{
			printf("%d, %d\n", i, sum[i]);
		}
	}

	return 0;
}
