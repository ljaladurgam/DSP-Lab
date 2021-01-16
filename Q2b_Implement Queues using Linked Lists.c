#include<stdio.h>   
#include<stdlib.h>  
struct node   
{  
    int data;   
    struct node *next;  
};  
struct node *front;  
struct node *rear;   
void enqueue();  
void dequeue();  
void display();  
void main ()  
{  
    printf("\n***********Implement Queues using Linked Lists [Enqueue and Dequeue]***********"); 
	printf("\n------------------------------------------------------------------------------------"); 
    int choice;   
    while(choice != 4)   
    {     
        printf("\nChoose one of the options from below:\n");  
        printf("\n1.Enqueue \n2.Dequeue \n3.Display the Queue\n4.Exit\n");  
        printf("\nEnter your choice:");  
        scanf("%d",& choice);  
        switch(choice)  
        {  
            case 1:  
            enqueue();  
            break;  
            case 2:  
            dequeue();  
            break;  
            case 3:  
            display();  
            break;  
            case 4:  
            exit(0);  
            break;  
            default:   
            printf("\nEnter a valid choice");  
        }  
    }  
}  
void enqueue()  
{  
    struct node *ptr;  
    int item;   
      
    ptr = (struct node *) malloc (sizeof(struct node));  
    if(ptr == NULL)  
    {  
        printf("\nOverflow - Enqueue can't be performed as Queue is full\n");   
        return;  
    }  
    else  
    {   
        printf("\nEnter value:");  
        scanf("%d",&item);  
        ptr -> data = item;  
        if(front == NULL)  
        {  
            front = ptr;  
            rear = ptr;   
            front -> next = NULL;  
            rear -> next = NULL;  
        }  
        else   
        {  
            rear -> next = ptr;  
            rear = ptr;  
            rear->next = NULL;  
        }  
    	printf("\nElement is Enqueued \n");
    }  
}     
void dequeue()  
{  
    struct node *ptr;  
    if(front == NULL)  
    {  
        printf("\nUnderflow - Dequeue can't be performed as Queue is Empty\n");  
        return;  
    }  
    else   
    {  
        ptr = front;  
        front = front -> next;  
        free(ptr);  
    }  
    printf("\nElement is Dequeued \n ");  
}  
void display()  
{  
    struct node *ptr;  
    ptr = front;      
    if(front == NULL)  
    {  
        printf("\nQueue is Empty\n");  
    }  
    else  
    {   printf("\nDisplaying Queue Elements...\n");  
        while(ptr != NULL)   
        {  
            printf("\n%d\n",ptr -> data);  
            ptr = ptr -> next;  
        }  
    }  
}  
