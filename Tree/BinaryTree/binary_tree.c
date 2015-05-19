
#define TreeNode *PtrToNode
struct TreeNode{

	ElementType elem;

	PtrToNode left_child;
	PtrToNode right_child;

	// int height;
};


/*initation   */
PtrToNode make_empty(PtrToNode tree)
{
	if (tree != NULL)
	{
		make_empty(tree->left_child);
		make_empty(tree->right_child);
		free(tree);
	}

	return NULL
}

PtrToNode find(ElementType x, PtrToNode tree)
{
	if (NULL == tree)
		return NULL;

	if (x < tree->elem)
		find(x, tree->left_child);
	else if (x > tree->elem)
		find(x, tree->right_child);
	else
		return tree;
}

PtrToNode find_min(PtrToNode tree)
{
	if (NULL == tree)
		return NULL;

	if (tree->left_child != NULL)
		find_min(tree->left_child);
	else
		return tree;
}

PtrToNode insert(ElementType x, PtrToNode tree)
{
	if (NULL == tree)
	{
		tree = (PtrToNode)malloc(sizeof (struct TreeNode));
		tree->elem = x;
		tree->left_child = NULL;
		tree->right_child = NULL;
	}
	else if (x < tree->elem)
		tree->left = insert(x, tree->left);
	else if (x > tree->elem)
		tree->right = insert(x, tree->right);
	else
	{
		/*do nothing */
	}

	return tree;
}

PtrToNode delete(ElementType x, PtrToNode tree)
{
	if (NULL == tree)
		return NULL;

	PtrToNode temp = NULL;
	if (x < tree->elem)
		delete(x, tree->left);
	else if (x > tree->elem)
		delete(x, tree->right);
	else if (tree->left && tree->right)
	{
		temp = find_min(tree->right);
		tree->elem = temp->elem;
		tree->right = delete(tree->elem, tree->right);
	}
	else
	{
		temp = tree;
		if (tree->left == NULL)
			tree = tree->right;
		else if (tree->right == NULL)
			tree = tree->left;
		free(temp);
	}

	return tree;
}


