#include<stdio.h>
//找到路径和等于给定值的所有路径
struct TreeNode
{
  int n_mValue;
  struct TreeNode *left;
  struct TreeNode *right;
};
typedef struct TreeNode *pNode;
int search_num(pNode root, int key)
{
  if (root == NULL && key == 0)
  {
    return 1;
  }
  if (root->left)
  {
    if (search_num(root->left, key - root->n_mValue))
    {
      printf("%d ", root->n_mValue);
      return 1;
    }
  }
  
  if (root->right)
  {
    if (search_num(root->right, key - root->n_mValue))
    {
      printf("%d ", root->n_mValue);
      return 1;
    }
  }

  return 0;
}

void search_num2(pNode root, int key, int path[], int top)
{
	path[top++] = root->n_mValue;
	key -= root->n_mValue;
	if (root->left== NULL && root->right == NULL)
	{
		if (key == 0)
			print_path(path, top);
	}
	else
	{
		if (root->left != NULL)
			search_num2(root->left, key, path, top);
		if (root->right != NULL)
			search_num2(root->right, key, path, top);
	}
}
void print_path(int *path, int n)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		printf("%d ", path[i]);
	}
	printf("\n");
}

int main(void)
{
 
}
