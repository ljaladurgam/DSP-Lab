/* C program to build the binary search tree, and print the 
   Pre, In and Post order traversal of the built BST. 
   Condition is that the Post order Traversal method should 
   implement in Iterative Way */
   
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

void preorder(Node *root)
{
	if(root!=NULL)
	{
		printf("%d ",root->value);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(Node *root)
{
	if(root!=NULL)
	{
		inorder(root->left);
		printf("%d ",root->value);
		inorder(root->right);
	}
}

// Iterative function to perform post-order traversal of the tree
void postorderIterative(Node* root)
{
    // create an empty stack and push root node
	struct Node* stk[50]; 
    int stk_top = -1, out_top = -1;     
    stk_top++;
    stk[stk_top] = root;
 
    // create another stack to store post-order traversal 
	int out[50]; 
 
    // loop till stack is empty
    while (stk_top!=-1)
    {
        // we pop a node from the stack and push the data to output stack
        Node *curr = stk[stk_top];
        stk[stk_top] = NULL;
        stk_top--;
 
        //out.push(curr->data);
        out_top++;
    	out[out_top] = curr->value;
 
        // push left and right child of popped node to the stack
        if (curr->left)
		{  
            //stk.push(curr->left);  
		    stk_top++;
		    stk[stk_top] = curr->left;
		}
 
        if (curr->right)
		{
            //stk.push(curr->right);
		    stk_top++;
		    stk[stk_top] = curr->right;
		}
    }
 
    // print post-order traversal
    while (out_top!=-1)
    {
        //cout << out.top() << " ";
		printf("%d ",out[out_top]);
        //out.pop();
        out[out_top] = '\0';
        out_top--;
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
    //height = tree_height(root);
    //printf("%d", height);
    //Print the Preorder traversal    
	preorder(root);
    //Print the Inorder traversal   
	printf("\n"); 
	inorder(root);
    //Print the Postorder traversal in Iterative way 
	printf("\n");    
	postorderIterative(root);
 
    // Free the tree
    free_tree(root);
    return 0;
}
