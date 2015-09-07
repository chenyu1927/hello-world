#include<stdio.h>

struct Node
{
	int data;
	struct Node *next;
};
typedef Node * ptr;

struct List
{
	ptr head;
};

int has_circle(struct List* list)
{
	if (NULL == list)
		return 0;

	ptr fast = list->head;
	ptr slow = list->head;

	while (fast != slow && fast && slow)
	{
		if (fast->next != NULL)
			fast = fast->next;

		fast = fast->next;
		slow = slow->next;

	}

	if (fast == slow && fast && slow)
	{
		return 1;
	}
	
	return 0;
}
