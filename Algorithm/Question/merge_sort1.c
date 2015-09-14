#include<stdio.h>
#include<assert.h>
#include<string.h>

#define SIZE 2500000 
static int num[SIZE];

void quick_sort(int *arr, int left, int right)
{
	assert(arr);
	int lh = left;
	int rh = right;

	if (lh < rh)
	{
		int key = arr[lh];
		while (lh < rh)
		{
			while (lh < rh && arr[rh] => key)
				--rh;
			arr[lh] = arr[rh];
			
			while (lh < rh && arr[lh] <= key)
				++lh;
			arr[rh] = arr[lh];
		}

		quicksort(arr, left, lh-1);
		quicksort(arr, rh+1, right);
	}
}

int main(void)
{
	FILE *unsort_fp = fopen("data.txt", "r");
	assert(unsort_fp);
	memset(num, 0, sizeof (num));

	int is_finish = 1, i, k = 0;
	char name[20] = {0};
	
	while (is_finish)
	{
		i = 0;
		while (i < SiZE - 1)
		{
			if (fscanf(unsort_fp, "%d ", num+i) == EOF)
			{
				is_finish = 0;
				break;
			}
			++i;
		}

		quicksort(num, 0, i);
		++k;
		sprintf(name, "sort_%d.txt", k);

		FILE *sort_fp = fopen(name, "w");
		int j;
		for (j = 0; j <= i; ++j)
		{
			fprintf(sort_fp, "%d ", num[j]);
		}

		memset(num, 0, sizeof (num));
	}

	int sort_num[k];
	char flag[k];
	memset(sort_num, 0, sizeof (sort_num));
	memset(flag, 1, sizeof (flag));
	is_finish = 1;
	while (is_finish)
	{
		
	}

	
		
	return 0;
}
