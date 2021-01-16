/*  Write a program that convert the infix Expression in to Postfix Expression and then
evaluate the postfix expression using stacks. [Note: There should be atleast one two digit
operand in the expression] */
#include <stdio.h> 
#include <string.h>  
#include <ctype.h> 
#include <stdlib.h> 

// Stack type 
struct Stack 
{ 
	int top; 
	unsigned capacity; 
	int* array; 
}; 

// Stack Operations 
struct Stack* createStack( unsigned capacity ) 
{ 
	struct Stack* stack = (struct Stack*) 
		malloc(sizeof(struct Stack)); 

	if (!stack) 
		return NULL; 

	stack->top = -1; 
	stack->capacity = capacity; 

	stack->array = (int*) malloc(stack->capacity * 
								sizeof(int)); 

	return stack; 
} 
int isEmpty(struct Stack* stack) 
{ 
	return stack->top == -1 ; 
} 
char peek(struct Stack* stack) 
{ 
	return stack->array[stack->top]; 
} 
char pop(struct Stack* stack) 
{ 
	if (!isEmpty(stack)) 
		return stack->array[stack->top--] ; 
	return '$'; 
} 
void push(struct Stack* stack, char op) 
{ 
	stack->array[++stack->top] = op; 
} 
 
int peek2(struct Stack* stack) 
{ 
    return stack->array[stack->top]; 
} 
  
int pop2(struct Stack* stack) 
{ 
    if (!isEmpty(stack)) 
        return stack->array[stack->top--] ; 
    return '$'; 
} 
  
void push2(struct Stack* stack,int op) 
{ 
    stack->array[++stack->top] = op; 
} 

/* A utility function to check if 
the given character is operand  */
int isOperand(char ch) 
{ 
	return (ch >= 'a' && ch <= 'z') || 
		(ch >= 'A' && ch <= 'Z'); 
} 

/* A utility function to return precedence of a given operator 
   Higher returned value means higher precedence  */
int Prec(char ch) 
{ 
	switch (ch) 
	{ 
	case '+': 
	case '-': 
		return 1; 

	case '*': 
	case '/': 
		return 2; 

	case '^': 
		return 3; 
	} 
	return -1; 
} 


 /* The main function that converts given infix 
    expression to postfix expression.  */
int infixToPostfix(char* exp) 
{ 
	int i, k; 

	// Create a stack of capacity 
	// equal to expression size 
	struct Stack* stack = createStack(strlen(exp)); 
	if(!stack) // See if stack was created successfully 
		return -1 ; 

	for (i = 0, k = -1; exp[i]; ++i) 
	{ 
		
		// If the scanned character is 
		// an operand, add it to output. 
		if (isOperand(exp[i])) 
			exp[++k] = exp[i]; 
		
		// If the scanned character is an 
		// ‘(‘, push it to the stack. 
		else if (exp[i] == '(') 
			push(stack, exp[i]); 
		
		// If the scanned character is an ‘)’, 
		// pop and output from the stack 
		// until an ‘(‘ is encountered. 
		else if (exp[i] == ')') 
		{ 
			while (!isEmpty(stack) && peek(stack) != '(') 
				exp[++k] = pop(stack); 
			if (!isEmpty(stack) && peek(stack) != '(') 
				return -1; // invalid expression			 
			else
				pop(stack); 
		} 
		else // an operator is encountered 
		{ 
			while (!isEmpty(stack) && 
				Prec(exp[i]) <= Prec(peek(stack))) 
				exp[++k] = pop(stack); 
			push(stack, exp[i]); 
		} 

	} 

	// pop all the operators from the stack 
	while (!isEmpty(stack)) 
		exp[++k] = pop(stack ); 

	exp[++k] = '\0'; 
	printf( "\nConverted Postfix expression: %s \n", exp ); 
    //printf ("\nEvaluation of Postfix expression: %d \n", evaluatePostfix(exp)); 
} 

 /* The main function that returns value  
 	of a given postfix expression  */
int evaluatePostfix(char* exp) 
{ 
    // Create a stack of capacity equal to expression size 
    struct Stack* stack = createStack(strlen(exp)); 
    int i; 
  
    // See if stack was created successfully 
    if (!stack) return -1; 
  
    // Scan all characters one by one 
    for (i = 0; exp[i]; ++i) 
    { 
        //if the character is blank space then continue 
        if(exp[i]==' ')continue; 
          
        // If the scanned character is an  
        // operand (number here),extract the full number 
        // Push it to the stack. 
        else if (isdigit(exp[i])) 
        { 
            int num=0; 
              
            //extract full number 
            while(isdigit(exp[i]))  
            { 
            num=num*10 + (int)(exp[i]-'0'); 
                i++; 
            } 
            i--; 
              
            //push the element in the stack 
            push2(stack,num); 
        } 
          
        // If the scanned character is an operator, pop two 
        // elements from stack apply the operator 
        else
        { 
            int val1 = pop2(stack); 
            int val2 = pop2(stack); 
              
            switch (exp[i]) 
            { 
            case '+': push2(stack, val2 + val1); break; 
            case '-': push2(stack, val2 - val1); break; 
            case '*': push2(stack, val2 * val1); break; 
            case '/': push2(stack, val2/val1); break; 
              
            } 
        } 
    } 
    return pop2(stack); 
} 

// Driver program to test above functions 
int main() 
{ 
    int ch;
  	printf("\n*********Convert Infix to Postfix Expression and Evaluate Postfix expression using stack*********");  
  	printf("\n----------------------------------------------------------------------------------------------------------\n");   
	char exp1[] = "a+b*c/d-f+a^E";  
    char exp2[] = "100 200 + 2 / 5 * 7 +"; 
    while (1)
    {
    	printf("\n1.Convert Infix to Postfix Expression");
    	printf("\n2.Evaluate Postfix expression"); 
    	printf("\n3.Exit");
        printf("\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
    		printf ("\nGiven Infix expression: %s \n", exp1); 
			infixToPostfix(exp1); 
            break;
        case 2:
    		printf ("\nGiven Postfix expression: %s \n", exp2); 
    		printf ("\nEvaluation of Postfix expression: %d \n", evaluatePostfix(exp2));  
            break;
        case 3:
            exit(0);
        default:
            printf("\nInvalid choice\n");
            exit(0);
        }
    }
     
	return 0; 
} 

