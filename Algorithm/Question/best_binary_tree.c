#include<stdio.h>
#include<stdlib.h>
//最优二叉查找树
//用到动态规划的方法
//e[i,j]=min{e[i,k-1]+e[k+1,j]+ w[i,j]}
//w[i,j]是i,j之间所有节点的概率和,先不关心
#define MAX 999
void optimal_bst(float *p, /*float *q*/ float **e, int **r, int n)
{
  int i, d, j, kmin;
  int temp, sum;
  for (i = i; i < n+1; ++i)
  {
    e[i][i-1] = 0; /* q[i-1]*/
    e[i][i] = p[i];
    r[i][i] = i;
  }
  e[n+1][n] = 0;
  
  for (d = 1; d <= n-1; ++d)
  {
    for (i = 1; i <= n-d; ++i)
    {
      j = i+d;
      temp = MAX;
      for (k = i; k <= j; ++k)
      {
	if (e[i][k-1]+e[k+1][j] < temp)
	{
	  temp = e[i][k-1]+e[k+1][j];
	  kmin = k;
	}
      }
      r[i][j] = kmin;
      sum = p[i];
      for (s = i+1; s <= j; ++s)
	sum += p[s];

      e[i][j] = temp + sum;
    }
  }
}
