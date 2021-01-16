#include<stdio.h>   
#include<stdlib.h>  
#define maxsize 5  
void enqueue();  
void dequeue();  
void display();  
int front = -1, rear = -1;  
int queue[maxsize];  
void main()  
{  
    int choice;
	printf("\n********Implement Queues using Arrays [Enqueue and Dequeue]***********"); 
	printf("\n------------------------------------------------------------------------------"); 
    while(choice != 4)   
    {       
        printf("\nChoose one of the options from below:\n"); 
        printf("\n1.Enqueue \n2.Dequeue \n3.Display the Queue \n4.Exit\n");  
        printf("\nEnter your choice:");  
        scanf("%d",&choice);  
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
            printf("\nEnter a valid choice.");  
        }  
    }  
}  
void enqueue()  
{  
    int item;  
    printf("\nEnter the element:");  
    scanf("\n%d",&item);      
    if(rear == maxsize-1)  
    {  
        printf("\nOverflow - Enqueue can't be performed as Queue is full\n");  
        return;  
    }  
    if(front == -1 && rear == -1)  
    {  
        front = 0;  
        rear = 0;  
    }  
    else   
    {  
        rear = rear+1;  
    }  
    queue[rear] = item;  
    printf("\nElement is Enqueued \n");  
      
}  
void dequeue()  
{  
    int item;   
    if (front == -1 || front > rear)  
    {  
        printf("\nUnderflow - Dequeue can't be performed as Queue is Empty\n");  
        return;  
              
    }  
    else  
    {  
        item = queue[front];  
        if(front == rear)  
        {  
            front = -1;  
            rear = -1 ;  
        }  
        else   
        {  
            front = front + 1;  
        }  
        printf("\nElement is Dequeued \n");  
    }  
      
      
}  
      
void display()  
{  
    int i;  
    if(rear == -1)  
    {  
        printf("\nQueue is empty\n");  
    }  
    else  
    {   printf("\nDisplaying Queue elements...\n");  
        for(i=front;i<=rear;i++)  
        {  
            printf("\n%d\n",queue[i]);  
        }     
    }  
}  
