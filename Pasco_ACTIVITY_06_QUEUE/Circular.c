#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Circular.h"

void initQueue(Queue *q){
	q->front = 7;
	q->rear = 6;
	
	int i;
	for(i = 0; i < MAX; ++i ){
		q->elems[i] = EMPTY;
	}
}

void enqueue(Queue *q, int item){
	if(isFull(*q)){
		printf("\nCIRCULAR ARRAY IS FULL\n");
		return;
	}
	
	q->rear = (q->rear + 1) % MAX;
	q->elems[q->rear] = item;
}

void dequeue(Queue *q){
	if(isEmpty(*q)){
		return;
	}
	
	q->elems[q->front] = EMPTY;
	q->front = (q->front + 1) % MAX;
}
int front(Queue q){
	if(!isEmpty(q)){
		return q.elems[q.front];
	}
	return EMPTY;
}

bool isEmpty(Queue q){
	return (q.rear + 1) % MAX == q.front;
}

bool isFull(Queue q){
	return (q.rear + 2) % MAX == q.front;
}

void visualize(Queue q){
	int i;
	
	printf("%5s | %5s | %s\n", "INDEX", "VALUE", "POSITION");
	printf("------------------------\n");
	for(i = 0; i < MAX; i++){
		printf("%5d | ", i);
		if(q.elems[i] != EMPTY){
			printf("%5d | ", q.elems[i]);
		} else {
			printf("%5s | ", "EMPTY");
		}
		if(i == q.front){
			printf(" Front");
		}
		if (i == q.rear){
			printf(" Rear");
		}
		printf("\n");
	}
	printf("------------------------\n");
}

void display(Queue q){
	if(isEmpty(q)){
		printf("\nLIST IS EMPTY\n");
		return;
	}
	printf("\n{");
	while(!isEmpty(q)){
		if(q.rear == q.front){
			printf("%d", front(q));
		} else {
			printf("%d, ", front(q));
		}
		dequeue(&q);
	}
	printf("}\n");
}

bool removeItem(Queue *q, int item){
	if(isEmpty(*q)){
		return false;
	}
	
	int remainingCount = countQueue(*q);
	// printf("\nCount = %d\n", remainingCount);
	int frontVal;
	bool isRemoved = false;
	
	while(remainingCount != 0){
			frontVal = front(*q);
		if((frontVal != item && isRemoved == false) || isRemoved == true){
			dequeue(q);
			enqueue(q, frontVal);
		} else if (frontVal == item && isRemoved == false) {
			dequeue(q);
			isRemoved = true;
		} 
		remainingCount--;
	}

	// remainingCount = countQueue(*q);
	// printf("\nCount = %d\n", remainingCount);

	return isRemoved; 
}

Queue removeEven(Queue *q){
	if(isEmpty(*q)){
		return *q;
	}

	Queue evenQ;
	initQueue(&evenQ);

	int remainingCount = countQueue(*q);
	int frontVal;
	
	while(remainingCount != 0){
		frontVal = front(*q);
		if(frontVal %  2 == 0){
			dequeue(q);
			enqueue(&evenQ, frontVal);
		} else {
			dequeue(q);
			enqueue(q, frontVal);
		} 
		remainingCount--;
	}

	return evenQ;
}

int doubleTheValue(Queue *q, int value){
	if(isEmpty(*q)){
		return 0;
	}

	int doubleCtr = 0;

	int remainingCount = countQueue(*q);
	int frontVal;

	while(remainingCount != 0){
		frontVal = front(*q);
		if(frontVal % value == 0){
			frontVal *= 2;
			dequeue(q);
			enqueue(q, frontVal);
			doubleCtr++;
		} else {
			dequeue(q);
			enqueue(q, frontVal);
		}
		--remainingCount;
	}

	return doubleCtr;
}

int countQueue(Queue q){
	int count = 0;

	// while(!isEmpty(q)){
	// 	++count;
	// 	dequeue(&q);
	// }

	count = (q.rear - q.front + (MAX+1)) % MAX;
    
	
	return count;
}




