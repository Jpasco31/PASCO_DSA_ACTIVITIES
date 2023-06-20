#ifndef STACKARR_H
#define STACKARR_H


#include <stdbool.h>

#define MAX 20

typedef int Data;

typedef struct {
	Data elems[MAX];
	int top;
} Stack;

void initStack(Stack *list);		// set an empty stack
bool isEmpty(Stack list);			//check if stack is empty
bool isFull(Stack list);			//check if stack is full
void push(Stack *list, Data item);	//insert from the top
void pop(Stack *list);					//delete form the top
Data peek(Stack list);				//return the top
void display(Stack list);						// display the top
void visualize(Stack list);					//display the list

#include "stackarr.c"

#endif
