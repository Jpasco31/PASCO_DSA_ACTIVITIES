#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Graphs.h"
#include <stdbool.h>

int hash(String value){				//hash function
	int key = toupper(value[0]);
	return (key - 'A');
}

Dictionary newDictionary(){
	Dictionary newDic;
	
	int i;
	for(i = 0; i < MAX; i++){
		strcpy(newDic.data[i].vertex, "EMPTY");			//initialize all vertex to EMPTY
		newDic.data[i].value.edge = NULL;
	}
	
	return newDic;
}

void addVertex(Dictionary *L, String key){
	int loc = hash(key);
	
	int added = 0;
	int count = 0;
	while(added == 0 && count < MAX){
		if(strcmp(L->data[loc].vertex, "EMPTY") == 0 && count < MAX){
			strcpy(L->data[loc].vertex, key);
			L->data[loc].value.max = 2;
			L->data[loc].value.count = 0;
			L->data[loc].value.edge = malloc(sizeof(String) * L->data[loc].value.max);		//array of edges
			added = 1;
		} else {
			loc++;
			if(loc == MAX){		// Wrap around to the beginning of the array
				loc = 0;
			}
		}
		count++;
	}
	
}

void addEdge(Dictionary *L, String vertex, String edge){
	//vertex location
	int locVertex = hash(vertex);		//locate vertex 1

	bool foundVertex = true;				
	if(strcmp(L->data[locVertex].vertex, vertex) != 0){			// if collision occured for vertex
		foundVertex = locateKey(L, vertex, &locVertex);	
	}

	//search if edge exist and find its location
	int locEdge = hash(edge);								//locate vertex 2 AKA edge

	bool foundEdge = true;
	if(strcmp(L->data[locEdge].vertex, edge) != 0){			// if collision occured for edge 
		foundEdge = locateKey(L, edge, &locEdge);	
	}

	//add edge and connection
	if(foundVertex == true && foundEdge == true){
		if(isFullEdges(L->data[locVertex].value)){		//realloc vertex if full
			increaseSpace(&(L->data[locVertex].value));
		}
		strcpy(L->data[locVertex].value.edge[(L->data[locVertex].value.count)++], edge);	//add edge to the vertex
		if(isFullEdges(L->data[locEdge].value)){		//realloc edge if full
			increaseSpace(&(L->data[locEdge].value));
		}
		strcpy(L->data[locEdge].value.edge[(L->data[locEdge].value.count)++], vertex); 		//add vertex to the edge
	}
	
}

//function to locate the key if collision occured in the index
bool locateKey(Dictionary* L, String key, int* loc) {
    for (int count = 0; count < MAX; count++) {
        if (strcmp(L->data[*loc].vertex, key) == 0) {
            return true; // Key found
        } else {
            (*loc)++;
            if (*loc == MAX) {
                *loc = 0; // Wrap around to the beginning of the array
            }
        }
    }

    return false; // Key not found
}

bool isFullEdges(Value edges){		//check if array of edges is full
	if(edges.max == edges.count){		
		return true;
	}
	return false;
}

void increaseSpace(Value *vertex){		//realloc array of edges array
	vertex->max *= 2;
	vertex->edge = realloc(vertex->edge, sizeof(String) * vertex->max);
}

void visualize(Dictionary L){
	int i;
	printf("\n");
	for(i = 0; i < MAX; i++){
			printf("%s: [", L.data[i].vertex);
			int j;
		if(strcmp(L.data[i].vertex, "EMPTY") != 0 && strcmp(L.data[i].vertex, "DELETED") != 0){
			for(j = 0; j < L.data[i].value.count; j++){
				printf("%s", L.data[i].value.edge[j]);
				if(j != L.data[i].value.count - 1){
					printf(", ");
				}
			}
		}
		printf("]\n");
	}
}

void freeEdges(Dictionary *L){
	int i;
	for(i = 0; i < MAX; i++){
		if(strcmp(L->data[i].vertex, "EMPTY") != 0){
			free(L->data[i].value.edge);
		}
	}
}

//delete edge function		
void removeEdge(Dictionary *L, String vertex, String edge){
	//vertex location
	int locVertex = hash(vertex);			//locate vertex 1

	bool foundVertex = true;
	if(strcmp(L->data[locVertex].vertex, vertex) != 0){			// if collision occured for vertex
		foundVertex = locateKey(L, vertex, &locVertex);	
	}

	//search if edge exist and find its location	
	int locEdge = hash(edge);			//locate vertex 2 AKA edge

	bool foundEdge = true;
	if(strcmp(L->data[locEdge].vertex, edge) != 0){			// if collision occured for edge 
		foundEdge = locateKey(L, edge, &locEdge);	
	}

	//delete edge
	if(foundVertex == true && foundEdge == true){
		// locate the index of vertex2 in the vertex1 edge
		int edge1 = 0;
		while(strcmp(L->data[locVertex].value.edge[edge1], edge) != 0 && edge1 < L->data[locVertex].value.count){
			edge1++;
		}
		deleteAt(&(L->data[locVertex].value), edge1);		// delete at
		
		//locate the  index of vertex 1 in the vertex 2 edge
		int edge2 = 0;
		while(strcmp(L->data[locEdge].value.edge[edge2], vertex) != 0 && edge2 < L->data[locEdge].value.count){
			edge2++;
		}
		deleteAt(&(L->data[locEdge].value), edge2);			//delete at
	}
}
// delete vertex function	- delete the edge and the other connection in the other vertex
void removeVertex(Dictionary *L, String vertex){
	//locate the vertex
	int loc = hash(vertex);
	bool foundVertex = true;
	if(strcmp(L->data[loc].vertex, vertex) != 0){			// if collision occured for vertex
		foundVertex = locateKey(L, vertex, &loc);	
	}
	
	//if found
	if(foundVertex){
		//delete all the edges with the vertex
		int locVertex[L->data[loc].value.count];	//location of vertices that is connect to the vertex to be deleted
		int i;
		for(i = 0; i < L->data[loc].value.count; i++){
			locVertex[i] = hash(L->data[loc].value.edge[i]);			// store the indexes in the dictionary of vertices connected to the vertex
			if(strcmp(L->data[locVertex[i]].vertex, L->data[loc].value.edge[i]) != 0){			// if collision occured for edge 
				locateKey(L, L->data[loc].value.edge[i], &(locVertex[i]));		//update the locVertex to the correct location in the dictionary
			}
		}
		int j;
		for(j = 0; j < L->data[loc].value.count; j++){
			int edge = 0;		//index of the vertex 1 in the edge connection array of vertex 2 (vertex 2 is its connected vertices)
			while(strcmp(L->data[locVertex[j]].value.edge[edge], vertex) != 0 && edge < L->data[locVertex[j]].value.count){
				edge++;		//increment edge to locate its vertex
			} //if index is found
			deleteAt(&(L->data[locVertex[j]].value), edge);	//delete that index in the edge connect array of vertex 2
		}

		//delete vertex
		strcpy(L->data[loc].vertex, "DELETED"); 
		L->data[loc].value.count = 0;
		L->data[loc].value.max = 0;
		free(L->data[loc].value.edge);
	}
	
	
}

void deleteAt(Value *key, int loc){
	int i;
    for(i = loc; i < key->count - 1; i++){
        strcpy(key->edge[i], key->edge[i+1]);
    }

   	key->count--;
}

//depth first traversal
//if all neighbors are visited pop from stack if not visit the neighbog and push it in the stack, visit by ascending letter or number, find the smallest first 
void depthFirst(Dictionary L){

	printf("\nDEPTH FIRST\n");
	int i;
	int sVertex = 0;

	//loop to find the starting vertex which should be visited by ascending order - source node
	//find the index of the smallest vertex
	for(i = 1; i < MAX; i++){
		if(strcmp(L.data[i].vertex, "EMPTY") != 0 && strcmp(L.data[i].vertex, "DELETED") != 0 && strcmp(L.data[i].vertex, L.data[sVertex].vertex) < 0){
			sVertex = i;
		}
	}

	//visited list
	bool visited[MAX] = {false};

	Stack stackList;
	initStack(&stackList);
	// Visit DFSList;

	//starting vertex to the stack 
	push(&stackList, L.data[sVertex].vertex);	
	
	// determining the next vertex to visit
	while(!(isEmptyStack(stackList))){
		//locate the top of the stack in the dictionary
		int current = hash(stackList.data[stackList.top]);
		// if collision occured for vertex
		if(strcmp(L.data[current].vertex, stackList.data[stackList.top]) != 0){			
			locateKey(&L, stackList.data[stackList.top], &current);	
		}
		// pop the top of the stack
		pop(&stackList);
		if(!visited[current]){
			//print the top of the stack
			printf("%s\n", L.data[current].vertex);
			visited[current] = true;
			int j;
			// push neigbors of current to the stack
			if (L.data[current].value.edge != NULL) {	
				//update neighbors to descending order to get the desired sequence of depth first ascending order
				bubbleSortEdgesDescending(L.data[current].value.edge, L.data[current].value.count);
				for(j = 0; j < L.data[current].value.count; j++){
					int nLoc = hash(L.data[current].value.edge[j]);
					//if collision occured update the nLoc	
					if(strcmp(L.data[nLoc].vertex, L.data[current].value.edge[j]) != 0){		
						locateKey(&L, L.data[current].value.edge[j], &nLoc);	
					}
					if(!visited[nLoc]){		//add to stack all not visited neigbors
						push(&stackList, L.data[current].value.edge[j]);
					}
				}
			}
		}
	}
	printf("\n");
	
}

void bubbleSortEdgesDescending(String* edges, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(edges[j], edges[j + 1]) < 0) {
                // Swap the contents of the strings (char arrays)
                char temp[20];
                strcpy(temp, edges[j]);
                strcpy(edges[j], edges[j + 1]);
                strcpy(edges[j + 1], temp);
            }
        }
    }
}

void initStack(Stack *list){
	list->top = -1;
}

bool isEmptyStack(Stack list){
	return list.top == -1;
}

void push(Stack *list, String item){
	strcpy(list->data[++(list->top)], item);
}

void pop(Stack *list){
	if(!(isEmptyStack(*list))){
		list->top--;
	}
}

//Breath first traversal
void breadthFirst(Dictionary L){
	printf("\nBREADTH FIRST\n");
	int i;
	int sVertex = 0;

	//loop to find the starting vertex which should be visited by ascending order - source node
	//find the index of the smallest vertex
	for(i = 1; i < MAX; i++){
		if(strcmp(L.data[i].vertex, "EMPTY") != 0 && strcmp(L.data[i].vertex, "DELETED") != 0 && strcmp(L.data[i].vertex, L.data[sVertex].vertex) < 0){
			sVertex = i;
		}
	}

	//visited list
	bool visited[MAX] = {false};

	Queue qList;
	initQueue(&qList);

	enqueue(&qList, L.data[sVertex].vertex);	
	
	// determining the next vertex to visit
	while(!(isEmptyQueue(qList))){
		//locate the top of the stack in the dictionary
		int current = hash(qList.data[qList.front]);
		// if collision occured for vertex
		if(strcmp(L.data[current].vertex, qList.data[qList.front]) != 0){			
			locateKey(&L, qList.data[qList.front], &current);	
		}
		// pop the top of the stack
		dequeue(&qList);
		if(!visited[current]){
			//print the top of the stack
			printf("%s\n", L.data[current].vertex);
			visited[current] = true;
			int j;
			// push neigbors of current to the stack
			if (L.data[current].value.edge != NULL) {	
				//update neighbors to ascending order to get the desired sequence of breadth first ascending order
				bubbleSortEdgesAscending(L.data[current].value.edge, L.data[current].value.count);
				for(j = 0; j < L.data[current].value.count; j++){
					int nLoc = hash(L.data[current].value.edge[j]);
					//if collision occured update the nLoc	
					if(strcmp(L.data[nLoc].vertex, L.data[current].value.edge[j]) != 0){			
						locateKey(&L, L.data[current].value.edge[j], &nLoc);	
					}
					if(!visited[nLoc]){		//add to queue all not visited neigbors
						enqueue(&qList, L.data[current].value.edge[j]);
					}
				}
			}
		}
	}
	printf("\n");
}

void initQueue(Queue *q){
	q->front = 0;
	q->rear = SIZE - 1;
}

void enqueue(Queue *q, String item){
	q->rear = (q->rear + 1) % SIZE;
	strcpy(q->data[q->rear], item);
}

void dequeue(Queue *q){
	strcpy(q->data[q->front], "DELETED");
	q->front = (q->front + 1) % SIZE;
}

bool isEmptyQueue(Queue q){
	return (q.rear + 1) % SIZE == q.front;
}

void bubbleSortEdgesAscending(String* edges, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(edges[j], edges[j + 1]) > 0) {
                // Swap the contents of the strings (char arrays)
                char temp[20];
                strcpy(temp, edges[j]);
                strcpy(edges[j], edges[j + 1]);
                strcpy(edges[j + 1], temp);
            }
        }
    }
}