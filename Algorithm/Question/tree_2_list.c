#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"queue.hpp"
/*输入一个二叉查找树， 将它转换成一个排序好的双向链表。*/
struct BSTreeNode
{
  int m_nValue;
  struct BSTreeNode *left;
  struct BSTreeNode *right;
};
typedef struct BSTreeNode *pNode;
pNode tree_to_list(pNode root)
{
  pNode temp;
  if (root->left == NULL && root->right == NULL)
    temp = root;
  if (root->right)
  {
    pNode rchild = tree_to_list(root->right);
    root->right = rchild;
    rchild->left = root;
    temp = root;
  }
  if (root->left)
  {
    pNode lchild = tree_to_list(root->left);
    temp = lchild;
    while (lchild->right)
      lchild = lchild->right;
    root->left = lchild;
    lchild->right = root;
  }
  return temp;
}
void print_num(int *arr, int n);
//找出所有和等于给定值的路径
void search_num(pNode root, int key, int *arr, int top)
{
	if (NULL == root)
		return ;
	arr[top++] = root->m_nValue;
	key -= root->m_nValue;
	if (root->left == NULL && root->right == NULL)
	{
		if (key == 0)
		{
			print_num(arr, top);
		}
	}

	if (root->left)
	{
		search_num(root->left, key, arr, top);
	}
	
	if (root->right)
	{
		search_num(root->right, key, arr, top);
	}
}

// 转换二叉查找树使左子树都大于右子树
void tree_left_to_right(pNode root)
{
  if (root)
  {
    pNode temp = root->left;
    root->left = root->right;
    root->right = temp;

    tree_left_to_right(root->left);
    tree_left_to_right(root->right);
  }
}
//迭代版需要用栈来回溯
void tree_left_to_right2(pNode root)
{
  if(root == NULL)
    return ;

  struct stack buf;
  buf.push(root);
  while (!buf.is_empty())
  {
    pNode temp = buf.pop();
    swap(temp->left, temp->right);
    if (temp->left) buf.push(temp->left);
    if (temp->right) buf.push(temp->right);
  }
}

//按照层次输出二叉树，每一层从左到右
void tree_to_queue(pNode root)
{
	if (root == NULL)
		return ;

	struct queue q;
	q.push(root);
	while (!q.is_empty())
	{
		pNode  temp = q.pop();
		print(temp);

		if (temp->left)	q.push(temp->left);
		if (temp->right) q.push(temp->right);

	}
}
//非递归版的中序遍历
void mid_tree_print(pNode root)
{
	if (root == NULL)
		return ;
	struct stack buf;
	pNode temp;
	buf.push(root);
	while (!buf.is_empty)
	{
		temp = buf.pop();
		while (temp != NULL)
		{
			if (temp->right) buf.push(temp->right);
			buf.push(temp);
			if (temp->left) buf.push(temp->left);
			temp = temp->left;
		}

		while (1)
		{
			temp = buf.pop();
			print(temp);

			if (temp->right) break;
		}
	}
}
void print_num(int *arr, int n)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

pNode tree_insert(pNode root, int key)
{
  if (NULL == root)
  {
    root = malloc(sizeof (struct BSTreeNode));
    root->m_nValue = key;
    root->left = NULL;
    root->right = NULL;
  }
  else
  {

    if (root->m_nValue < key)
      root->right = tree_insert(root->right, key);
    else
      root->left = tree_insert(root->left, key);
  }
  return root;
}

void print_tree(pNode root)
{
  if (root)
  {
    printf("%d ", root->m_nValue);
    print_tree(root->left);
    print_tree(root->right);
  }
}
int main(void)
{
  int arr[7] = {10, 6, 14, 4, 8, 12, 16};
  int brr[5]  = {10, 5, 12, 4, 7};
  int i;
  pNode root = NULL;
  for (i = 0; i < 5; ++i)
  {
    if (root == NULL)
      root = tree_insert(root, brr[i]);
    else
      tree_insert(root, brr[i]);
  }

  int trr[3];
  memset(trr, 0, sizeof (trr));
  search_num(root, 22, trr, 0);

  print_tree(root);
  printf("\n");
  tree_left_to_right(root);
  print_tree(root);
  printf("\n");
/*  print_tree(root);
  printf("\n");
  pNode temp;
  temp = tree_to_list(root);
  while (temp)
  {
    printf("%d ", temp->m_nValue);
    temp = temp->right;
  }
  printf("\n");*/
  return 0;
}

