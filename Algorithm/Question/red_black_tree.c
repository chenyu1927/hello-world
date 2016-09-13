#include<stdio.h>

struct Node
{
	int data;
	int color;
	struct Node *lchild;
	struct Node *rchild;
	struct Node *parent;
};

typedef struct Node * pNode;

struct RBTree
{
	pNode root;
	int size;
};

void insert(RBTree *tree, int x);
int remove(RBTree *tree, int );




