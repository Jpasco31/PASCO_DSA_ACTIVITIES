#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stacklink.h"

void initStack(Stack *list){    // set an empty stack
    *list = NULL;
}		
bool isEmpty(Stack list){   //check if stack is empty
    return list == NULL;
}			
bool isFull(Stack *list){   //check if stack is full
    Stack newNode = (NodeType*)malloc(sizeof(NodeType));
    if(newNode == NULL){
        return true;
    }
    newNode->next = *list;
    *list = newNode;
    return false;
}			
void push(Stack *list, Data item){  //insert from the top(aka front)
    if(isFull(&(*list))){
        return;
    }
    (*list)->data = item;
}	

void pop(Stack *list){      //delete form the top(aka front)
    Stack temp = *list;

    *list = (*list)->next;

    free(temp); 
}					
Data peek(Stack list){      //return the top
    return list->data;
}				
void display(Stack list){   // display the top
    if(isEmpty(list)){
        return;
    }

    Stack temp;
    initStack(&temp);

    printf("Original List\n");
    while(!(isEmpty(list))){
        push(&temp, peek(list));
        printf("%d ", peek(list));
        pop(&list);
    }

    printf("\nRestore the Stack (temp stack to oringal)\n");
    while(!(isEmpty(temp))){
        printf("%d ", peek(temp));
        push(&list, peek(temp));
        pop(&temp);
    }
    printf("\n");
}	    
					
void visualize(Stack list){     //display the list
    if(isEmpty(list)){
        return;
    }

    while(list != NULL){
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");
}

//Free linked list function
void freeStack(Stack list){
    if(isEmpty(list)){
        return;
    }

    Stack temp;

    while(list->next != NULL){
        temp = list;
        list = list->next;
        free(temp);
    }
}

