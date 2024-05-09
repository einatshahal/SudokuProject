#include "general_functions.h"
#include "source3.h"

double mylog(double x, double base)
{
	return (log(x) / log(base));
}

ListNodePlayer** newArr(ListNodePlayer** arr, int* size)
{
	int i;
	int newSize;
	
	double reslog = mylog((*size + 1), 2);
	double res = ceil(reslog);
	newSize = pow(2, res) - 1;

	ListNodePlayer** newArr = (ListNodePlayer*)malloc(newSize * sizeof(ListNodePlayer));
	check_allocation(newArr, "Check Allocation failure!!");

	/*1 2 3 4 n n n*/
	/*0 1 2 3 4 5 6*/

	for (i = 0; i < *size; i++)
	{
		newArr[i] = arr[i];
	}
	for (i = *size; i < newSize; i++)
	{
		newArr[i] =NULL;
	}
	(*size) = newSize;
	//free(arr);
	return newArr;
}

Tree BuildTreeFromArray(ListNodePlayer** arr, int  size)
{
	Tree tr;
	tr.root = recursiveTree(arr, size);
	return tr;
}



TreeNode* recursiveTree(ListNodePlayer** arr, int size)
{
	TreeNode* root;
	TreeNode* left;
	TreeNode* right;

	int l = 0;/*l is the left of the arr*/
	int r = size - 1;/*r is the right of the arr*/
	int mid = (l + r) / 2;/*mid is the middle of the arr*/
	left = NULL;/*the left of the root*/
	right = NULL;/*the right of the root*/

	if (size == 1)
	{
		return createNewTreeNode(arr[0], left, right);/*the middle of the tree is the root*/
	}
	else
	{
		if (arr[(mid) / 2] != NULL) /*there is no right for the root*/
		{

			left = recursiveTree(arr, size / 2);/*build the mini tree of the left side*/

		}
		if (arr[(mid + (mid / 2)) + 1] != NULL) /*there is no left for the root*/
		{
			right = recursiveTree(arr + (size - mid), size / 2);/*build the mini tree of the right side*/
		}
		root = createNewTreeNode(arr[mid], left, right);/*the middle of the tree is the root*/
	}
	return root;
}

TreeNode* createNewTreeNode(ListNodePlayer* data, TreeNode* left, TreeNode* right)
{
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));/*make a new node*/
	check_allocation(newNode, "Check Allocation failure!!");

	newNode->data = data;
	newNode->left = left;
	newNode->right = right;

	return newNode;
}

void printTreeInorder(Tree tr)
{
	printNodes(tr.root);
}

void printNodes(TreeNode* root)
{
	if (root == NULL)
	{
		return;
	}
	printNodes(root->left);
	printf("%s\n ", root->data->data.name);
	printNodes(root->right);
}
void freeTree(Tree tr)
{
	freeNodes(tr.root);
}

void freeNodes(TreeNode* root)
{
	if (root == NULL)
	{
		return;
	}
	freeNodes(root->left);
	freeNodes(root->right);
	free(root);
}

