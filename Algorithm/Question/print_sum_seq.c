#include<stdio.h>

void print_sum_seq(int n)
{
  int i = (n%2 == 0 ? n/2 : n/2+1);
  int j = 1, k;
  int sum;
  for (k = 1; k <= i; ++k)
  {
    sum = 0;
    for (j = k; j <= i; ++j)
    {
      sum += j;
      if (sum == n)
      {
	printf("%d -- %d\n", k, j);
      }
    }
  }
}


int main(void)
{
  int n;
  scanf("%d", &n);
  print_sum_seq(n);
  return 0;
}
