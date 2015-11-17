#ifndef QUEUE_H_
#define QUEUE_H_

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 20
struct Queue
{
  int data_[MAX_SIZE];
  int tail;
  int head;
};
typedef struct Queue *pQueue;

void queue_init(pQueue q)
{
  q->head = 0;
  q->tail = 1;
}
int is_full(pQueue q)
{
  return q->tail == MAX_SIZE;
}
int is_empty(pQueue q)
{
  return q->head == (q->tail-1);
}
void push(pQueue q, int key)
{
  if (is_full(q))
  {
    printf("queue is full\n");
    return;
  }

  q->data_[q->tail-1] = key;
  q->tail += 1;
}

int pop(pQueue q)
{
  if (is_empty(q))
  {
    printf("queue is empty\n");
    return 0;
  }

  return q->data_[q->head ++];
}



















#endif
