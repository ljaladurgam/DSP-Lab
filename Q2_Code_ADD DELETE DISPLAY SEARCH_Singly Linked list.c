/* Write a C program to ADD, DELETE, DISPLAY and SEARCH elements 
   in a Singly Linked List */ 

/* The #include directive tells the C preprocessor to include the
   contents of the file specified in the input stream to the 
   compiler and then continue with the rest of the original file.
   Declare stdlib.h for using standard library functions
   Declare stdio.h for using standard input and output functions*/  
#include<stdlib.h>
#include <stdio.h>

// Declare functions to Add, Delete, Display and Search
void add();
void display();
void delete();
void search(); 


/* Define node for linked list with variables to hold the
   the value of the current element and pointer reference 
   to next element.*/ 
struct node
{
    int info;
    struct node *next;
};
struct node *start=NULL;


// Driver code: This is the first funciton which gets invoked and executed
int main()     
{
	//Declare local variables 
    int choice;
    while(1){
        
        //Show the menu options to the user to perform differnet operations on Singly linked list
        printf("\n----------------------------------------------------------------------------------------------");
        printf("\n**************ADD, DELETE, DISPLAY and SEARCH elements in a Singly Linked List****************");
        printf("\n----------------------------------------------------------------------------------------------");
        printf("\n 1.ADD");
        printf("\n 2.DELETE");
        printf("\n 3.DISPLAY");
        printf("\n 4.SEARCH");
        printf("\n 5.EXIT\n"); 
        printf("\n Enter your choice:");
        //Take input for choice of operation of the user
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            	//Add element to the Singly Linked List
                add();
                break;
            case 2:
            	//Delete element from the Singly Linked List
                delete();
                break;
            case 3: 
            	//Display the elements of the Singly Linked List
                display(); 
                break;
            case 4:
            	//Search the element in the Singly Linked List
                search();
                break;
            case 5:
            	//Exit
                exit(0);                 
            default:
            	//Show the message as Invalid choice
                printf("\n Invalid Choice\n");
                break;
        }
    }
    return 0;
}

//Function to Add the element to the Singly Linked List
void add()
{
	//Declare local variables 
    struct node *temp,*ptr;
    temp=(struct node *)malloc(sizeof(struct node));
    
    if(temp==NULL)
    {
        printf("\n Out of Memory Space:\n");
        exit(0);
    }
    printf("\n Enter the data value for the node:\t");
    //Take input for the value to be added 
    scanf("%d",&temp->info);
    temp->next=NULL;
    if(start==NULL)
    {	
    	//If the list is empty, Add as first element
        start=temp;
    }
    else
    {
        ptr=start;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        //Add the element as last element
        ptr->next=temp;
    }
}

//Function to Display the elements of the Singly Linked List
void display()
{
	//Declare local variables 
    struct node *ptr;
    
    //Check if the Linked list is empty
    if(start==NULL)
    {
        printf("\nList is empty\n");
        return;
    }
    else
    {
        ptr=start;
        printf("\nThe List elements are:\n");
        while(ptr!=NULL)
        {
        	//Display the value element by element in the Linked list
            printf("%d\t",ptr->info );
            ptr=ptr->next ;
        }
    }
}

//Function to Delete the element from the Singly Linked List
void delete()
{
	//Declare local variables 
    int i,value,flag=-1;
    struct node *temp,*ptr;
    
    //Check if the Linked list is empty
    if(start==NULL)
    {
        printf("\nList is Empty\n");
        return;
    }
    else
    {
        printf("\nEnter the value of the node to be deleted:\t");
        //Take input for the value to be deleted
        scanf("%d",&value);
        
        ptr=start;
        while(ptr!=NULL)
        { 
            if(ptr->info==value){
            	//Display the message showing the element deleted
                printf("\nThe deleted element is:%d\t",ptr->info ); 
                temp->next =ptr->next ;
                free(ptr);
				flag = 1;  
				return; 							                     	
			}
            temp = ptr;
            ptr = temp->next ;
        }
    	if(flag==-1)
    	{   
    		//Display the message that value is not found in the list to delete
	        printf("\nThe value %d is not found in the list to delete\n", value);
	        return;
    	}            
    }
}

//Function to Search the given elements in the Singly Linked List
void search()
{
	//Declare local variables 
    int i,value,count;
    struct node *temp,*ptr;
    
    //Check if the Linked list is empty
    if(start==NULL)
    {
        printf("\nList is Empty\n");
        return;
    }
    else
    {
        printf("\nEnter the value of the node to search:\t");
        scanf("%d",&value);
        
        ptr=start; 
        count = 0;
        while(ptr!=NULL)
        {   
        	count++;
            if(ptr->info==value){
            	//Display the position of the value at it is found in the list
                printf("\nThe Value is found at position:%d\t", count); 
				return; 							                     	
			}
            ptr = ptr->next ;
        }
    	if(count==0)
    	{
    		//Display the message that value is not found  
	        printf("\nThe value %d is not found in the list\n", value);
	        return;
    	}
            
    }
}
