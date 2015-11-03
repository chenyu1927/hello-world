#include<stdio.h>
//判断整数数组是不是二叉查找树后序遍历的结果

int is_binary_tree(int *arr, int start, int end)
{
  if (start == end)
    return 1;
  int root = end;
  int i = end - 1;
  while(arr[i] >= arr[end] && i >= start)
    i--;
  if (!is_binary_tree(arr, start, i))
    return 0;

  return is_binary_tree(arr, i+1, end-1);
}

int main(void)
{

}
