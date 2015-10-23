#include<stdio.h>
#include<stdlib.h>
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
  int i;
  pNode root = NULL;
  for (i = 0; i < 7; ++i)
  {
    if (root == NULL)
      root = tree_insert(root, arr[i]);
    else
      tree_insert(root, arr[i]);
  }
  print_tree(root);
  printf("\n");
  pNode temp;
  temp = tree_to_list(root);
  while (temp)
  {
    printf("%d ", temp->m_nValue);
    temp = temp->right;
  }
  printf("\n");
  return 0;
}

