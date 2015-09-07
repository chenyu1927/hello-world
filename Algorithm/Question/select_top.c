#include<stdio.h>

#define HASHLEN 2807303
#define WORDLEN 30

typedef struct node_no_space* ptr_no_space;
typedef struct node_has_space* ptr_has_space;

struct node_no_space
{
	char *word;
	int count;
	ptr_no_space next;
};

struct node_has_space
{
	char word[WORDLEN];
	int count;
	ptr_has_space next;
};

ptr_no_space head[HASHLEN];

int hash_index(char const *p)
{
	int value = 0;
	while(*p != '\0')
	{
		value = value * 31 + *p++;
		if (value > HASHLEN)
			value = value % HASHLEN;
	}

	return value;
}

void add_word(char *str)
{
	int index = hash_index(str);
	ptr_no_space p = head[index];
	if (p != NULL)
	{
		if (strcmp(str, p->word) == 0)
		{
			p->count++;
			return;
		}

		p = p->next;
	}

	ptr_no_space q = malloc(sizeof (struct node_no_space));
	q->count = 1;
	q->word = malloc(strlen(str)+1);
	strcpy(q->word, str);
	q->next = head[index];
	head[index] = q;
}

void sift_down(node_has_space heap[], int i, int len)
{
	int min_index = -1;
	int left = 2 * i;
	int right = 2 * i + 1;
	if (left <= len && heap[i].count > heap[left].count)
		min_index = left;
	else
		min_index = i;

	if (right <= len && heap[i].count > heap[right].count)
		min_index = right;

	if (min_index != i)
	{
		swap(heap[min_index].count, heap[i].count);
		char buff[WORDLEN];
		strcpy(buff, heap[min_index].word);
		strcpy(heap[min_index].word, heap[i].word);
		strcpy(heap[i].word, buff);
		sift_down(heap, min_index, len);
	}
}

void build_heap(node_has_space heap[], int n)
{
	if (heap == NULL)
		return;

	for (int i = n/2; i > 0; --i)
		sift_down(heap, i, n);
}


