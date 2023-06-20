#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "stackarr.h"


void initStack(Stack *list){
	list->top = -1;
}

bool isEmpty(Stack list){
	return list.top == -1;
}

bool isFull(Stack list){
	return list.top >=MAX - 1;
}

void push(Stack *list, Data item){
	if(!(isFull(*list))){
		list->elems[++(list->top)] = item;
	}
}

void pop(Stack *list){
	if(!(isEmpty(*list))){
		list->top--;
	}
}

Data peek(Stack list){
	return list.elems[list.top];
}

void display(Stack list){
	if(isEmpty(list)){
		return;
	}
	
	Stack temp;
	initStack(&temp);
	
	printf("Temp Stack (To check for errors)\n");
	while(!(isEmpty(list))){
		push(&temp, peek(list));
		printf("%d ", peek(temp));
		pop(&list);
	}
	
	printf("\nThe original Stack\n");
	while(!(isEmpty(temp))){
		printf("%d ", peek(temp));
		pop(&temp);
	}
	printf("\n");
}

void visualize(Stack list){
	if(isEmpty(list)){
		return;
	}
	
	int i;
		
	printf("Stack\n");
	for(i = 0; i <= list.top; i++){
		printf("%d ", list.elems[i]);
	}

	printf("\n");
}

