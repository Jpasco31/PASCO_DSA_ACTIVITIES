#ifndef STACK_LINK_H
#define STACK_LINK_H

#include <stdbool.h>

typedef int Data;

typedef struct node {
	Data data;
	struct node *next;
} NodeType, *NodePtr, *Stack;


void initStack(Stack *list);		// set an empty stack
bool isEmpty(Stack list);			//check if stack is empty
bool isFull(Stack *list);			//check if stack is full
void push(Stack *list, Data item);	//insert from the top
void pop(Stack *list);					//delete form the top
Data peek(Stack list);				//return the top
void display(Stack list);				// display the top
void visualize(Stack list);			//display the list

void freeStack(Stack list);		//free linked list

// #include "stacklink.c"

#endif
