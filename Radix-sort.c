/* 
	Roll number: 20MCMB05
	Name: Lakshminarayana Jaladurgam
	Program to Implement a generic doubly linked list in C. Using the implemented 
	generic doubly linked list, implement Radix sorting technique to sort positive
	integer numbers. 
*/
   
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>


// Define the Node data structure
struct Node {
    int data;
    // Pointer to the previous node
    struct Node* prev;
    // Pointer to the next node
    struct Node* next;
};

// Define the List data structure
struct List { 
    // Pointer to the left and right children
    struct Node* dummy;
};

// Define the Radix data structure 
struct Radix { 
    // Pointer to the left and right children
    struct List* list;
};

// Funtion to check the valid character
int isValidChar(char s)
{
	if( s == '0' || s == '1' || 
	    s == '2' || s == '3' || 
	    s == '4' || s == '5' || 
	    s == '6' || s == '7' || 
	    s == '8' || 
	    s == ' ' || s == '\n' ||
	    s == '9' )
	   return 1;
	else
		return 0;
}

// Function to get the length of the number
int getNumLength(int n)
{	
	int length = 0;
	while(n!=0)  
   {  
       n=n/10;  
       length++;  
   }
   return length;
}

// Funtion to get the value at the given position in a number
int valueAt(int num, int n)
{	
	int r; 
    r = num / pow(10, n); 
    r = r % 10; 
    return r;
}

// Function to insert the data
void insertData(struct List* list, int d)
{
	struct Node* temp_node = list->dummy;
    struct Node* new_node = (struct Node *) malloc( sizeof(struct Node) );
    struct Node* prev_node = (struct Node *) malloc( sizeof(struct Node) );
    struct Node* next_node = (struct Node *) malloc( sizeof(struct Node) );
		
	if(temp_node->next == NULL)
	{ 
    	new_node->data = d; 
		temp_node->next = new_node;
		temp_node->prev = NULL; 
	}
	else
	{
		prev_node = temp_node;
		next_node = temp_node->next;
		while(next_node != NULL)
		{
			if(next_node->data <= d)
			{
				prev_node = next_node;
				next_node = next_node->next;
			}
			else
			{
				break;
			}
		} 
    	new_node->data = d; 
		prev_node->next = new_node; 
		new_node->next = next_node;
		new_node->prev = prev_node;
		if(next_node != NULL)
		    next_node->prev = new_node;
	}
}

struct Node* deleteNode(struct List* list, int d)
{
    struct Node* prev_node = (struct Node *) malloc( sizeof(struct Node) );
    struct Node* next_node = (struct Node *) malloc( sizeof(struct Node) );
     
    struct Node* temp_del = (struct Node *) malloc( sizeof(struct Node) );
    temp_del = list->dummy;
    
	if(temp_del->next == NULL)
	{
		return NULL;
	}
	else
	{
		prev_node = temp_del;
		next_node = temp_del->next;
		while(next_node != NULL)
		{
			if(next_node->data == d)
			{
				temp_del = next_node; 
				prev_node->next = next_node->next;
				next_node->prev = prev_node;
				temp_del->prev = NULL;
				temp_del->next = NULL;
				return prev_node->next;
			}
			else if(next_node->data < d)
			{
				prev_node = next_node;
				next_node = next_node->next;
			}
			else
			{
				break;
			}
		}
	}
	return NULL;
}

//print a given list
void printList(struct List* list)
{ 
    struct Node* print_node = (struct Node *) malloc( sizeof(struct Node) );
    
    print_node = list->dummy->next;
    
	while(print_node != NULL)
	{ 
		printf("%d ",print_node->data);
		print_node = print_node->next;
	} 
	//printf("\n");
}


void radixSort(int d[], struct Radix* r[], int maxL,int n)
{
	int coveredL = 0,j,totalL,p,data,i;
    int output[50],l=1,x=0; 	
	int rLength = 10;
	struct Node* temp;
	int s;
	
	for(j=1; j<=n; j++)
	{
		if(d[j] < 0)
		{			 
			totalL  = getNumLength(d[j])-2;
			if(coveredL <= totalL)
			{ 
				s = valueAt(d[j],totalL - coveredL + 1);
				insertData(r[s]->list,d[j]);
			}
			else
			{ 
				insertData(r[0]->list,d[j]);
			}
		}
		else
		{
			totalL  = getNumLength(d[j])-1;
			if(coveredL <= totalL)
			{ 
				s = valueAt(d[j],totalL - coveredL);
				insertData(r[s]->list,d[j]);
			}
			else
			{ 
				insertData(r[0]->list,d[j]);
			}
		}
	}//end of for loop
	 
	/*for( p=0; p<rLength; p++)
	{
		printf("Printing List %d :",p); 
		printList(r[p]->list);
	} 
	printf("\n"); */
	coveredL++;
	
	
	while(coveredL <= maxL)
	{
		for(i=0; i<rLength; i++)
		{
			temp = r[i]->list->dummy->next;
			while(temp != NULL)
			{
				data = temp->data;
				if(data < 0)
				{
					totalL = getNumLength(data)-2;
					if(coveredL <= totalL)
					{
						s = valueAt(data,totalL - coveredL + 1);
						if(i != s)
						{
							temp = deleteNode(r[i]->list,data);
							insertData(r[s]->list,data);
						}
						else
						{
							temp = temp->next;
						}
					}
					else
					{
						if(i != 0)
						{
							temp = deleteNode(r[i]->list,data);
							insertData(r[0]->list,data);
						}
						else
						{
							temp = temp->next;
						}
					}
				}
				else
				{
					totalL = getNumLength(data)-1;
					if(coveredL <= totalL)
					{
						s = valueAt(data,totalL - coveredL);
						if(i != s)
						{
							temp = deleteNode(r[i]->list,data);							
							insertData(r[s]->list,data);
						}
						else
						{
							temp = temp->next;
						}
					}
					else
					{
						if(i != 0)
						{
							temp = deleteNode(r[i]->list,data);							
							insertData(r[0]->list,data);
						}
						else
						{
							temp = temp->next;
						}
					}
				}
			}//while interior
		}//for loop
		 
		/*for( p=0; p<rLength; p++)
		{ 
			printf("Printing List %d :",p); 
			printList(r[p]->list);
		} 
		printf("\n");*/
		coveredL++;
	}//while loop
	
	/*for( p=0; p<rLength; p++)
	{
        struct Node* print_node = (struct Node *) malloc( sizeof(struct Node) );
        print_node = r[p]->list->dummy->next;
    	while(print_node != NULL)
    	{ 
    		output[l] = print_node->data;
    		l++;
    		print_node = print_node->next;
    	}
    }
    
    for(l=1;l<=n;l++)
	{ 
		if(d[l]!=output[l])
		{
		    x = 1;
		    break;
		}
	}  
	
	if(x==0)
	{
	    printf("INVALID INPUT"); 
	}
	else
	{
	    for( p=0; p<rLength; p++)
	    {
	        printList(r[p]->list);
	    } 
	}*/
	for( p=0; p<rLength; p++)
    {
        printList(r[p]->list);
    } 
}

// Driver code - Main is the first function that gets executed
int main() 
{
	
    struct Node* node; 
    struct List* list; 
    struct Radix* radixDLL; 
    struct Radix* radix[10];
	int input[50]; 	
	int i=1,n,k,x,maxLength,count;
	char val = ' ';
		
	scanf("%d", &count);	
	if(count<=0)
	{
		printf("INVALID INPUT");
		return 0;
	}
	
	while(val!='\n')
	{	 
		scanf("%c", &val);
		if(isValidChar(val)==0)
		{
			printf("INVALID INPUT");
			return 0;
		}
		if(val!='\n'&& val!=' ')
		{
			
			k = val - '0';
			if(x==1)
			{	 
				i--; 
				input[i] = input[i] * 10 + k; 
			}
			else
			{	
				input[i] = k; 
			} 	
			if(input[i]<0)
			{
				printf("INVALID INPUT");
				return 0;
			}
			i++; 
		}
		if( val== ' ')
			x = 0;
		else
			x = 1;
	}
	n = i-1;
	 
	/*//printf("\n%d\n",n);	
	for(i=1;i<=n;i++)
	{
		printf("\nvalue=%d,I= %d",input[i],i);
		printf("%d ",input[i]);
	} */
	
	maxLength = 0;
	//Calculate maximum length considering all data
	for( i=1; i<=n; i++)
	{	
		k = getNumLength(input[i]); 
		if(maxLength < k)
		{
			maxLength = k;			
		}			
	}	  
    
    for(i=0;i<10;i++)
	{
		node = (struct Node *) malloc( sizeof(struct Node) );
		list = (struct List *) malloc( sizeof(struct List) );
		radixDLL = (struct Radix *) malloc( sizeof(struct Radix) );
		node->next = NULL; 
		node->prev = NULL; 
    	list->dummy = node;
    	radixDLL->list = list;     
		radix[i] = radixDLL;
	}
	
	//Call function to do Radix sort 
    radixSort(input,radix,maxLength,n); 
	
	return 0;
	
}
