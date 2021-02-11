// Program to convert Infix to Postfix with Stacks using Linked list
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

// Define structure for Node of the linked list
struct node
{
	char data;
	struct node *next;
}*top=NULL,*pstart=NULL;

// Function to Insert in postfix expression linked list  
void insert(char ch)
{
    struct node *t,*child;
    child=(struct node *)malloc(sizeof(struct node));
    child->next=NULL;
    child->data=ch;
    t=pstart;

    if(pstart==NULL)
    {
    	pstart=child;
    }
    else
    {
	    while(t->next!=NULL)
	    t=t->next;
	    t->next=child;
    } 
}

// Function for Push operation of stack using Linked list
void push (char symbol)
{
    struct node *p;
    p=(struct node *)malloc(sizeof(struct node));
    p->data=symbol;
    if(top==NULL)
    {
		top=p;
	    p->next=NULL;
    }
    else
    {
	    p->next=top;
	    top=p;
    }
}

// Function for Pop operation of stack using Linked list
char pop()
{
	struct node *x,*y;
	char k;
	if(top==NULL)
	{
	    printf("stack underflow\n");
	    return 0;	
	}
	else
	{
		x=top;
		top=top->next;
		k=x->data; 
		free(x);
		x=NULL;
		return k;
	}
}

int isValid(char s)
{
	if(s == '0' || s == '1' || 
	   s == '2' || s == '3' || 
	   s == '4' || s == '5' || 
	   s == '6' || s == '7' || 
	   s == '8' ||  
	   s == 'a' || s == 'b' || 	  
	   s == 'c' || s == 'd' || 	
	   s == 'e' || s == 'f' || 	
	   s == 'A' || s == 'B' || 	
	   s == 'D' || s == 'F' || 	 	
	   s == 'G' || s == 'H' ||  	 	
	   s == '+' || s == '-' || 	 	
	   s == '*' || s == '/' || 	 	
	   s == '^' || s == '%' || 
	   s == '9' )
	   return 1;
	else
		return 0;
}

// Function for Display operation of stack using Linked list
void displaypost()
{
    struct node *to;
    int k1=0,k2=0,i=0;
    char postfix[70];
    
    if(pstart==NULL)
	{
    	printf("Root is null");    	
	}
    else 
    {
    	to=pstart;
    	while(to!=NULL)
    	{	
    		if( (k1!=k2 || k2 == 0) && i != 0 )
			{   
        		//printf(" %c",to->data);
			    if( isValid( to->data ) )
			    {
        		    //printf(" %c",to->data);
        		    postfix[i] = ' ';
        		    i++;
        		    postfix[i] = to->data;
			    }
    		}
    		else
    		{
        		//printf("%c",to->data);
			    if( isValid( to->data ) )
			    {
        		    //printf("%c",to->data);
        		    postfix[i] = to->data;
			    }
			}			 
        	k1 = isdigit(to->data); 
        	to=to->next;    
        	if(to!=NULL)
        	{
        	    k2 = isdigit(to->data);
        	}     
			i++;   
    	}
        postfix[i] = '\0';
        printf("%s",postfix);
    }
    //printf("\n%d ", i);
}

// Function for checking precedence of operators
int precedence(char ch)
{
	if(ch=='^' || ch=='%')
		return (5);
	else if(ch=='*' || ch== '/')
		return (4);
	else if (ch== '+' || ch== '-')
		return (3);
	else
		return (2);
}


// Function to convert Infix to Postfix expression with stacks using linked list
void intopost(char infix[])
{
    int len;
    int index=0;
    char symbol,temp;
    len= strlen(infix);     
    while(len>index)
    {
        symbol=infix[index];
        switch(symbol)
        {
	        case '(':
	        	push(symbol);
	        break;	
	        case ')':
		        temp=pop();
		        while(temp!='(')
		        {
		        insert(temp);
		        temp=pop();
		        }
		        break;	
	        case '^':	
	        case '%':
	        case '+':
	        case '-':
	        case '*':
	        case '/':
		        if(top==NULL)
		        {
		            push(symbol); 
		        }
		        else
		        {
			        while(top!=NULL && (precedence(top->data)>=precedence(symbol)))
			        {
			            temp=pop();
			            insert(temp);		
			        }
			        push(symbol);		
		        }   
		        break;
	        case ' ':
		        break;
		    default:
	        	insert(symbol);
         }
         index=index+1;
    }
    while(top!=NULL)
    {
    	temp=pop();
    	insert(temp);
    }
    displaypost();
    return;
}

// Driver code - Main is the first function that gets executed
int main()
{
	char infix[50],infix2[50];
	char ch;
	
	//while
	//system("clear");
	//printf("enter infix expression: ");
	
	//gets(infix);  
	
	//scanf("%s", infix);    
	//************************************************************************** 
	int i,n,j;
	i = -1;
	while(ch!='\n')
	{	 
		scanf("%c", &ch);
		if(ch!='\n')
		{
			i++;
			infix[i] = ch;	
		}
	}
	n = i; 
	
	i = 0;j=0;
   	infix2[i]= '('; 
	while(j<=n)
	{   
		if(infix[j]!=' ')
		{			
   			infix2[i+1]=infix[j];  
			i++;
		}
   		j++;
	}
   	infix2[i+1]=')'; 
   	
   	//n = i+2;
    //printf("%d ", n);
   	//for(i=0;i<=n;i++)
	//{
   		//printf("\n %c ", infix2[i]);
	//}
	//return 0;
	//**************************************************************************
	
	intopost(infix2); 
	return 0;
}
