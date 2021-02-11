/* C program to Find the height of the Binary search tree */
#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node Node;
 
void insert(Node *,Node *);
 
// Define the Tree Node here
struct Node {
    int value;
    // Pointers to the left and right children
    Node* left, *right;
};
  
Node* create_node(int data) {
    // Creates a new node
    Node* node = (Node*) malloc (sizeof(Node));
    node->value = data;
    node->left = node->right = NULL;
    return node;
}

void insert(Node *root, Node *temp)
{
	if(temp->value < root->value)
	{
		if(root->left!=NULL)
			insert(root->left,temp);
		else
			root->left=temp;
	}
	
	if(temp->value > root->value)
	{
		if(root->right!=NULL)
			insert(root->right,temp);
		else
			root->right=temp;
	}
}
 
void free_tree(Node* root) {
    // Deallocates memory corresponding
    // to every node in the tree.
    Node* temp = root;
    if (!temp)
        return;
    free_tree(temp->left);
    free_tree(temp->right);
    if (!temp->left && !temp->right) {
        free(temp);
        return;
    }
}
 
int tree_height(Node* root) {
    // Get the height of the tree
    if (!root)
        return 0;
    else {
        // Find the height of both subtrees
        // and use the larger one
        int left_height = tree_height(root->left);
        int right_height = tree_height(root->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}
 
int main() {
	
    int n,i,height;
	int arr[50];
	Node *root=NULL,*temp; 
	
   scanf("%d",&n);
 
   for(i=0;i<n;i++)
      scanf("%d",&arr[i]);
 
   for(i=0;i<n;i++)
   {	
   		//Create a node of BST
   		temp=create_node(arr[i]);
		if(root==NULL)
			root=temp;
		else	
			//Insert node in the BST
			insert(root,temp);   	
   }
 
    // Find the height of the tree
    height = tree_height(root);
    printf("%d", height);
 
    // Free the tree
    free_tree(root);
    return 0;
}
