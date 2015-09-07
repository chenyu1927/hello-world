#include<stdio.h>
struct Node
{
	int data;
	struct Node *next;
};
typedef struct Node * ptr_node;

struct List
{
	ptr_node head;
};

typedef struct List* p_list;

int list_length(p_list l)
{
	ptr_node temp = l->head;
	int k = 0;
	
	while (temp != NULL)
	{
		++k;
		temp = temp->next;
	}

	return k;
}

//位考虑有环的情况
ptr_node first_share_point(p_list f_list, p_list s_list)
{
	int f_length = list_length(f_list);
	int s_length = list_length(s_list);

	ptr_node long_list = f_list->head;
	ptr_node short_list = s_list->head;
	int diff_length = f_length - s_length;
	if (diff_length < 0)
	{
		diff_length = s_length - f_length;
		long_list = f_list->head;
		short_list = s_list->head;
	}

	while (diff_length > 0)
	{
		long_list = long_list->next;
		--diff_length;
	}

	while (long_list != NULL && short_list != NULL && 
			short_list != long_list)
	{
		long_list = long_list->next;
		short_list = short_list->next;
	}

	if (long_list == short_list)
		return long_list;

	return NULL;
}

int main(void)
{
	return 0;
}
