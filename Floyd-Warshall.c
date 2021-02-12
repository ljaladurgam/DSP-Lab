/* 
   Roll number: 20MCMB05
   Name: Lakshminarayana Jaladurgam
   C program to Implement Floyd-Warshall algorithm to find the 
   shortest path between Nodes. Output prints the adjMatrixacency 
   matrix with the shortest paths.
*/

#include <stdio.h>

//Define constants 
#define V 6
#define INF 999

//Declare functions
void printMatrix(int matrix[][V]);
void doFloydWarshall(int graph[][V]); 

// Function to perform floyd warshall algorithm
void doFloydWarshall(int graph[][V]) 
{	
	int matrix[V][V], i, j, k;

	//Initialize matrix wiht graph details 
  	for (i = 0; i < V; i++)
    	for (j = 0; j < V; j++)
      		matrix[i][j] = graph[i][j];

  	// Adding vertices individually
  	for (k = 0; k < V; k++) {
    	for (i = 0; i < V; i++) {
      		for (j = 0; j < V; j++) {
		        if (matrix[i][k] + matrix[k][j] < matrix[i][j])
		          	matrix[i][j] = matrix[i][k] + matrix[k][j]; 
      		}
    	}	 
	//printf("\n");   
  	//printMatrix(matrix);
  }
  printf("\nAdjancey matrix with shortest paths: \n\n");
  printMatrix(matrix);
}

//Function to print Adjacency Matrix
void printMatrix(int matrix[][V]) 
{
  	int p,q;
  	
  	for (p = 0; p < V; p++) {
    	for (q = 0; q < V; q++) {
      		if (matrix[p][q] == INF)
        	printf("%4s", "INF");
      	else
        	printf("%4d", matrix[p][q]);
    	}
    	printf("\n");
  	}
}

// Driver code - Main is the first function that gets executed
int main() {

  	int graph1[V][V] = 	{
//			    			v1,  v2,  v3,  v4,  v5,  v6 
			  			 {   0,   5,   6, INF, INF, INF }, //v1
			             {   5,   0,   8,   3,   4, INF }, //v2
			             {   6,   8,   0, INF,   6, INF }, //v3           
			             { INF,   3, INF,   0,   3,   7} , //v4            
			             { INF,   4,   6,   3,   0,   7 }, //v5            
			             { INF, INF, INF,   7,   7,   0 }  //v6             
			 			};

	/* Call function to perform Floyd Warshall algorithm and
	   Print the adjancy matrix with the shortest paths */
  	doFloydWarshall(graph1);
  	
  	return 1;
  
}
