#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "act7Product.h"

//Product
Date ExpDate(int date, int month, int year){
	Date expDate;
	
	expDate.date = date;
	expDate.month = month - 1;
	expDate.year = year;
	
	return expDate;
}
Product newProduct(int prodID, String prodName, int prodQty, double prodPrice, Date prodExp){
	Product newProduct;
	
	newProduct.prodID = prodID;;
	strcpy(newProduct.prodName, prodName);
	newProduct.prodQty = prodQty;
	newProduct.prodPrice = prodPrice;
	newProduct.prodExp = prodExp;
	
	return newProduct;
}

Product inputProductInfo(){
	Product newProduct;
	
	printf("Enter a product ID: ");
	scanf("%d", &newProduct.prodID);

	printf("Enter a product NAME: ");
	scanf("%s", newProduct.prodName);

	fflush(stdin);

	printf("Enter a product QUANTITY: ");
	scanf("%d", &newProduct.prodQty);

	printf("Enter a product PRICE: ");
	scanf("%lf", &newProduct.prodPrice);

	printf("Enter a product EXPIRY DATE (mm dd yyyy): ");
	scanf("%d %d %d", &newProduct.prodExp.month,  &newProduct.prodExp.date,  &newProduct.prodExp.year);

	return newProduct;
}

// Virtual Space
VirtualSpace newVirtualSpace(){	//create a new Virtual Heap
	VirtualSpace vh;
    int i;
    Date expDate;
    for (i = 0; i < MAX; i++) {
        vh.data[i].items = newProduct(0, "", 0, 0, ExpDate(0, -1, 0));
        vh.data[i].link = i - 1;
    }
    vh.avail = MAX - 1;
    return vh;
}	

int allocSpace(VirtualSpace *vh){	//Allocate an available space in the virtual heap
	int retVal = vh->avail;
	
	if(retVal != -1){
		vh->avail = vh->data[vh->avail].link;
	}
	
	return retVal;
}	

void deallocSpace(VirtualSpace *vh, int index){	//deallocate space in the that Index
	if(index <= 1 || index >= MAX){
		return;
	}

	vh->data[index].link = vh->avail;
	vh->data[index].items = newProduct(0, "", 0, 0, ExpDate(0, -1, 0));
	vh->avail = index;

}	
bool isFull(VirtualSpace vh){		//check if virtual space is full
	if(vh.avail == -1){
		printf("\n\n VIRTUAL SPACE IS FULL\n\n");
		return true;
	}
	
	return false;
}	
//visualize
void visualizeSpace(VirtualSpace vh){	//print virtual space
	int i;
	String m[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}; // months

	SType data;
	printf("\n\nVISUALIZE VIRTUAL SPACE\n");
	printf("%-8s | %-8s | %-10s | %-25s | %-10s | %-10s | %-20s\n", "INDEX", "LINK", "PROD ID", "PROD NAME", "PROD QTY", "PROD PRICE", "PROD EXP");
	printf("-----------------------------------------------------------------------------------------------------------\n");
	for(i = 0; i < MAX; i++){
		data = vh.data[i];
		if(data.items.prodID != 0){
			printf("%-8d | %-8d | %-10d | %-25s | %-10d | %-10.2f | %8s %02d, %-4d\n", i, data.link, data.items.prodID, data.items.prodName, data.items.prodQty, data.items.prodPrice, m[data.items.prodExp.month], data.items.prodExp.date, data.items.prodExp.year);
		} else {
			printf("%-8d | %-8d | %-10s | %-25s | %-10s | %-10.2s | %-20s\n", i, data.link, "EMPTY", "","" ,"" ,"");
		}
	}
	printf("-----------------------------------------------------------------------------------------------------------\n");
	printf("AVAILABLE: %d\n\n", vh.avail);
}
			

//Stack - top == front
void initStack(StackList *list){	// initialize an empty stack
	*list = -1;
}	
bool isEmptyStack(StackList  list){	//check if stack is empty
	if(list == -1){
		return true;
	}
	
	return false;
}			

void push(VirtualSpace *vh, StackList *list, Product item){	//insert from the top
	if(isFull(*vh)){
		return;
	}
	int space = allocSpace(vh);

	vh->data[space].items = item;
	vh->data[space].link = *list;
	*list = space;
}	
void pop(VirtualSpace *vh, StackList *list){	//delete from the top
	if(isEmptyStack(*list)){
		printf("\n\nSTACK IS EMPTY\n\n");
		return;
	}
	int temp = vh->data[*list].link;
	deallocSpace(vh, *list);
	*list = temp;
}					
Product peek(VirtualSpace *vh, StackList list){	// peek the top value of the Stack
	return vh->data[list].items;
}				
void displayStack(VirtualSpace vh, StackList list){	// display by stack
	if(isEmptyStack(list)){
		printf("\n\nSTACK IS EMPTY\n\n");
		return;
	}
	String m[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}; // months

	int count = 0;
	Product data;
	printf("\n\nDISPLAY STACK from %d\n", list);
	printf("%-8s | %-10s | %-25s | %-10s | %-10s | %-20s\n", "LIST #", "PROD ID", "PROD NAME", "PROD QTY", "PROD PRICE", "PROD EXP");
	printf("---------------------------------------------------------------------------------------------------\n");
	while(!(isEmptyStack(list))){
		count++;
		data = peek(&vh, list);
		printf("%-8d | %-10d | %-25s | %-10d | %-10.2f | %8s %02d, %-4d\n", count, data.prodID, data.prodName, data.prodQty, data.prodPrice, m[data.prodExp.month], data.prodExp.date, data.prodExp.year);
		pop(&vh, &list);
	}
	printf("---------------------------------------------------------------------------------------------------\n");
	printf("There are %d product in stack", count);
}		

//Queue
void initQueue(Queue *q){	//initialize queue an empty queue
	q->rear = -1;
	q->front = - 1;
}		
bool isEmptyQueue(Queue q){	// check if queue is empty
	if(q.front == -1 || q.rear == -1){
		return true;
	}

	return false;
}		
void enqueue(VirtualSpace *vh, Queue *q, Product item){	// insert rear
	if(isFull(*vh)){
		return;
	}

	vh->data[q->rear].link = vh->avail;
	int space = allocSpace(vh);
	
	if(isEmptyQueue(*q)){
		printf("\nINSERTING FIRST ITEM\n");
		q->front = space;
	}
	
	q->rear = space;
	vh->data[space].items = item;
}		
void dequeue(VirtualSpace *vh, Queue *q){	// delete front
	if(isEmptyQueue(*q)){
		printf("\n\nQUEUE IS EMPTY\n\n");
		return;
	}

	if(q->front == q->rear){
		deallocSpace(vh, (*q).front);
		q->front = -1;
		q->rear = -1;
		return;
	}

	int newFrontIndex = vh->data[(*q).front].link;
	deallocSpace(vh, (*q).front);
	q->front = newFrontIndex;
}				
Product front(VirtualSpace vh, Queue q){	//front value of Queue
	return vh.data[q.front].items;
}					
void displayQueue(VirtualSpace vh, Queue q){	//dsiplay by Queue
	if(isEmptyQueue(q)){
		printf("\n\nQUEUE IS EMPTY\n\n");
		return;
	}

	String m[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}; // months

	int count = 0;
	Product data;
	printf("\n\nDISPLAY QUEUE from INDEX %d to INDEX %d\n", q.front, q.rear);
	printf("%-8s | %-10s | %-25s | %-10s | %-10s | %-20s\n", "LIST #", "PROD ID", "PROD NAME", "PROD QTY", "PROD PRICE", "PROD EXP");
	printf("---------------------------------------------------------------------------------------------------\n");
	while(!(isEmptyQueue(q))){
		count++;
		data = front(vh, q);
		printf("%-8d | %-10d | %-25s | %-10d | %-10.2f | %8s %02d, %-4d\n", count, data.prodID, data.prodName, data.prodQty, data.prodPrice, m[data.prodExp.month], data.prodExp.date, data.prodExp.year);
		dequeue(&vh, &q);
	}
	printf("---------------------------------------------------------------------------------------------------\n");
	printf("There are %d product in Queue", count);
}

//Menu option functions STACK
void STACK(VirtualSpace *vh, StackList list[], int *count){
	String menuStack[2] = {"Create new Stack", "Choose Stack number to work with"};
	int i;
	int choice;

	printf("\nSTACK\n\n");

	do {
		system("cls");
		printf("Current Stack Lists");
		printf("\n--------------------\n");
		if(*count == 0){
			printf("NO STACKS CREATED YET");
		} else {
			for(i = 0; i < *count; i++){
			printf("STACK %d\n", i+1);
			}
		}

		printf("\n\nMENU STACK\n");
		for(i = 0; i < 2; ++i){
			printf("[%d] %s\n", i+1, menuStack[i]);
		}
		printf("Enter your choice <0 to EXIT>: ");
		scanf("%d", &choice);

		switch(choice){
			case 1: 
				initStack(&list[(*count)++]);
				printf("\nCREATED STACK # - %d\n", *count);
				break;
			case 2:
				stackManipulation(vh, list, *count);
				break;
			case 0:
				printf("RETURNING TO MAIN MENU...\n");
				return;
			default:
				printf("Invalid choice...\n");
		}
		printf("\n");
		system("pause");
	}while(choice != 0);
}

void stackManipulation(VirtualSpace *vh, StackList list[], int count){
	String menuOptionStack[3] = {"Push", "Pop", "Display Stack"};

	int i;
	int choice;
	Product newProduct;
	int stackNum;

	do {
		printf("Enter the STACK NUMBER <0 to EXIT>: ");
		scanf("%d", &stackNum);
	} while(stackNum < 0 || stackNum > count);

	do {
		system("cls");
		printf("\nMENU STACK MANIPULATION\n");
		for(i = 0; i < 3; ++i){
			printf("[%d] %s\n", i+1, menuOptionStack[i]);
		}
		printf("Enter your choice <0 to EXIT>: ");
		scanf("%d", &choice);
				
		switch(choice){
			case 1: 
				newProduct = inputProductInfo();
				push(vh, &list[stackNum - 1], newProduct);
				break;
			case 2:
				pop(vh, &list[stackNum - 1]);
				break;
			case 3:
				displayStack(*vh, list[stackNum - 1]);
				break;
			case 0:
				printf("RETURNING TO STACK OPTIONS...\n");
				return;
			default:
				printf("Invalid choice...\n");
		}
		printf("\n");
		system("pause");
	}while(choice != 0);
}

//Menu option functions QUEUE
void QUEUE(VirtualSpace *vh, Queue q[], int *count){
	String menuQ[2] = {"Create new Queue", "Choose Queue number to work with"};
	int i;
	int choice;

	printf("\nQUEUE\n\n");

	do {
		system("cls");
		printf("Current Queue Lists");
		printf("\n--------------------\n");
		if(*count == 0){
			printf("NO QUEUE CREATED YET");
		} else {
			for(i = 0; i < *count; i++){
			printf("Queue %d\n", i+1);
			}
		}

		printf("\n\nMENU QUEUE\n");
		for(i = 0; i < 2; ++i){
			printf("[%d] %s\n", i+1, menuQ[i]);
		}
		printf("Enter your choice <0 to EXIT>: ");
		scanf("%d", &choice);

		switch(choice){
			case 1: 
				initQueue(&q[(*count)++]);
				printf("\nCREATED QUEUE # - %d\n", *count);
				break;
			case 2:
				queueManipulation(vh, q, *count);
				break;
			case 0:
				printf("RETURNING TO MAIN MENU...\n");
				return;
			default:
				printf("Invalid choice...\n");
		}
		printf("\n");
		system("pause");
	}while(choice != 0);
}

void queueManipulation(VirtualSpace *vh, Queue q[], int count){
	String menuOptionQ[3] = {"Enqueue", "Dequeue", "Display Queue"};

	int i;
	int choice;
	Product newProduct;
	int qNum;

	do {
		printf("Enter the QUEUE NUMBER <0 to EXIT>: ");
		scanf("%d", &qNum);
	} while(qNum < 0 || qNum > count);

	do {
		system("cls");
		printf("\nMENU QUEUE MANIPULATION\n");
		for(i = 0; i < 3; ++i){
			printf("[%d] %s\n", i+1, menuOptionQ[i]);
		}
		printf("Enter your choice <0 to EXIT>: ");
		scanf("%d", &choice);
				
		switch(choice){
			case 1: 
				newProduct = inputProductInfo();
				enqueue(vh, &q[qNum - 1], newProduct);
				break;
			case 2:
				dequeue(vh, &q[qNum - 1]);
				break;
			case 3:
				displayQueue(*vh, q[qNum - 1]);
				break;
			case 0:
				printf("RETURNING TO QUEUE OPTIONS...\n");
				return;
			default:
				printf("Invalid choice...\n");
		}
		printf("\n");
		system("pause");
	}while(choice != 0);
}
