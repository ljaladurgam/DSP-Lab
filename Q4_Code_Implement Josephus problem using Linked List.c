/* Write a C program to Implement Josephus problem using Linked List */ 

/* The #include directive tells the C preprocessor to include the
   contents of the file specified in the input stream to the 
   compiler and then continue with the rest of the original file.
   Declare stdlib.h for using standard library functions
   Declare stdio.h for using standard input and output functions*/
#include <stdio.h>
#include <stdlib.h> 

// Define structure of Linked list node 
struct node
{
    int num;
    struct node *next;
};
 
// Declare functions to create, display, survivor  
void create(struct node **);
void display(struct node *);
int survivor(struct node **, int);
 
// Driver code: This is the first funciton which gets invoked and executed
int main()
{
    struct node *head = NULL;
    int survive, skip;
    
    //Create Head node
    create(&head);
    printf("The persons in circular list are:\n");
    display(head);
    printf("Enter the number of persons to be skipped: ");
    scanf("%d", &skip);
    survive = survivor(&head, skip);
    printf("The person number to survive is : %d\n", survive);
    free(head);
 
    return 0;
}

// Function to calcualte surviving person number 
int survivor(struct node **head, int k)
{
    struct node *p, *q;
    int i;
 
    q = p = *head;
    while (p->next != p)
    {
        for (i = 0; i < k - 1; i++)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        printf("Person number %d has been killed.\n", p->num);
        free(p);
        p = q->next;
    }
    *head = p;
 
    return (p->num);
}


// Function to create circulat linked list 
void create (struct node **head)
{
    struct node *temp, *rear;
    int a, ch;
 
    do
    {
        printf("Enter a Person number: ");
        scanf("%d", &a);
        temp = (struct node *)malloc(sizeof(struct node));
        temp->num = a;
        temp->next = NULL;
        if (*head == NULL)
        {
            *head = temp;
        }
        else
        {
            rear->next = temp;
        }
        rear = temp;
        printf("Do you want to add a Person by entering his number [1/0]? ");
        scanf("%d", &ch);
    } while (ch != 0);
    rear->next = *head;
}

// Function to display the ciruclar Linked List elements
void display(struct node *head)
{
    struct node *temp;
 
    temp = head;
    printf("%d   ", temp->num);
    temp = temp->next;
    while (head != temp)
    {
        printf("%d   ", temp->num);
        temp = temp->next;
    }
    printf("\n");
}
