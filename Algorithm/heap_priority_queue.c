#include<stdio.h>
#include"heap_sort2.c"

#define PARENT(i) ((i)>>1)
//返回arr中最大的元素(O(1))
int maximum(int *arr)
{
  if (NULL == arr)
    return 0;
  else
    return arr[1];
}

//extract-max删除最大的元素
//size代表的是元素个数
int heap_extract_max(int *arr, int size)
{
  if (size <= 0)
    return -1;
  int max;
  max = arr[1];
  arr[1] = arr[size];
  size = size -1;
  max_heapify(arr, 1, size);
  return max;
}
// 增加关键字的值(O(lgn))
void heap_increase_key(int *arr, int i, int key)
{
  if (arr[i] > key)
    return;
  arr[i] = key;
  while (i > 1 && arr[PARENT(i)] < arr[i])
  {
    SWAP(arr[i], arr[PARENT(i)]);
    i = PARENT(i);
  }
}

//插入元素
void heap_insert(int *arr, int key)
{
  size = size + 1;
  arr[size] = key;
  int i = size;
  while (i > 1 && arr[PARENT(i)] < arr[i])
  {
    SWAP(arr[i], arr[PARENT(i)]);
    i = PARENT(i);
  }
}
