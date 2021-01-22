/* 
	Roll number: 20MCMB05
	Name: Lakshminarayana Jaladurgam
	C program to Implement Depth First Search Algorithm using Stacks. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20

struct Vertex {
   char label;
   bool visited;
};

//stack variables
int stack[MAX]; 
int top = -1; 

void addVertex( char );   // 0

//graph variables

//array of vertices
struct Vertex* lstVertices[MAX];

//adjacency matrix
int adjMatrix[MAX][MAX];

//vertex count
int vertexCount = 0;

//stack functions

// Stack funtion - Push item
void push(int item) { 
   stack[++top] = item; 
} 

// Stack funtion - Push Pop
int pop() { 
   return stack[top--]; 
} 

// Stack funtion - Push Peek
int peek() {
   return stack[top];
}

// Stack funtion - Stack empty
bool isStackEmpty() {
   return top == -1;
}

//graph functions

//Add vertex to the vertex list
void addVertex(char label) {
   struct Vertex* vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
   vertex->label = label;  
   vertex->visited = false;     
   lstVertices[vertexCount++] = vertex;
}

//add edge to edge array
void addEdge(int start,int end) {
   adjMatrix[start][end] = 1;
   adjMatrix[end][start] = 1;
}

void displayStack( ){
	int i;	
   	printf("\tStack Values: ");
	for(i=0;i<=top;i++)
   		printf("%c ",lstVertices[stack[i]]->label );
			
}

//Display the vertex
void displayVertex(int vertexIndex) {
   printf("\nNode Visited: %c ",lstVertices[vertexIndex]->label);
   displayStack( );
}       

//Get the adjacent unvisited vertex
int getAdjUnvisitedVertex(int vertexIndex) {
   int i;

   for(i = 0; i < vertexCount; i++) {
      if(adjMatrix[vertexIndex][i] == 1 && lstVertices[i]->visited == false) {
         return i;
      }
   }

   return -1;
}

//Funtion for Depth First Search 
void depthFirstSearch() {
   int i;

   //mark first node as visited
   lstVertices[0]->visited = true;

   //push vertex index in stack
   push(0);

   //display the vertex
   displayVertex(0);   

   while(!isStackEmpty()) {
      //get the unvisited vertex of vertex which is at top of the stack
      int unvisitedVertex = getAdjUnvisitedVertex(peek());

      //no adjacent vertex found
      if(unvisitedVertex == -1) {
        pop();
      } else {
	    lstVertices[unvisitedVertex]->visited = true;
	    push(unvisitedVertex);
	    displayVertex(unvisitedVertex);
      }
   }

   //stack is empty, search is complete, reset the visited flag        
   for(i = 0;i < vertexCount;i++) {
      lstVertices[i]->visited = false;
   }        
}

// Driver code - Main is the first function that gets executed
int main() 
{
   int i, j; 

   for(i = 0; i < MAX; i++)    // set adjacency 
   {
      for(j = 0; j < MAX; j++) // matrix to 0
        adjMatrix[i][j] = 0;
   }
   
   addVertex('0');   // Node 0
   addVertex('1');   // Node 1
   addVertex('2');   // Node 2
   addVertex('3');   // Node 3
   addVertex('4');   // Node 4

   addEdge(0, 1);    // Edge 0 - 1
   addEdge(0, 2);    // Edge 0 - 2
   addEdge(0, 3);    // Edge 0 - 3
   addEdge(1, 2);    // Edge 1 - 2
   addEdge(2, 4);    // Edge 2 - 4  

   printf("Depth First Search Output for First Graph: \n ");
   depthFirstSearch(); 
    
   top = -1; vertexCount = 0;
   for(i = 0; i < MAX; i++)    // set adjacency 
   {
      for(j = 0; j < MAX; j++) // matrix to 0
         adjMatrix[i][j] = 0;
   }
        
   addVertex('1');   // Node 1
   addVertex('2');   // Node 2
   addVertex('3');   // Node 3
   addVertex('4');   // Node 4
   addVertex('5');   // Node 5
   addVertex('6');   // Node 6

   addEdge(0, 1);    // Edge 1 - 2
   addEdge(0, 3);    // Edge 1 - 4
   addEdge(1, 2);    // Edge 2 - 3
   addEdge(1, 4);    // Edge 2 - 5
   addEdge(4, 5);    // Edge 5 - 6   

   printf("\n\nDepth First Search Output for Second Graph: \n ");
   depthFirstSearch(); 

   return 0;   
}
