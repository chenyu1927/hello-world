#include<stdlib.h>

struct TreeNode;
typedef struct TreeNode *p_node;

struct TreeNode
{
	int data;
	int color;
	p_node left;
	p_node right;
	p_node parent;
};

struct RBTree
{
	p_node root;
	struct TreeNode null; 
	int size;
};
typedef struct RBTree *p_tree;

#define _NULL(rbtree) (&((rbtree)->null)) //the NULL of tree
#define rbt_black(rbnode) ((rbnode)->color = 1)
#define rbt_red(rbnode) ((rbnode)->color = 0)
#define rbt_is_black(rbnode) ((rbnode)->color == 1)
#define rbt_is_red(rbnode) ((rbnode)->color == 0)

void rbtree_init(p_tree rbtree)
{
	if (rbtree != NULL)
	{
		rbt_black(_NULL(rbtree));
		rbtree->root = _NULL(rbtree);
		rbtree->size = 0;
	}
}


void rbtree_insert(p_tree rbtree, p_node rbtree_node)
{
	if (rbtree->root == _NULL(rbtree))
	{
		rbtree->root = rbtree_node;
		rbtree_node->parent = _NULL(rbtree)
	}
	else
	{
		p_node x = rbtree->root;
		p_node y;
		while (x != _NULL(rbtree))
		{
			y = x;
			if (x->data < rbtree_node->data)
				x = x->right;
			else
				x = x->left;
		}
		rbtree_node->parent = y;
		if (y->data < rbtree_node->data)
			y->right = rbtree_node;
		else
			y->left = rbtree_node;
	}
	rbtree_node->left = _NULL(rbtree);
	rbtree_node->right =  _NULL(rbtree); 
	rbt_red(rbtree_node);

	rbt_insert_fixup(rbtree, rbtree_node);
	rbtree->size++;
}

void rbt_insert_fixup(p_tree rbt, p_node rbt_node)
{
	if (rbt == NULL || rbt_node == NULL)
		return ;
	
	p_node p, u;
	while (rbt_is_red(rbt_node->parent))
	{
		p = rbt_node->parent;
		if (p == p->parent->left)
		{
			u = p->parent->right;
			if (rbt_is_red(u))
			{
				rbt_red(p->parent);
				rbt_black(p);
				rbt_black(u);
				rbt_node = p->parent;
			}
			else
			{
				if (rbt_node == p->right)
				{
					rbt_node = p;
					single_rotate_with_left(rbt, rbt_node);
					p = rbt_node->parent;
				}

				rbt_black(p);
				rbt_red(p->parent);
				single_rotate_with_right(rbt, rbt_node);
			}
		}
		else
		{
			//对称的，代码一样
		}
	}

	rbt_black(rbt->root);
}

void rbtree_delete(p_tree rbt, p_node node)
{
	if (rbt == NULL || node == NULL || node == _NULL(rbt))
		return ;

	rbt->size--;
	p_node temp, sub;
	if (node->left == _NULL(rbt))
	{
		temp = node;
		sub = temp->right;
	}
	else if (node->right == _NULL(rbt))
	{
		temp = node;
		sub = temp->left;
	}
	else
	{

	}


}

