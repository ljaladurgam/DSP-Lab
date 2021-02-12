/* 
   Roll number: 20MCMB05
   Name: Lakshminarayana Jaladurgam
   C program to Implement Krushkal's Algorithm for finding the  Minimum Spanning 
   Tree  of a Graph. [Choose any weighted graph of your choice with minimum 6 
   Vertices and > 6 Edges ]
*/  
#include<stdio.h>
 
#define MAX 30

//Define structure for Edge
typedef struct edge
{
	int src,dest,weight;
}edge;
 
//Define structure for List of edges
typedef struct edgelist
{
	edge data[MAX];
	int n;
}edgelist;
 
//Declare global variables 
edgelist elist; 
int G[MAX][MAX],n;
edgelist spanlist;
 
//Declare functions
void kruskal();
int find(int belongs[],int vertexno);
void union1(int belongs[],int c1,int c2);
void sort();
void print();

// Driver code - Main is the first function that gets executed
void main()
{
	int i,j,total_cost; 
	
	printf("\nEnter Number of Vertices: ");	
	scanf("%d",&n);
	
	printf("\nEnter the Adjacency Matrix:\n");	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G[i][j]);
			
	kruskal();
	print();
}

//Function to perform Krushkal algorithm
void kruskal()
{
	int belongs[MAX],i,j,cno1,cno2;
	elist.n=0;
 
	for(i=1;i<n;i++)
		for(j=0;j<i;j++)
		{
			if(G[i][j]!=0)
			{
				elist.data[elist.n].src=i;
				elist.data[elist.n].dest=j;
				elist.data[elist.n].weight=G[i][j];
				elist.n++;
			}
		}
 
	sort();
	
	for(i=0;i<n;i++)
		belongs[i]=i;
	
	spanlist.n=0;
	
	for(i=0;i<elist.n;i++)
	{
		cno1=find(belongs,elist.data[i].src);
		cno2=find(belongs,elist.data[i].dest);
		
		if(cno1!=cno2)
		{
			spanlist.data[spanlist.n]=elist.data[i];
			spanlist.n=spanlist.n+1;
			union1(belongs,cno1,cno2);
		}
	}
}

//Function to find
int find(int belongs[],int vertexno)
{
	return(belongs[vertexno]);
}

//Function for Union
void union1(int belongs[],int c1,int c2)
{
	int i;
	
	for(i=0;i<n;i++)
		if(belongs[i]==c2)
			belongs[i]=c1;
}
 
//Function to sort the edges in the ascending order of weights
void sort()
{
	int i,j;
	edge temp;
	
	for(i=1;i<elist.n;i++)
		for(j=0;j<elist.n-1;j++)
			if(elist.data[j].weight>elist.data[j+1].weight)
			{
				temp=elist.data[j];
				elist.data[j]=elist.data[j+1];
				elist.data[j+1]=temp;
			}
}

//Function to print the Minimum spanning tree
void print()
{
	int i,cost=0;
	
	printf("\n\nThe Minimum Spanning Tree details:");
	printf("\n------------------------");
	printf("\nSource\t|Target\t|Weight");
	printf("\n------------------------");
	for(i=0;i<spanlist.n;i++)
	{
		printf("\n%d\t|%d\t|%d",spanlist.data[i].dest+1,spanlist.data[i].src+1,spanlist.data[i].weight);
		cost=cost+spanlist.data[i].weight;
	}	
	printf("\n------------------------");
	
	printf("\n\nCost of the Minimum Spanning Tree: %d",cost);
	
	printf("\n\nEdges of the Minimum Spanning Tree:");
	
	for(i=0;i<spanlist.n;i++)
	{
		printf("\nEdge %d: Between vertices %d and %d with weight %d",i+1,spanlist.data[i].dest+1,spanlist.data[i].src+1,spanlist.data[i].weight); 
	}
 
}


