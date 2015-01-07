
void reverse(Node *head)
{
	if (head = NULL)
		return;

	Node *p = head;
	Node *p2 = head->next;
	if (p2 == NULL)
		return;

	Node *p3 = p2->next;

	p->next = 0;
	p2->next = p;

	while (p3 != 0)
	{
		p = p2;
		p2 = p3;
		p3 = p3->next;

		p2->next = p;
	}

	p2->next = p;
}
