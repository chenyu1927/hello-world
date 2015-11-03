#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//对于没有指针和对象类型的语言,如何实现链表呢？
//使用数组来实现链表
//    多数组实现链表 -- c 语言演示
#define SIZE 20
#define NIL -1 // 代表着空

struct List
{
  int next[SIZE];  
  int key[SIZE];   //存整数值
  int prev[SIZE];

  int used_head_idx;  //使用链表头
  int free_head_idx;  //空闲链表头
};
/*struct Node
{
  int idx;
};
typedef struct Node *p_node;*/

typedef struct List *p_list;
//查找操作
int list_search(p_list l, int key)
{
  if (l == NULL)
    return -1;

  int index = l->used_head_idx;
  while (index != NIL && l->key[index] != key)
  {
    index = l->next[index];
  }
  return index;
}
// 插入 空闲链表弹出一个 插入链表头部
int list_insert(p_list l, int key)
{
  int index = l->free_head_idx;
  if (index == NIL)
    return -1;

  l->free_head_idx = l->next[index];
  l->next[index] = l->used_head_idx;
  l->prev[l->used_head_idx] = index;
  l->prev[index] = NIL;
  l->key[index] = key;
  l->used_head_idx = index;
  return index;
}
// 删除
int list_delete(p_list l, int index)
{
  if (index == NIL)
    return -1;

  int pre_index = l->prev[index];
  int next_index = l->next[index];

  l->next[pre_index] = next_index;
  l->prev[next_index] = pre_index;

  l->next[index] = l->free_head_idx;
  l->free_head_idx = index;

  return l->key[index];
}

void list_init(p_list l)
{
  l->used_head_idx = NIL;
  l->free_head_idx = 0;
  int i;
  for (i = 0; i < SIZE; ++i)
  {
    if (i < SIZE-1)
      l->next[i] = i+1;
    else
      l->next[i] = NIL; 
  }
}

int main(void)
{
  p_list l = malloc(sizeof (struct List));
  list_init(l);
  int arr[7] = {56, 253, 34, 98, 10, 45, 61};
  int i;
  for (i = 0; i < 7; ++i)
  {
    list_insert(l, arr[i]);
  }

  printf("%d \n", list_search(l, 98));
  printf("%d \n", list_delete(l, 3));
  return 0;
}

