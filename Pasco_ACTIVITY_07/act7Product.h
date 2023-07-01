#ifndef ACT7_PRODUCT_H
#define ACT7_PRODUCT_H

#define MAX 20

typedef char String[50];

typedef struct {
	int date;
	int month;
	int year;
}Date;

typedef struct {
	int prodID;
	String prodName;
	int prodQty;
	double prodPrice;
	Date prodExp;
}Product;

typedef struct{
	Product items;
	int link;
}SType;

typedef struct {
	SType data[MAX];
	int avail;
}VirtualSpace;

typedef int StackList;

typedef struct {	
	int front;
	int rear;
}Queue;

//Product
Date ExpDate(int date, int month, int year);
Product newProduct(int prodID, String studName, int prodQty, double prodPrice, Date prodExp);
Product inputProductInfo();

// Virtual Heap
VirtualSpace newVirtualSpace();	//create a new Virtual Heap
int allocSpace(VirtualSpace *vh);	//Allocate an available space in the virtual heap
void deallocSpace(VirtualSpace *vh, int index);	//deallocate space in the that Index
bool isFull(VirtualSpace vh);			//check if stack is full
//visualize
void visualizeSpace(VirtualSpace vh);			//print virtual space

//Stack - top == front
void initStack(StackList *list);		// initialize an empty stack		- top should be initialize -1
bool isEmptyStack(StackList list);			//check if stack is empty
void push(VirtualSpace *vh, StackList *list, Product item);	//insert from the top
void pop(VirtualSpace *vh, StackList *list);					//delete from the top
Product peek(VirtualSpace *vh, StackList list);				// peek the top value of the Stack
void displayStack(VirtualSpace vh, StackList list);		// display by stack

//Queue
void initQueue(Queue *q);		//initialize queue an empty queue		- rear and front should be initialize -1
bool isEmptyQueue(Queue q);		// check if queue is empty			- empty stack -1 if 1st insertion front == rear
void enqueue(VirtualSpace *vh, Queue *q, Product item);		// insert rear
void dequeue(VirtualSpace *vh, Queue *q);				// delete front
Product front(VirtualSpace vh, Queue q);					//front value of Queue
void displayQueue(VirtualSpace vh, Queue q);			//dsiplay by Queue
int countQueue(VirtualSpace vh, Queue q);

//Menu stack option functions
void STACK(VirtualSpace *vh, StackList list[], int *count);
void stackManipulation(VirtualSpace *vh, StackList list[], int stackNum);

//Menu queue option functions
void QUEUE(VirtualSpace *vh, Queue q[], int *count);
void queueManipulation(VirtualSpace *vh, Queue q[], int count);

// #include "act7Product.c"

#endif
