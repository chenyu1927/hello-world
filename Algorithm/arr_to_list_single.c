#include<stdio.h>
//单数组的链表实现
// c语言实现
#define SIZE 20
#define FREE_LIST_NODE 0
#define USED_LIST_NODE 1

struct node
{
  int prev_;
  int key_;
  int next_;
  int idx_;

  int is_used_;
};

struct List
{
  struct node data[SIZE];
  int size;
};

//0表示空闲链表的头
//1表示已使用链表的头

typedef struct List *p_list;
typedef struct node *p_node;
void list_init(p_list l)
{
  l->size = 0;
  memset(l->data, 0, sizeof (l->data));
  struct node node;
  //空闲链表头
  node.prev_ = node.next_ = FREE_LIST_NODE;
  node.is_used_ = 1;
  l->data[FREE_LIST_NODE] = node;
  l->size++;

  //已使用表头
  node.prev_ = node.next_ = USED_LIST_NODE;
  node.is_used_ = 1;
  l->data[USED_LIST_NODE] = node;
  l->size++;
}

int valiate_id(int idx)
{
  if (idx < 2 || idx >= SIZE)
    return 0;

  return 1;
}

struct node * head_used(p_list l)
{
  return &(l->data[USED_LIST_NODE]);
}

struct node * head_free(p_list l)
{
  return &(l->data[FREE_LIST_NODE]);
}

void list_insert(p_list l, int key)
{
  if (head_free(l)->next_ == FREE_LIST_NODE && head_free(l)->prev_ == FREE_LIST_NODE)
  {
    struct node node;
    node.prev_ = USED_LIST_NODE;
    node.next_ = head_used(l).next_;
    node.is_used_ = 1;
    node.key_ = key;

    l->data[head_used(l).next].prev_ = l->size;
    head_used(l).next = l->size;

    l->data[l->size] = node;
    l->size++;
  }else{
    p_node first_free_node = &(l->data[head_free(l)->next_]);
    l->data[first_free_node->next_].prev_ = FREE_LIST_NODE;
    head_free(l)->next_ = first_free_node->next_;

    l->data[head_used(l)->next_].prev_ = first_free_node->idx_;
    first_free_node->next_ = head_used(l)->next_;
    head_used(l)->next_ = first_free_node->idx_;
    first_free_node->prev_ = USED_LIST_NODE;
    first_free_node->key_ = key;
  }
}

void list_earse(p_list l, int x)
{
  if (!valiate_idx(x))
    return ;

  p_node node = &(l->data[x]);
  if (!node->is_used_)
    return ;

  l->data[node->next_].prev_ = node->prev_;
  l->data[node->prev_].next_ = node->next_;

  node->prev_ = head_free(l).prev_;
  node->next_ = FREE_LIST_NODE;

  head_free(l)->prev_ = node->idx_;
  node->is_used_ = 0;
}

