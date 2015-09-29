#include<stdio.h>

struct Node
{
	int data;
	int color;
	struct Node *lchild;
	struct Node *rchild;
	struct Node *parent;
};
typedef struct Node * node_t;

struct RBTree
{
	struct Node *root;
	int size;
};

void insert(RBTree *tree, int x);



