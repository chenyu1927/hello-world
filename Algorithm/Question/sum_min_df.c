#include<stdio.h>
#include<stdlib.h>
//交换两个序列的元素，使得两个序列的和的差最小
void swap(int *a, int *b)
{
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
}

void sum_min_df(int *a, int n, int *b, int m)
{
  if (a == NULL || b == NULL)
    return ;

  int sum_a = 0, sum_b = 0;
  int i, j;
  for (i = 0; i < n; ++i)
    sum_a += a[i];
  for (i = 0; i < m; ++i)
    sum_b += b[i];

  int diff = abs(sum_a - sum_b);
  int sub = 0, best_sub = diff + 1;
  int min_i = -1;
  int min_j = -1;
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < m; ++j)
    {
      sub = abs(a[i] - b[j]);
      if (best_sub > abs(diff/2 - sub))
      {
	  best_sub = abs(diff/2 - sub);
	  min_i = i;
	  min_j = j;
      }
    }
  }
  if (min_i != -1 && min_j != -1)
  {
    if (min_i < n && min_j < m && min_i >= 0 && min_j >= 0)
    {
      int temp = a[min_i];
	  a[min_i] = b[min_j];
	  b[min_j] = temp;
      sum_min_df(a, n, b, m);
    }
  }
}

int main(void)
{
  int a[6] = { 100, 99, 98, 1, 2, 3};
  int b[6] = { 1, 2, 3, 4, 5, 40};

  sum_min_df(a, 6, b, 6);
  int i;
  for (i = 0; i < 6; ++i)
  {
    printf("%d ", a[i]);
  }
  printf("\n");

  for (i = 0; i < 6; ++i)
  {
    printf("%d ", b[i]);
  }
  printf("\n");
  return 0;
}
