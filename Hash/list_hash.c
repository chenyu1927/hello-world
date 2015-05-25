#include<stdlib.h>
#include<stdio.h>


struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable init(int table_size);
void destroy(HashTable h);
Position find(ElementType x, HashTable h);
void insert(ElementType x, HashTable h);


struct ListNode{
	ElementType elem;
	Position next;
};

typedef Position List;

struct HashTbl{
	int table_size;
	List *the_list;
};

HashTable init(int table_size)
{
	HashTable h;
	int i;

	if (table_size < MinTableSize)
	{
		error("table size too small");
		return NULL;
	}

	h = malloc(sizeof (struct HashTbl));
	h->table_size = table_size;
	h->the_list = malloc(sizeof(List) * h->table_size);

	int i;
	for (i = 0; i < h->table_size; ++i)
	{
		h->the_list[i] = malloc(sizeof (struct ListNode));
		h->the_list[i]->next = NULL;
	}

	return h;
}

void destory(HashTable h)
{
	if (h != NULL)
	{
		int i;
		for (i = 0; i < h->table_size; ++i)
		{
			Position temp = NULL;
			while (h->the_list[i])
			{
				temp = h->the_list[i];
				h->the_list[i] = h->the_list[i]->next;
				free(temp);
			}
		}

		free(h->the_list);
		free(h);
	}
}

Position find(ElementType x, HashTable h)
{
	if (NULL == h)
		return NULL;

	List l;
	l = h->the_list[Hash(x, h->table_size)];
	Position p;
	p = l->next;
	while (p && p->elem != x)
	{
		p = p->next;
	}

	return p;
}

void insert(ElementType x, HashTable h)
{
	Position pos = find(x, h);
	if (NULL == pos)
	{
		int index = Hash(x, h->table_size);
		List l;
		l = h->the_list[index];
		Position node = malloc(sizeof (struct ListNode));
		node->next = l->next;
		l->next = node;
		node->elem = x;
	}
}
