/* C program to Find preorder using inorder and postorder */
#include <stdio.h>
#include <stdlib.h>
 
/* A binary tree node has data, pointer to left
child and a pointer to right child */
struct Node {
	int data;
	struct Node *left, *right;
};

// Utility function to create a new node
struct Node* newNode(int data);

/* Prototypes for utility functions */
int search(int arr[], int strt, int end, int value);

/* Recursive function to construct binary of size n
from Inorder traversal in[] and Postorder traversal
post[]. Initial values of inStrt and inEnd should
be 0 and n -1. The function doesn't do any error
checking for cases where inorder and postorder
do not form a tree */
struct Node* buildUtil(int in[], int post[], int inStrt,
				int inEnd, int* pIndex)
{
	// Base case
	if (inStrt > inEnd)
		return NULL;

	/* Pick current node from Postorder traversal using
	postIndex and decrement postIndex */
	struct Node* node = newNode(post[*pIndex]);
	(*pIndex)--;

	/* If this node has no children then return */
	if (inStrt == inEnd)
		return node;

	/* Else find the index of this node in Inorder
	traversal */
	int iIndex = search(in, inStrt, inEnd, node->data);

	/* Using index in Inorder traversal, construct left and
	right subtress */
	node->right = buildUtil(in, post, iIndex + 1, inEnd, pIndex);
	node->left = buildUtil(in, post, inStrt, iIndex - 1, pIndex);

	return node;
}

// This function mainly initializes index of root
// and calls buildUtil()
struct Node* buildTree(int in[], int post[], int n)
{
	int pIndex = n - 1;
	return buildUtil(in, post, 0, n - 1, &pIndex);
}

/* Function to find index of value in arr[start...end]
The function assumes that value is postsent in in[] */
int search(int arr[], int strt, int end, int value)
{
	int i;
	for (i = strt; i <= end; i++) {
		if (arr[i] == value)
			break;
	}
	return i;
}

/* Helper function that allocates a new node */
struct Node* newNode(int data)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
  
	//struct Node* Node = (struct Node *)malloc(sizeof(struct Node) );
    //struct node* Node = (struct Node *) malloc( sizeof(struct Node) );
 
	node->data = data;
	node->left = node->right = NULL;
	return (node);  
}

/* This funtcion is here just to test */
void preOrder(struct Node* node)
{
	if (node == NULL)
		return;
	printf("%d ", node->data);
	preOrder(node->left);
	preOrder(node->right);
}

// Driver code
int main()
{
    int n,i;
	int in[50],post[50];
	//int in[] = { 4, 2, 5, 1, 6, 3, 7 };
	//int post[] = { 4, 5, 2, 6, 7, 3, 1 }; 
	
   scanf("%d",&n);
 
   for(i=0;i<n;i++)
      scanf("%d",&in[i]);
 
   for(i=0;i<n;i++)
      scanf("%d",&post[i]);
      
	struct Node* root = buildTree(in, post, n);

	//printf("Preorder of the constructed tree : \n");
	preOrder(root);

	return 0;
}

