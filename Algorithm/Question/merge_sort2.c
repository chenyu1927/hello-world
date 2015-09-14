#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
/* 内存限制1M*/
#define mem_size 250000
#define sort_size 10000000

int read_data(FILE *fp, int *space)
{
	assert(fp && space);
	int index = 0;
	while (index < mem_size && fscanf(fp, "%d ", space + index) != EOF)
		++index;

	return index;
}

void write_data(FILE *fp, int *space, int n)
{
	assert(fp && space);
	int index = 0;
	while (index < n)
	{
		fprintf(fp, "%d ", space[index]);
		++index;
	}
}

void check_fp(FILE *fp)
{
	if (NULL == fp)
	{
		printf("The file pointer is invalid \n");
		exit(-1);
	}
}

int compare(const void *first, const void *second)
{
	return *(int *)first - *(int *)second;
}

int memory_sort()
{
	FILE *unsort_fp = fopen("data.txt", "r");
	check_fp(unsort_fp);

	int counter = 0;
	int *space = calloc(mem_size, sizeof (int));
	char name[20] = {0};

	while (1)
	{
		int num = read_data(unsort_fp, space);
		if (num <= 0)
			break;

		qsort(space, num, sizeof (int), compare);
		counter++;
		sprintf(name, "sort%d.txt", counter);

		FILE *sort_fp = fopen(name, "w");
		write_data(sort_fp, space, num);
		memset(space, 0, mem_size * sizeof(int));
		fclose(sort_fp);
	}

	free(space);
	fclose(unsort_fp);

	return counter;
}

void merge_sort(int file_num)
{
	if (file_num <= 0)
		return;

	FILE *res_fp = fopen("result.txt", "w");
	check_fp(res_fp);

	/*	FILE **file_fp = malloc(sizeof (FILE *) * file_num);*/
	FILE **file_fp = calloc(file_num, sizeof(FILE *));
	int i;
	for (i = 0; i < file_num; ++i)
	{
		char name[20] = {0};
		sprintf(name, "sort%d.txt", i+1);
		file_fp[i] = fopen(name, "r");
		check_fp(sort_fp);

	}

	int *num = calloc(file_num, sizeof (int));
	char *flag = calloc(file_num, sizeof(char));

	for (i = 0; i < file_num; ++i)
	{
		if (fscanf(file_fp[i], "%d ", num+i) == EOF)
			flag[i] = 1;
	}

	FILE *res_fp = fopen("result.txt", "w");
	check_fp(res_fp);

	while (1)
	{
		int min_num = num[0];
		int index = 0;

		for (i = 0; i < file_num; ++i)
		{
			if (flag[i])
				continue;
			
			if (index == 0)
			{
				min_num = num[i];
				index = i;
			}
			else if (num[i] < min_num)
			{
				min_num = num[i];
				index = i;
			}
		}

		fprintf(res_fp, "%d ", min_num);
		if (fscanf(file_fp[index], "%d ", num+index) == EOF)
		{
			flag[index] = 1;
			++finished;
		}
	}
	
	fclose(res_fp);
	free(num);
	free(flag);
	for (i = 0; i < file_num; ++i)
		fclose(file_fp[i]);

	free(file_fp);
}


