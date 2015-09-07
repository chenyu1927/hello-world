#include<stdio.h>
#include<assert.h>
struct Node
{
	int data;
	struct List *next;
};
typedef struct Node* ptr_node;

struct List
{
	struct Node *head;
};

struct Node *select_k(struct List *list, int k)
{
	assert(list != NULL);
	ptr_node ptr1 = list->head;
	ptr_node ptr2 = list->head;
	while (k > 0 && ptr1 != NULL)
	{
		ptr1 = ptr->next;
		--k;
	}

	if (k > 0)
		return NULL;

	while (ptr1 != NULL)
	{
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}

	return ptr2;
}

int main(void)
{
	return 0;
}
