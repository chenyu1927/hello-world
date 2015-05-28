
#ifndef _BinHeap_H
#define _BinHeap_H

struct HeapStruct{
	int capacity;
	int size;
	ElementType *elems;
};
typedef struct HeapStruct *PriorityQueue;

PriorityQueue init(int max_size)
{
	PriorityQueue q = malloc(sizeof(struct HeapStruct));
	if (NULL == q)
		return NULL;

	q->capacity = max_size;
	q->elems = malloc(sizeof (Element) * (max_size + 1));
	q->size = 0;
	q->elems[0] = MinData;

	return q;
}

void destroy(PriorityQueue q)
{
	if (NULL == q)
		return NULL;

	free(q->elems);
	free(q);
}

void insert(ElementType x, PriorityQueue q)
{
	if (NULL == q)
		return NULL;

/*	int pos;
	pos = size;
	while (x < q->elems[size/2])
	{
		q->elems[size] = q->elems[size/2];
		pos = size/2;
	}

	q->elems[pos] = x;*/
	int i;
	for (i = ++q->size; q->elems[i/2] > x; i /= 2)
		q->elems[i] = q->elems[i/2];

	q->elems[i] = x;
}

ElementType delete_min(PriorityQueue q)
{
	if (NULL == q)
		return NULL;

	if (q->size == 0)
		return 0;

	int min_data = q->elems[1];
	int last_data = q->elems[q->size--];
	int i = 1;
	while (i * 2 < q->size)
	{
		if (q->elems[2*i] < q->elems[2*i + 1])
		{
			q->elems[i] = q->elems[2 * i];
			i = 2 * i;
		}
		else if(q->elems[2 * i] > q->elems[2*i + 1]) 
		{
			q->elems[i] = q->elems[2 * i + 1];
			i = 2 * i + 1;
		}
		else
			break;
	}

	q->elems[i] = last_data;
	
	return min_data;
}

#endif
