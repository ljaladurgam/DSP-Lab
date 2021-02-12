/* 
   Roll number: 20MCMB05
   Name: Lakshminarayana Jaladurgam
   Menu driven C program to perform the operations Insert, Delete, Search, Find Height
   and Print using Pre-Order traversal on B-Trees.   
*/  

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
 
// Define BTree node structure
struct BTreeNode 
{ 
	int *keys; // An array of keys 
	int t;	 // Minimum degree (defines the range for number of keys) 
	struct BTreeNode **C; // An array of child pointers 
	int n;	 // Current number of keys 
	bool leaf; // Is true when node is leaf. Otherwise false 
};

//Define BTree structure
struct BTree 
{ 
	struct BTreeNode *root; // Pointer to root node 
	int t; // Minimum degree 
};

//Declaration of functions 

//Create new BTreeNode
struct BTreeNode* newBTreeNode(int _t, bool _leaf);

// A function to traverse all nodes in a subtree rooted with this node 
void traverseBTreeNode(struct BTreeNode *btn); 

// A function to search a key in subtree rooted with this node. 
struct BTreeNode *searchBTreeNode(struct BTreeNode *btn, int k); // returns NULL if k is not present. 

// A function that returns the index of the first key that is greater 
// or equal to k 
int findKeyBTreeNode( struct BTreeNode *btn, int k); 

// A utility function to insert a new key in the subtree rooted with 
// this node. The assumption is, the node must be non-full when this 
// function is called 
void insertNonFullBTreeNode(struct BTreeNode *btn, int k); 

// A utility function to split the child y of this node. i is index 
// of y in child array C[]. The Child y must be full when this 
// function is called 
void splitChildBTreeNode( struct BTreeNode *btn, int i, struct BTreeNode *y); 

// A wrapper function to remove the key k in subtree rooted with 
// this node. 
void removeBTreeNode( struct BTreeNode *btn, int k); 

// A function to remove the key present in idx-th position in 
// this node which is a leaf 
void removeFromLeafBTreeNode( struct BTreeNode *btn, int idx); 

// A function to remove the key present in idx-th position in 
// this node which is a non-leaf node 
void removeFromNonLeafBTreeNode( struct BTreeNode *btn, int idx); 

// A function to get the predecessor of the key- where the key 
// is present in the idx-th position in the node 
int getPredBTreeNode( struct BTreeNode *btn, int idx); 

// A function to get the successor of the key- where the key 
// is present in the idx-th position in the node 
int getSuccBTreeNode( struct BTreeNode *btn, int idx); 

// A function to fill up the child node present in the idx-th 
// position in the C[] array if that child has less than t-1 keys 
void fillBTreeNode(struct BTreeNode *btn, int idx); 

// A function to borrow a key from the C[idx-1]-th node and place 
// it in C[idx]th node 
void borrowFromPrevBTreeNode(struct BTreeNode *btn, int idx); 

// A function to borrow a key from the C[idx+1]-th node and place it 
// in C[idx]th node 
void borrowFromNextBTreeNode(struct BTreeNode *btn, int idx); 

// A function to merge idx-th child of the node with (idx+1)th child of 
// the node 
void mergeBTreeNode( struct BTreeNode *btn, int idx); 

// The main function that inserts a new key in this B-Tree 
void insertBTree(struct BTree *btree, int k); 

// The main function that removes a new key in thie B-Tree 
void removeBTree(struct BTree *btree, int k); 

// Create New BTreeNode
struct BTreeNode* newBTreeNode(int t1, bool leaf1) 
{ 
    struct BTreeNode* btNode; 
	btNode = (struct BTreeNode *) malloc( sizeof(struct BTreeNode) );
	
	// Copy the given minimum degree and leaf property 
	btNode->t = t1; 
	btNode->leaf = leaf1; 

	// Allocate memory for maximum number of possible keys 
	// and child pointers  
	int* keys1 = malloc(2*t1-1*sizeof(*keys1));   
	btNode->keys = keys1;    
	struct BTreeNode* btn = malloc(2*t1*sizeof(*btn));  
	btNode->C = btn;  

	// Initialize the number of keys as 0 
	btNode->n = 0; 
	
	return btNode;
} 

// Initializes tree as empty
struct BTree* newBTree(int _t) 
{ 	
    struct BTree* btree;       
	btree = (struct BTree *) malloc( sizeof(struct BTree) ); 
	
	btree->root = NULL; 
	btree->t = _t; 
	return btree;
} 

//Traverse BTree
void traverseBTree( struct BTree *btree ) 
{ 
	if (btree->root != NULL) traverseBTreeNode(btree->root); 
} 

// function to search a key in this tree 
struct BTreeNode* searchBTree(struct BTree *btree, int k) 
{ 
	return (btree->root == NULL)? NULL : searchBTreeNode(btree->root, k); 
} 

// A utility function that returns the index of the first key that is 
// greater than or equal to k 
int findKeyBTreeNode(struct BTreeNode *btn, int k) 
{ 
	int idx=0; 
	while (idx<btn->n && btn->keys[idx] < k) 
		++idx; 
	return idx; 
} 

// A function to remove the key k from the sub-tree rooted with this node 
void removeBTreeNode( struct BTreeNode *btn, int k) 
{ 
	int idx = findKeyBTreeNode( btn, k); 

	// The key to be removed is present in this node 
	if (idx < btn->n && btn->keys[idx] == k) 
	{ 

		// If the node is a leaf node - removeFromLeaf is called 
		// Otherwise, removeFromNonLeaf function is called 
		if (btn->leaf) 
			removeFromLeafBTreeNode(btn, idx); 
		else
			removeFromNonLeafBTreeNode(btn, idx); 
	} 
	else
	{ 

		// If this node is a leaf node, then the key is not present in tree 
		if (btn->leaf) 
		{ 
			printf(" The key %d does not exist in the tree\n",k); 
			return; 
		} 

		// The key to be removed is present in the sub-tree rooted with this node 
		// The flag indicates whether the key is present in the sub-tree rooted 
		// with the last child of this node 
		bool flag = ( (idx==btn->n)? true : false ); 

		// If the child where the key is supposed to exist has less that t keys, 
		// we fill that child 
		if (btn->C[idx]->n < btn->t) 
			fillBTreeNode(btn, idx); 

		// If the last child has been merged, it must have merged with the previous 
		// child and so we recurse on the (idx-1)th child. Else, we recurse on the 
		// (idx)th child which now has atleast t keys 
		if (flag && idx > btn->n) 
			removeBTreeNode(btn->C[idx-1], k); 
		else
			removeBTreeNode(btn->C[idx], k); 
	} 
	return; 
} 

// A function to remove the idx-th key from this node - which is a leaf node 
void removeFromLeafBTreeNode( struct BTreeNode *btn, int idx) 
{ 
    int i; 
	// Move all the keys after the idx-th pos one place backward 
	for (i=idx+1; i<btn->n; ++i) 
		btn->keys[i-1] = btn->keys[i]; 

	// Reduce the count of keys 
	btn->n--; 

	return; 
} 

// A function to remove the idx-th key from this node - which is a non-leaf node 
void removeFromNonLeafBTreeNode( struct BTreeNode *btn, int idx) 
{ 

	int k = btn->keys[idx]; 

	// If the child that precedes k (C[idx]) has atleast t keys, 
	// find the predecessor 'pred' of k in the subtree rooted at 
	// C[idx]. Replace k by pred. Recursively delete pred 
	// in C[idx] 
	if (btn->C[idx]->n >= btn->t) 
	{ 
		int pred = getPredBTreeNode(btn, idx); 
		btn->keys[idx] = pred; 
		removeBTreeNode(btn->C[idx], pred); 
	} 

	// If the child C[idx] has less that t keys, examine C[idx+1]. 
	// If C[idx+1] has atleast t keys, find the successor 'succ' of k in 
	// the subtree rooted at C[idx+1] 
	// Replace k by succ 
	// Recursively delete succ in C[idx+1] 
	else if (btn->C[idx+1]->n >= btn->t) 
	{ 
		int succ = getSuccBTreeNode(btn, idx); 
		btn->keys[idx] = succ; 
		removeBTreeNode(btn->C[idx+1], succ); 
	} 

	// If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1] 
	// into C[idx] 
	// Now C[idx] contains 2t-1 keys 
	// Free C[idx+1] and recursively delete k from C[idx] 
	else
	{ 
		mergeBTreeNode(btn, idx); 
		removeBTreeNode(btn->C[idx], k); 
	} 
	return; 
} 

// A function to get predecessor of keys[idx] 
int getPredBTreeNode( struct BTreeNode *btn, int idx) 
{ 
	// Keep moving to the right most node until we reach a leaf 
	struct BTreeNode *cur = btn->C[idx]; 
	while (!cur->leaf) 
		cur = cur->C[cur->n]; 

	// Return the last key of the leaf 
	return cur->keys[cur->n-1]; 
} 

// A function to get successor of keys[idx] 
int getSuccBTreeNode( struct BTreeNode *btn, int idx) 
{ 

	// Keep moving the left most node starting from C[idx+1] until we reach a leaf 
	struct BTreeNode *cur = btn->C[idx+1]; 
	while (!cur->leaf) 
		cur = cur->C[0]; 

	// Return the first key of the leaf 
	return cur->keys[0]; 
} 

// A function to fill child C[idx] which has less than t-1 keys 
void fillBTreeNode(struct BTreeNode *btn, int idx) 
{ 

	// If the previous child(C[idx-1]) has more than t-1 keys, borrow a key 
	// from that child 
	if (idx!=0 && btn->C[idx-1]->n>=btn->t) 
		borrowFromPrevBTreeNode(btn, idx); 

	// If the next child(C[idx+1]) has more than t-1 keys, borrow a key 
	// from that child 
	else if (idx!=btn->n && btn->C[idx+1]->n>=btn->t) 
		borrowFromNextBTreeNode(btn, idx); 

	// Merge C[idx] with its sibling 
	// If C[idx] is the last child, merge it with with its previous sibling 
	// Otherwise merge it with its next sibling 
	else
	{ 
		if (idx != btn->n) 
			mergeBTreeNode(btn, idx); 
		else
			mergeBTreeNode(btn, idx-1); 
	} 
	return; 
} 

// A function to borrow a key from C[idx-1] and insert it 
// into C[idx] 
void borrowFromPrevBTreeNode(struct BTreeNode *btn, int idx) 
{ 
    int i; 
	struct BTreeNode *child=btn->C[idx]; 
	struct BTreeNode *sibling=btn->C[idx-1]; 

	// The last key from C[idx-1] goes up to the parent and key[idx-1] 
	// from parent is inserted as the first key in C[idx]. Thus, the loses 
	// sibling one key and child gains one key 

	// Moving all key in C[idx] one step ahead 
	for (i=child->n-1; i>=0; --i) 
		child->keys[i+1] = child->keys[i]; 

	// If C[idx] is not a leaf, move all its child pointers one step ahead 
	if (!child->leaf) 
	{ 
		for(i=child->n; i>=0; --i) 
			child->C[i+1] = child->C[i]; 
	} 

	// Setting child's first key equal to keys[idx-1] from the current node 
	child->keys[0] = btn->keys[idx-1]; 

	// Moving sibling's last child as C[idx]'s first child 
	if(!child->leaf) 
		child->C[0] = sibling->C[sibling->n]; 

	// Moving the key from the sibling to the parent 
	// This reduces the number of keys in the sibling 
	btn->keys[idx-1] = sibling->keys[sibling->n-1]; 

	child->n += 1; 
	sibling->n -= 1; 

	return; 
} 

// A function to borrow a key from the C[idx+1] and place 
// it in C[idx] 
void borrowFromNextBTreeNode(struct BTreeNode *btn, int idx) 
{ 
    int i; 
	struct BTreeNode *child=btn->C[idx]; 
	struct BTreeNode *sibling=btn->C[idx+1]; 

	// keys[idx] is inserted as the last key in C[idx] 
	child->keys[(child->n)] = btn->keys[idx]; 

	// Sibling's first child is inserted as the last child 
	// into C[idx] 
	if (!(child->leaf)) 
		child->C[(child->n)+1] = sibling->C[0]; 

	//The first key from sibling is inserted into keys[idx] 
	btn->keys[idx] = sibling->keys[0]; 

	// Moving all keys in sibling one step behind 
	for (i=1; i<sibling->n; ++i) 
		sibling->keys[i-1] = sibling->keys[i]; 

	// Moving the child pointers one step behind 
	if (!sibling->leaf) 
	{ 
		for(i=1; i<=sibling->n; ++i) 
			sibling->C[i-1] = sibling->C[i]; 
	} 

	// Increasing and decreasing the key count of C[idx] and C[idx+1] 
	// respectively 
	child->n += 1; 
	sibling->n -= 1; 

	return; 
} 

// A function to merge C[idx] with C[idx+1] 
// C[idx+1] is freed after merging 
void mergeBTreeNode( struct BTreeNode *btn, int idx) 
{ 
	int i;
	struct BTreeNode *child = btn->C[idx]; 
	struct BTreeNode *sibling = btn->C[idx+1]; 

	// Pulling a key from the current node and inserting it into (t-1)th 
	// position of C[idx] 
	child->keys[btn->t-1] = btn->keys[idx]; 

	// Copying the keys from C[idx+1] to C[idx] at the end 
	for (i=0; i<sibling->n; ++i) 
		child->keys[i+btn->t] = sibling->keys[i]; 

	// Copying the child pointers from C[idx+1] to C[idx] 
	if (!child->leaf) 
	{ 
		for(i=0; i<=sibling->n; ++i) 
			child->C[i+btn->t] = sibling->C[i]; 
	} 

	// Moving all keys after idx in the current node one step before - 
	// to fill the gap created by moving keys[idx] to C[idx] 
	for (i=idx+1; i<btn->n; ++i) 
		btn->keys[i-1] = btn->keys[i]; 

	// Moving the child pointers after (idx+1) in the current node one 
	// step before 
	for (i=idx+2; i<=btn->n; ++i) 
		btn->C[i-1] = btn->C[i]; 

	// Updating the key count of child and the current node 
	child->n += sibling->n+1; 
	btn->n--; 

	// Freeing the memory occupied by sibling 
	free(sibling); 
	return; 
} 

// The main function that inserts a new key in this B-Tree 
void insertBTree(struct BTree *btree, int k) 
{ 
	// If tree is empty 
	if (btree->root == NULL) 
	{ 
		// Allocate memory for root 
		btree->root = newBTreeNode(btree->t, true); 
		btree->root->keys[0] = k; // Insert key 
		btree->root->n = 1; // Update number of keys in root 
	} 
	else // If tree is not empty 
	{ 
		// If root is full, then tree grows in height 
		if (btree->root->n == 2*btree->t-1) 
		{ 
			// Allocate memory for new root 
			struct BTreeNode *s = newBTreeNode(btree->t, false); 

			// Make old root as child of new root 
			s->C[0] = btree->root; 

			// Split the old root and move 1 key to the new root 
			splitChildBTreeNode(s, 0, btree->root); 

			// New root has two children now. Decide which of the 
			// two children is going to have new key 
			int i = 0; 
			if (s->keys[0] < k) 
				i++; 
		    insertNonFullBTreeNode(s->C[i], k); 

			// Change root 
			btree->root = s; 
		} 
		else // If root is not full, call insertNonFull for root 
			insertNonFullBTreeNode(btree->root, k); 
	} 
} 

// A utility function to insert a new key in this node 
// The assumption is, the node must be non-full when this 
// function is called 
void insertNonFullBTreeNode(struct BTreeNode *btn, int k) 
{ 
	// Initialize index as index of rightmost element 
	int i = btn->n-1; 

	// If this is a leaf node 
	if ( btn->leaf == true) 
	{ 
		// The following loop does two things 
		// a) Finds the location of new key to be inserted 
		// b) Moves all greater keys to one place ahead 
		while (i >= 0 &&  btn->keys[i] > k) 
		{ 
			btn->keys[i+1] = btn->keys[i]; 
			i--; 
		} 

		// Insert the new key at found location 
		btn->keys[i+1] = k; 
		btn->n = btn->n+1; 
	} 
	else // If this node is not leaf 
	{ 
		// Find the child which is going to have the new key 
		while (i >= 0 && btn->keys[i] > k) 
			i--; 

		// See if the found child is full 
		if (btn->C[i+1]->n == 2*btn->t-1) 
		{ 
			// If the child is full, then split it 
			splitChildBTreeNode(btn, i+1, btn->C[i+1]); 

			// After split, the middle key of C[i] goes up and 
			// C[i] is splitted into two. See which of the two 
			// is going to have the new key 
			if (btn->keys[i+1] < k) 
				i++; 
		} 
		insertNonFullBTreeNode(btn->C[i+1], k); 
	} 
} 

// A utility function to split the child y of this node 
// Note that y must be full when this function is called 
void splitChildBTreeNode(struct BTreeNode *btn, int i, struct BTreeNode *y) 
{ 
	int j;
	// Create a new node which is going to store (t-1) keys 
	// of y 
	struct BTreeNode *z = newBTreeNode(y->t, y->leaf); 
	z->n = btn->t - 1; 

	// Copy the last (t-1) keys of y to z 
	for (j = 0; j < btn->t-1; j++) 
		z->keys[j] = y->keys[j+btn->t]; 

	// Copy the last t children of y to z 
	if (y->leaf == false) 
	{ 
		for (j = 0; j < btn->t; j++) 
			z->C[j] = y->C[j+btn->t]; 
	} 

	// Reduce the number of keys in y 
	y->n = btn->t - 1; 

	// Since this node is going to have a new child, 
	// create space of new child 
	for (j = btn->n; j >= i+1; j--) 
		btn->C[j+1] = btn->C[j]; 

	// Link the new child to this node 
	btn->C[i+1] = z; 

	// A key of y will move to this node. Find location of 
	// new key and move all greater keys one space ahead 
	for (j = btn->n-1; j >= i; j--) 
		btn->keys[j+1] = btn->keys[j]; 

	// Copy the middle key of y to this node 
	btn->keys[i] = y->keys[btn->t-1]; 

	// Increment count of keys in this node 
	btn->n = btn->n + 1; 
} 

// Function to get height of the B-Tree traversing until the leaf node is found 
void getHeightBTreeNode(struct BTreeNode *btn, int height) 
{   
	int i; 
		
	// Print the subtree rooted with last child 
	if (btn->leaf == true)
		printf("%d ",height); 
	else
	{
		height = height + 1; 
		// There are n keys and n+1 children, traverse through n keys 
		// and first n children 
		for (i = 0; i <= btn->n; i++)
		{ 
			// traverse the subtree rooted with child C[i]. 
			if (btn->C[i] != NULL) 
			{	 
				getHeightBTreeNode(btn->C[i], height);
				break; 
			} 
		} 		
	}	
} 

// Get hight of BTree
void getHeightBTree( struct BTree *btree ) 
{   	
	if (btree->root != NULL) 
		getHeightBTreeNode(btree->root, 1);
	else
		printf("0");  
} 

// Function to traverse all nodes in a subtree rooted with this node 
void traverseBTreeNode(struct BTreeNode *btn) 
{ 
	// There are n keys and n+1 children, traverse through n keys 
	// and first n children 
	int i; 
	for (i = 0; i < btn->n; i++) 
	{ 
		// If this is not leaf, then before printing key[i], 
		// traverse the subtree rooted with child C[i]. 
		if (btn->leaf == false) 
			traverseBTreeNode(btn->C[i]); 
		printf("%d ",btn->keys[i]); 
	} 

	// Print the subtree rooted with last child 
	if (btn->leaf == false) 
		traverseBTreeNode(btn->C[i]); 
} 

// Function to search key k in subtree rooted with this node 
struct BTreeNode* searchBTreeNode(struct BTreeNode *btn, int k) 
{ 
	// Find the first key greater than or equal to k 
	int i = 0; 
	while (i < btn->n && k > btn->keys[i]) 
		i++; 

	// If the found key is equal to k, return this node 
	if (btn->keys[i] == k)  
		return btn; 

	// If key is not found here and this is a leaf node 
	if (btn->leaf == true) 
		return NULL; 

	// Go to the appropriate child 
	return searchBTreeNode(btn->C[i], k); 
} 

// Remove BTree
void removeBTree(struct BTree *btree, int k) 
{ 
	if (!btree->root) 
	{ 
		printf(" The tree is empty\n"); 
		return; 
	} 

	// Call the remove function for root  
	removeBTreeNode(btree->root,k); 

	// If the root node has 0 keys, make its first child as the new root 
	// if it has a child, otherwise set root as NULL 
	if (btree->root->n==0) 
	{ 
		struct BTreeNode *tmp = btree->root; 
		if (btree->root->leaf) 
			btree->root = NULL; 
		else
			btree->root = btree->root->C[0]; 

		// Free the old root 
		free(tmp); 
	} 
	return; 
} 

// Driver code - Main is the first function that gets executed
int main() 
{ 
    int choice,item,m;     	
    struct BTree* btree1;     
    
	printf("\n Enter Order of BTree: ");
	scanf("%d", &m);
	btree1 = newBTree(m);	
	
	do {
		do 
		{
			printf("\n\n\t 1. Insert an element into BTree  ");
			printf("\n\t 2. Delete an element from BTree ");
			printf("\n\t 3. Check If element is there in BTree");
			printf("\n\t 4. Display Height of the BTree");
			printf("\n\t 5. Print elements of the Btree"); 
			printf("\n\t 6. Exit ");
			printf("\n\t Enter choice: ");
			scanf(" %d",&choice);
			if(choice<1 || choice>6)
				printf("\n Invalid choice - try again");
		} while (choice<1 || choice>6);
		switch(choice) 
		{
			case 1:
				printf("\n Enter new element: ");
				scanf("%d", &item);
				insertBTree(btree1, item); 
				printf("\n Traversal of tree after Insert is: ");
				traverseBTree(btree1);    
				break;
			case 2:
				printf("\n Enter the element to be deleted : ");
				scanf(" %d",&item);
				removeBTree(btree1, item); 
				printf("\n Traversal of tree is: ");
				traverseBTree(btree1);  
				break;
			case 3: 
				printf("\n Enter element to Search: ");
				scanf("%d", &item); 
				struct BTreeNode* btn = searchBTree(btree1, item);
				if( btn != NULL )
			       printf("\n 1 - Found");
			    else
			       printf("\n 0 - Not found");
				break;
			case 4:
				printf("\n Height of the BTree : ");
				getHeightBTree(btree1);
				break;
			case 5:
				printf("\n Preorder traversal of Btree is : ");
				traverseBTree(btree1);  
				break; 
			default:
				printf("\n End of program ");
		} 
	} while(choice !=6);	
	
	//Free memory occupied by BTree node
	free(btree1);
	return 0;   
} 

