/* 
   Roll number: 20MCMB05
   Name: Lakshminarayana Jaladurgam
   C program to compute number of connected components of an undirected graph
   using Adjacency list. The input graph file name will be provided as a 
   command line argument.
*/  

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	int vertex;
	struct node* next;
};
struct node* createNode(int);

struct Graph {
	int numVertices;
	struct node** adjLists;
};

// Create a node
struct node* createNode(int vertex) {
	struct node* newNode = malloc(sizeof(struct node));
	newNode->vertex = vertex;
	newNode->next = NULL;
	return newNode;
}

// Create a graph
struct Graph* createAGraph(int numVertices) 
{
	int i;
	
	struct Graph* graph = malloc(sizeof(struct Graph));
	graph->numVertices = numVertices;
	
	graph->adjLists = malloc(numVertices * sizeof(struct node*));
	
	for (i = 0; i < numVertices; i++)
		graph->adjLists[i] = NULL;
	
	return graph;
}

// Add edge
void addEdge(struct Graph* graph, int source, int target) 
{
	// Add edge from source to target
	struct node* newNode = createNode(target);
	newNode->next = graph->adjLists[source];
	graph->adjLists[source] = newNode;
	
	// Add edge from target to source
	newNode = createNode(source);
	newNode->next = graph->adjLists[target];
	graph->adjLists[target] = newNode;
}

// Print the graph
void printGraph(struct Graph* graph) 
{
	int v;
	 
	for (v = 0; v < graph->numVertices; v++) 
	{
		struct node* temp = graph->adjLists[v];
		printf("\nVertex %d : ", v+1);
		while (temp) 
		{
			printf("%d -> ", temp->vertex+1);
			temp = temp->next;
		} 
	}
}

void DFSUtil(int vertex, bool visited[], struct Graph* graph)
{ 
	// Mark the current node as visited and print it
    visited[vertex] = true; 
	printf("%d ",vertex+1);
	
	struct node* temp = graph->adjLists[vertex]; 
	while (temp) 
	{ 	
		// Recur for all the vertices adjacent to this vertex
		if (!visited[temp->vertex])
			DFSUtil(temp->vertex, visited, graph);
		temp = temp->next;
	} 
}

void getConnectedComponents(struct Graph* graph)
{
	int v,comps = 1;
    bool visited[graph->numVertices]; 
    
	// Mark all the vertices as not visited 
    for (v = 0; v < graph->numVertices; v++)
    	visited[v] = false;
 
    for ( v = 0; v < graph->numVertices; v++) {
    	if (visited[v] == false) 
		{
            // print all reachable vertices from v
			printf("\nComponent: %d Vertices: ",comps);
            DFSUtil(v, visited, graph); 
			//printf("Component: %d \n",comps++);
			comps++;
        }
    }
    
	comps--;   
    printf("\n\nNumber of connected Components = %d\n", comps);

    if(comps == 1)
        printf("\nThe given graph is a Connected Graph\n");
    else
        printf("\nThe given graph is NOT a Connected Graph\n");

}


// Driver code - Main is the first function that gets executed
int main(int argc, char *fpath[])
{
	int n,maxedges,i,source,target;
	
    //Print Input file path received through command line arguments
	printf("\nInput file path provided: %s\n",fpath[1]);
    
	// Open Input file in read only mode and assign to file pointer variable
	FILE *fp1 = fopen(fpath[1], "r"); 
	
	//Validate that file is opened successfully
	if (fp1 == NULL) 
	{ 	
		//Display the user regarding the file opening error.
		printf("\nError : File is not opened\n"); 
		exit(0); 
	} 
	
    //Read number of vertices and edges from the input file
    fscanf(fp1, "%d %d", &n,&maxedges); 
    printf("\nNumber of vertices read from file : %d ",n); 
    printf("\nNumber of edges read from file : %d",maxedges); 
    
    //Validate number of possible edges
    if(maxedges > n*(n-1)/2)
    {   
		printf("\nInvalid number of edges");
    	return 0;
	}
	
	//Create graph by providing number of vertices
	struct Graph* graph = createAGraph(n);
	
	for(i=1;i<=maxedges;i++)
    {
    	//Read edges from input file
  		fscanf(fp1, "%d %d", &source, &target); 
        printf("\nEdge %d read from file between vertices: %d and %d",i,source,target); 
        source = source - 1;
        target = target -1 ;

        if((source == -1) && (target == -1))
            break;

        if( source >= n || target >= n || source<0 || target<0)
        {
            printf("\nInvalid edge\n");
            i--;
        }
        else
        { 
        	//Add Edge 
            addEdge(graph, source, target);
        }
    }
	
	//Print Graph
	printf("\n\nBelow is the Adjacency List representation of given Undirected Graph:");
	printGraph(graph);
	
	printf("\n\nList of Connected components:\n");
	//Get Connected Components for the given graph 
	getConnectedComponents(graph);
	
	/* Close the input file: If the file is not closed, the memory allocated to the file pointer 
	vertariable will not be cleared until the program execution is completed. It is good 
	practice to close the files programatically always.*/
	fclose(fp1); 
	
	return 0;
} 

