#include<stdio.h>
#include<stdlib.h>
/*设计包含min函数的栈， 要求min, push, pop操作都是O(1)*/
/*这里有个陷阱就是pop操作后如何知道min元素*/
#define MAX_SIZE 50
struct elem
{
  int data;
  int min;
};

struct stack
{
  struct elem *elem_arr;
  int top;
  int size;
};

typedef struct stack *pStack;
typedef struct elem Elem;

pStack init(int size)
{
  pStack s;
  s = malloc(sizeof (struct stack));
  s->top = 0;
  s->size = size;
  s->elem_arr = calloc(size, sizeof (Elem));
  return s;
}

void destroy(pStack s)
{
  if (s->elem_arr)
    free(s->elem_arr);
  free(s);
}

void push(pStack s, int key)
{
  if (s->top >= s->size)
  {
    printf("full stack\n");
  }
  else
  {

    s->elem_arr[s->top].data = key;
    if (s->top == 0 || key < s->elem_arr[s->top - 1].min)
      s->elem_arr[s->top].min = key;
    else
      s->elem_arr[s->top].min = s->elem_arr[s->top - 1].min;

    s->top++;
  }
}

int pop(pStack s)
{
  if (s->top <= 0)
  {
    printf("empty stack\n");
    return 0;
  }

  // return s->elem_arr[--s->top].data;
  s->top--;
  return s->elem_arr[s->top].data;
}

int min(pStack s)
{
  if (s->top <= 0)
  {
    printf("empty stack");
    return 0;
  }
  return s->elem_arr[s->top - 1].min;
}

int main(void)
{
  int arr[10] = {34, 21, 23, 12, 34, 45, 98, 22, 85, 19};
  pStack s;
  s = init(10);
  int i;
  for (i = 0; i < 10; ++i)
  {
    push(s, arr[i]);
    printf("%d, min=%d ", arr[i],min(s));
  }
  printf("\n");
  while (s->top)
  {
    printf("%d,", pop(s));
    printf("min=%d ",min(s));
  }
  printf("\n");
  return 0;
}


