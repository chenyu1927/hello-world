
typedef struct TreeNode *PtrToNode;
struct TreeNode
{
	ElementType elem;
	PtrToNode FirstChild;
	PtrToNode NextSibling;

};

#define Tree PtrToNode
static void preorder( Tree t)
{
	if (t == NULL)
		return;

	print(t);
	preorder(t->FirstChild);
	preorder(t->NextSibling);

}


static void preorder2(Tree t)
{
   
}
