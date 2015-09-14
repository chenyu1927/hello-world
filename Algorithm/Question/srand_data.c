#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

#define MAX_NUM 10000000
int num[MAX_NUM];

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(void)
{
	FILE *fp = fopen("data.txt", "w");
	assert(fp);

	int i;
	for (i = 1; i <= MAX_NUM; ++i)
	{
		num[i-1] = i;
	}

	srand((unsigned)time(NULL));
	size_t n, m;

	int temp;
	for (i = 0; i < MAX_NUM; ++i)
	{
		n = rand() % MAX_NUM;
		m = rand() % MAX_NUM;
		temp = num[n];
		num[n] = num[m];
		num[m] = temp;
	}

	for (i = 0; i < MAX_NUM; ++i)
	{
		fprintf(fp, "%d ", num[i]);
	}

	fclose(fp);

	return 0;
}
