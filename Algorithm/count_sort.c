#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<google/profiler.h>

void count_sort(int *arr, int n, int k)
{
  int c_arr[k];
  int *data;
  memset(c_arr, 0, sizeof (int)*k);
  data = (int*)malloc(n * sizeof (int));
  int j, i;
  for (j = 0; j < n; ++j)
  {
    c_arr[arr[j]] += 1;
  }
  for (i = 1; i < k; ++i)
  {
    c_arr[i] += c_arr[i-1];
  }
  for (j = n-1; j >= 0; --j)
  {
    data[c_arr[arr[j]]-1] = arr[j];
    c_arr[arr[j]] -= 1;
  }
  for (j = 0; j < n; ++j)
  {
    arr[j] = data[j];
  }
  free(data);
}

int main(void)
{
  int arr[8]={2,5,3,0,2,3,0,3};
//  ProfilerStart("ptest.prof");
  count_sort(arr, 8, 6);
  int i;
  for (i = 0; i < 8; ++i)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
//  ProfilerStop();
  return 0;
}
