#include<stdio.h>
#include<time.h>
#include<string.h>
#include<assert.h>
#include<sys/time.h>

#define MAX_SCAN 5000000

int main(void)
{
	clock_t begin = clock();
	char bit[MAX_SCAN];
	memset(bit, 0, MAX_SCAN);

	FILE *unsort_fp = fopen("data.txt", "r");
	assert(unsort_fp);
	int num;

	while (fscanf(unsort_fp, "%d ", &num) != EOF) //这里一定要一个空格不然段错误，因为fscanf遇到空格或者换行才结束
	{
		if (num < MAX_SCAN)
			bit[num] = 1;
	}

	FILE *sort_fp = fopen("sort.txt", "w");
	assert(sort_fp);
	int i;
	for (i = 0; i < MAX_SCAN; ++i)
	{
		if (bit[i])
			fprintf(sort_fp, "%d ", i);
	}

	int result = fseek(unsort_fp, 0, SEEK_SET);
	if (result)
		printf("fseek failed!");
	else
	{
		memset(bit, 0, MAX_SCAN);
		while (fscanf(unsort_fp, "%d ", &num) != EOF)
		{
			if (MAX_SCAN <= num && num < 10000000)
				bit[num - MAX_SCAN] = 1;
		}

		for (i = 0; i < MAX_SCAN; ++i)
		{
			if (bit[i])
				fprintf(sort_fp, "%d", i + MAX_SCAN);
		}
	}
	
	clock_t end = clock();
	printf("%d ms\n", (end - begin)/CLOCKS_PER_SEC);

	fclose(unsort_fp);
	fclose(sort_fp);

	return 0;
}
