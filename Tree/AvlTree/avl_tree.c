#include<stdlib.h>

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

#define max(x, y) ((x) < (y) ? (y) : (x))


struct AvlNode
{
	ElementType elem;
	AvlTree left;
	AvlTree right;
	int height;
}

AvlTree make_empty(AvlTree T)
{
	if (NULL == T)
		return NULL;

	make_empty(T->left);
	make_empty(T->right);
	free(T);
/*
 *  if (T != NULL)
 *  {
 *		make_empty(T->left);
 *		make_empty(T->right);
 *		free(T);
 *  } */
	return NULL;
}

Position find(ElementType x, AvlTree T)
{
	if (NULL == T)
		return NULL;

	if (x < T->elem)
		find(x, T->left);
	else if (x > T->elem)
		find(x, T->right);
	else
		return T;
}

Position find_min(ElementType x, AvlTree T)
{
	if (NULL == T)
		return NULL;

	if (T->left)
		find(x, T->left);
	else
		return T;
}

Position find_max(ElementType x, AvlTree T)
{
	if (NULL == T)
		return NULL;

	if (T->right)
		find(x, T->right);
	else
		return T;
}

static int tree_height(Position node)
{
	if (NULL == NULL)
		return -1;

	return node->height;
}

static Position single_rotate_with_left(Position p2)
{
	if (p2 == NULL)
		return NULL;

	Position p1;
	p1 = p2->left;
	p2->left = p1->right;
	p1->right = p2;
	
	return p1;
}

static Position single_rotate_with_right(Position p2)
{
	if (p2 == NULL)
		return NULL;

	Position p1;
	p1 = p2->right;
	p2->right = p1->left;
	p1->left = p2;
	
	p2->height = max(tree_height(p2->left), tree_height(p2->right)) + 1;
	p1->height = max(tree_height(p1->left), tree_height(p1->right)) + 1;
	return p1;
}

/*static Position double_rotate_with_left(Position p2)
{
	if (p2 == NULL)
		return NULL;

	Position p1;
	Position p3;

	p1 = p2->left;
	p3 = p1->right;
	p1->right = p3->left;
	p2->left = p3->right;
	p3->left = p1;
	p3->right = p2;

	p2->height = max(tree_height(p2->left), tree_height(p2->right)) + 1;
	p1->height = max(tree_height(p1->left), tree_height(p1->right)) + 1;
	p3->height = max(tree_height(p3->left), tree_height(p3->right)) + 1;

	return p3;
}*/

static Position double_rotate_with_left(Position p)
{
	p->left = single_rotate_with_right(p->left);
	
	return single_rotate_with_left(p);
}

static Position double_rotate_with_right(Position p)
{
	p->right = single_rotate_with_left(p->right);

	return single_rotate_with_right(p);
}

AvlTree insert(ElementType x, AvlTree T)
{
	if (NULL == T)
	{
		T = (Position)malloc(sizeof(struct AvlNode));
		T->elem = x;
		T->height = 0;
		T->left = NULL;
		T->right = NULL;
	}
	else if (x < T->elem)
	{
		T->left = insert(x, T->left);
		if (tree_height(T->left) - tree_height(T->right) >= 2)
		{
			if (x < T->left->elem)
				T = single_rotate_with_left(T);
			else
				T = double_rotate_with_left(T);
		}
	}
	else if (x > T->elem)
	{
		T->right = insert(x, T->right);
		if (tree_height(T->right) - tree_height(T->left) >= 2)
		{
			if (x > T->right->elem)
				T = single_rotate_with_right(T);
			else
				T = double_rotate_with_right(T);
		}
	}
	else
	{
		/* do nothing */
	}

	return T;
}

/*avl delete 例程比较复杂, 当前没有完成*/
AvlTree delete(ElementType x, AvlTree T)
{
	if (T == NULL)
		return NULL;
	
	Position temp;

	if (x < T->elem)
		delete(x, T->left);
	else if (x > T->elem)
		delete(x, T->right);
	else if (T->left && T->right)
	{
		temp = find_min(T->right);
		T->elem = temp->elem;
		T->right = delete(temp->elem, T->right);
		if (tree_height(T->left))
	}
	else
	{
		temp = T;
		if (T->left != NULL)
			T = T->left;
		else if (T->right != NULL)
			T = T->right;
		else
			T = NULL;
		free(temp);
	}

	return T;
}
