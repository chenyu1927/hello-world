#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct HuffNode
{
	int weight;
	char ch;
	char code[20];
	struct HuffNode *rchild;
	struct HuffNode *lchild;
}HuffMan;

typedef struct _node_
{
	HuffMan *data;
	struct _node_ *next;
}ListNode;

typedef struct
{
	ListNode *front;
	ListNode *rear;
}Queue;

Queue *create_empty_queue()
{
	ListNode *HList;
	Queue *HQueue;

	HList = (struct ListNode*)malloc(sizeof (struct ListNode));
	HList->next = NULL;
	HList->data = NULL;

	HQueue = (Queue *)malloc(sizeof (Queue));
	HQueue->front = HQueue->rear = HList;
	return HQueue;
}

int enter_queue(Queue *q, HuffMan *data)
{
	ListNode *node;
	node = (ListNode *)malloc(sizeof (ListNode));
	node->data = data;
	node->next = NULL;

	q->rear->next = node;
	q->rear = node;

	return 0;
}

int is_empty(Queue *q)
{
	return q->front==q->rear ? 1 : 0;
}

HuffMan * delete_queue(Queue *q)
{
	if (is_empty(q))
		return NULL;

	ListNode *temp = q->front;
	q->front = q->front->next;
	free(temp);
	return q->front->data;
}

int order_enter_queue(Queue *q, HuffMax *data)
{
	ListNode *n = q->front;
	ListNode *m = q->front->next;
	ListNode *cur;

	while (m->data->weight < data->weight)
	{
		n = n->next;
		m = m->next;
	}

	if (m == NULL)
	{
		enter_queue(q, data);
	}
	else
	{
		cur = (ListNode *)malloc(sizeof (ListNode));
		cur->data = data;
		cur->next = m;
		n->next = cur;
	}
	
	return 0;
}

HuffMan *create_huffman_tree(Queue *q)
{
	HuffMan *right, *left;
	HuffMan *cur;
	while(!is_empty(q))
	{
		left = delete_queue(q);
		right = delete_queue(q);
		cur = (HuffMan *)malloc(sizeof (HuffMan));
		cur ->weight = left->weight + right->weight;
		cur->lchild = left;
		cur->rchild = right;
		order_enter_queue(q, cur);
	}

	return q->front->next->data;
}

int huffman_code(HuffMan *root)
{
	
}
