/* 
	Roll number: 20MCMB05
	Name: Lakshminarayana Jaladurgam
	C program to Implement Breadth First Search Algorithm using Queues. 
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 40

// Define data structure for Queue
struct queue {
  int items[SIZE];
  int front;
  int rear;
};

// Declare funtions
struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);

//Define data structure for Vertex
struct node {
  int vertex;
  struct node* next;
};

struct node* createNode(int);

//Define data structure for Graph 
struct Graph {
  int numVertices;
  struct node** adjLists;
  int* visited;
};

// BFS algorithm
void bfs(struct Graph* graph, int startVertex) {
  struct queue* q = createQueue();

  graph->visited[startVertex] = 1;
  enqueue(q, startVertex);

  while (!isEmpty(q)) {
    int currentVertex = dequeue(q);
    printf("\nNode Visited: %d \t", currentVertex);
    printQueue(q);

    struct node* temp = graph->adjLists[currentVertex];

    while (temp) {
      int adjVertex = temp->vertex;

      if (graph->visited[adjVertex] == 0) {
        graph->visited[adjVertex] = 1;
        enqueue(q, adjVertex);
      }
      temp = temp->next;
    }
  }
}

// Creating a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Creating a graph
struct Graph* createGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));
  graph->visited = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }

  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int dest) {
  // Add edge from src to dest
  struct node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  // Add edge from dest to src
  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

// Create a queue
struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

// Check if the queue is empty
int isEmpty(struct queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

// Adding elements into queue
void enqueue(struct queue* q, int value) {
  if (q->rear == SIZE - 1)
    printf("\tQueue is Full");
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

// Removing elements from queue
int dequeue(struct queue* q) {
  int item;
  if (isEmpty(q)) {
    printf("\tQueue is empty");
    item = -1;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      printf("Resetting Queue ");
      q->front = q->rear = -1;
    }
  }
  return item;
}

// Print the queue
void printQueue(struct queue* q) {
  int i = q->front;

  if (isEmpty(q)) {
    printf("Queue is empty ");
  } else {
    printf("Queue Values: ");
    for (i = q->front; i < q->rear + 1; i++) {
      printf("%d ", q->items[i]);
    }
  }
}

// Driver code - Main is the first function that gets executed
int main() {
  //Create Grpah 1 
  struct Graph* graph1 = createGraph(5);
  addEdge(graph1, 0, 1); //Add edge between vertex 0 and 1
  addEdge(graph1, 0, 2); //Add edge between vertex 0 and 2
  addEdge(graph1, 0, 3); //Add edge between vertex 0 and 3
  addEdge(graph1, 1, 2); //Add edge between vertex 1 and 2
  addEdge(graph1, 2, 4); //Add edge between vertex 1 and 4
  
  printf("Breadth First Search Output for First Graph: \n");
  //Call funtion to perform Breadth First Search for Graph 1
  bfs(graph1, 0);
  
  //Create Graph 2
  struct Graph* graph2 = createGraph(6);
  addEdge(graph2, 1, 2); //Add edge between vertex 1 and 2
  addEdge(graph2, 1, 4); //Add edge between vertex 1 and 4
  addEdge(graph2, 2, 3); //Add edge between vertex 2 and 3
  addEdge(graph2, 2, 5); //Add edge between vertex 2 and 5
  addEdge(graph2, 5, 6); //Add edge between vertex 5 and 6

  printf("\n\nBreadth First Search Output for Second Graph: \n");
  //Call funtion to perform Breadth First Search for Graph 2
  bfs(graph2, 1);

  return 0;
}
