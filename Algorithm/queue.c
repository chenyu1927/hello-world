
#define N 1000
typedef struct Queue
{
	int logCnt;
	Node *head;
	Node *tail;
};

typedef struct Node
{
	SYNC_LOG_DATA data;
	Node *next;
}

void sync_log_add(Queue q)
{
	if (q->tail + 1 == q->head)
	{
		q->head = q->head->next;
	}

	q->tail = q->tail
}
