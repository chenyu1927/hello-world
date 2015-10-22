#include<stdio.h>

void swap(int *a, int *b)
{
  if (a == b)
    return ;
  (*a) = (*a) ^ (*b);
  (*b) = (*a) ^ (*b);
  (*a) = (*a) ^ (*b);
}
void quick_sort(int *arr, int left, int right)
{
  if (left < right)
  {
    int p;
    p = partition(arr, left, right);
    quick_sort(arr, left, p-1);
    quick_sort(arr, p+1, right);
  }
}

int partition(int *arr, int left, int right)
{
  int key, i, j;
  key = arr[right];
  i = left -1;
  for (j = left; j < right; ++j)
  {
    if (arr[j] <= key)
    {
      ++i;
      swap(arr+i, arr+j);
    }
  }
  swap(arr+i+1, arr+right);
  return i+1;
}

void quick_sort2(int *arr, int left, int right)
{
  if (left < right)
  {
    int key, i, j;
    i = left;
    j = right;
    key = arr[left];
    while (i < j)
    {
      while (i < j && arr[j] >= key)
	--j;
      arr[i] = arr[j];
      while (i < j && arr[i] <= key)
	++i;
      arr[j] = arr[i];
    }
    arr[i] = key;
    quick_sort2(arr, left, i-1);
    quick_sort2(arr, i+1, right);
  }
}

int main(void)
{
  int arr[7] = {45, 13, 3, 56, 21, 45, 98};
  quick_sort(arr, 0, 6);
  int i;
  for (i = 0; i < 7; ++i)
    printf("%d ", arr[i]);
  printf("\n");
  return 0;
}
