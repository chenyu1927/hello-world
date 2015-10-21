#include<stdio.h>
#define LEFT_CHILD(i) ((i) << 1)
#define RIGHT_CHILD(i) ((i) << 1 + 1)
#define SWAP(a, b) {(a) = (a)^(b);(b) = (a)^(b); (a) = (a)^(b)}

//保持堆的性质 对i做调整
void max_heapify(int *arr, int i, int size)
{
  int max_index = i;
  int lchild = LEFT_CHILD(i);
  int rchild = LEFT_RIGHT(i);
  if (lchild <= size && arr[lchild] > arr[max_index])
    max_index = lchild;
  if (rchild <= size && arr[rchild] > arr[max_index])
    max_index = rchild;
  
  if (max_index != i)
  {
    SWAP(arr[i], arr[max_index]);
    max_heapify(arr, max_index, size);
  }
}
//保持堆性质的迭代写法  这个写法非常简洁，功力不一般
void max_heap_adjust(int *arr, int i, int size)
{
  int child;
  int temp;
  for (temp = arr[i]; LEFT_CHILD(i) < size; i = child)
  {
    child = LEFT_CHILD(i);
    if (child+1 <= size && arr[child] < arr[child+1])
      ++child;
    if (arr[child] > temp)
      arr[i] = arr[child];
    else
      break;
  }
  arr[i] = temp;
}
//建最大堆
void build_heap(int *arr, int size)
{
  int i;
  for (i = size/2; i > 0; --i)
  {
    max_heapify(arr, i, size);
  }
}
//堆排序
void heap_sort(int *arr, int size)
{
  int i;
  for (i = size; i >= 2; --i)
  {
    SWAP(arr[1], arr[i]);
    max_heapify(arr, 1, i);
  }
}
