#include <stdio.h>   
int stack[100],i,j,choice=0,n,top=-1;  
void push();  
void pop();  
void display();  
void main ()  
{  
      
    printf("Enter the maximum number of elements in the stack: ");   
    scanf("%d",&n);  
    printf("*********Implement Stack using Arrays [Push, Pop, Display]*********");  
  
printf("\n------------------------------------------------------------------------------\n");  
    while(choice != 4)  
    {  
        printf("\nChoose one of the options from below:\n");  
        printf("1.Push\n2.Pop\n3.Display\n4.Exit");  
        printf("\nEnter your choice: ");        
        scanf("%d",&choice);  
        switch(choice)  
        {  
            case 1:  
            {   
                push();  
                break;  
            }  
            case 2:  
            {  
                pop();  
                break;  
            }  
            case 3:  
            {  
                display();  
                break;  
            }  
            case 4:   
            {  
                printf("Exiting...");  
                break;   
            }  
            default:  
            {  
                printf("\nPlease Enter valid choice\n");  
            }   
        };  
    }  
}   
  
void push ()  
{  
    int val;      
    if (top == n - 1 )   
    printf("\nOverflow - Push can't be performed as stack is full\n");   
    else   
    {  
        printf("Enter the value:");  
        scanf("%d",&val);         
        top = top +1;   
        stack[top] = val;    
		printf("\nItem is pushed\n"); 
    }   
}   
  
void pop ()   
{   
    if(top == -1)   
    printf("\nUnderflow - Pop can't be performed as stack is empty\n");  
    else
	{    	
    	top = top -1; 
		printf("\nItem is popped\n"); 
	}    
}   
void display()  
{    
    if(top == -1)   
    {  
        printf("\nStack is empty\n");  
    }  
    else
	{
        printf("\nDisplaying Stack elements...\n"); 
	    for (i=top;i>=0;i--)  
	    {  
	        printf("%d\n",stack[i]);  
	    } 
	}
}
