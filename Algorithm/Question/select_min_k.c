#include<stdio.h>
//选择出数组arr中第i小的元素

int randomized_select(int *arr, int left, int right, int i)
{
  if (left == right)
    return arr[left];

  int begin = left;
  int end = right;
  int key = arr[begin];
  while (begin < end)
  {
    while (begin < end && arr[end] >= key)
      end--;
    arr[begin] = arr[end];
    while (begin < end && arr[begin] <= key)
      begin++;
    arr[end] = arr[begin];
  }
  arr[begin] = key;
  int n = begin - left + 1;
  if (n == i)
    return arr[begin];
  else if (n < i)
  {
    return randomized_select(arr, begin+1, right, i - n);
  }
  else
    return randomized_select(arr, left, begin - 1, i);
}

int main(void)
{
  int arr[10] = {23, 34, 21, 67, 89, 90, 6, 31, 16, 54};
  printf("%d \n", randomized_select(arr, 0, 9, 5));
  return 0;
}
