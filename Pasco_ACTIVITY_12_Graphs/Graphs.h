#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define MAX 26			//store in alphabetical 26 is size of alphabets	
#define SIZE 100

typedef char String[20];

typedef struct {		//edges
	String *edge;		//array of edges or connections of the vertex
	int count;			//count of current edges
	int max;			//maximum space of array
}Value;

typedef struct {		//Structure for the separation compenents of dictionary
	String vertex;		// the vertex
	Value value;		//Value - contains edges or connections
}Row;

typedef struct {		//Dictionary Strucutre
	Row data[MAX];
}Dictionary;

typedef struct{		//structure of the Stack use in DFS
	String data[SIZE];
	int top;
} Stack;

typedef struct {
	String data[SIZE];
	int front;
	int rear;
}Queue;

int hash(String value);		//hash function

Dictionary newDictionary();
void addVertex(Dictionary *L, String key);					//add a vertex or node
void addEdge(Dictionary *L, String vertex, String edge);	//add a connection between to edges - vertices must exist
bool locateKey(Dictionary* L, String key, int* loc);	//locate the index of that vertex if collision occured
bool isFullEdges(Value edges);		//check if array of connections are full
void increaseSpace(Value *vertex);	//realloc the array of connections for that vertex if full

//Free the malloc edges array
void freeEdges(Dictionary *L);
//delete edge function		
void removeEdge(Dictionary *L, String vertex, String edge);
// delete vertex function	- delete the vertex and the other connections of the vertex to other vertices 
void removeVertex(Dictionary *L, String vertex);
void deleteAt(Value *key, int loc);

void visualize(Dictionary L);

//DFS - STACK IMPLEMENTATIONS
void depthFirst(Dictionary L);
void bubbleSortEdgesDescending(String* edges, int count);
void initStack(Stack *list);
bool isEmptyStack(Stack list);
void push(Stack *list, String item);
void pop(Stack *list);

//BSF - QUEUE IMPLEMENTATIONS
void breadthFirst(Dictionary L);
void initQueue(Queue *q);
void enqueue(Queue *q, String item);
void dequeue(Queue *q);
bool isEmptyQueue(Queue q);
void bubbleSortEdgesAscending(String* edges, int count);

#include "Graphs.c"
#endif
