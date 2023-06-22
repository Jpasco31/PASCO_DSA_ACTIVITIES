#include <stdio.h>
#include <stdlib.h>
#include "Circular.h"


int main(int argc, char *argv[]) {
	Queue myQueue;
	initQueue(&myQueue);
	
	int choice;
	String menuOption[10] = {"Enqueue", "Dequeue", "isEmpty", "isFull", "Display", "Visualize", "Front", "Remove Item", "Even Items", "Double the Multiple of Item"};
	int value;
	int i;
	
	
	enqueue(&myQueue, 56);
	enqueue(&myQueue, 29);
	enqueue(&myQueue, 15);
	enqueue(&myQueue, 8);
		
	do {
		system("cls");
		printf("\nMENU\n");
		for(i = 0; i < 10; ++i){
			printf("[%d] %s\n", i+1, menuOption[i]);
		}
		printf("Enter your choice <0 to EXIT>: ");
		scanf("%d", &choice);
		
		
		switch(choice){
			case 1: 
				printf("Enqueue\n");
				printf("Enter a number: ");
				scanf("%d", &value);
				enqueue(&myQueue, value);
				visualize(myQueue);
				break;
			case 2:
				printf("Dequeue\n");
				dequeue(&myQueue);
				visualize(myQueue);
				break;
			case 3:
				printf("Check if empty\n");
				int empty = isEmpty(myQueue);
				if(empty){
					printf("\nEMPTY LIST");
				} else {
					printf("\nNOT EMPTY LIST");
				}
				break;
			case 4:
				printf("Check if full\n");
				int full = isFull(myQueue);
				if(full){
					printf("\nFULL LIST");
				} else {
					printf("\nNOT FULL LIST");
				}
				break; 
			case 5:
				printf("Display\n");
				display(myQueue);
				break; 
			case 6:
				printf("Visualize\n");
				visualize(myQueue);
				break; 	
			case 7:
				printf("Front\n");
				int frontVal = front(myQueue);
				printf("Front value: %d\n", frontVal);
				break;
			case 8:
				printf("Remove Item\n");
				printf("Enter a number: ");
				scanf("%d", &value);
				visualize(myQueue);
				removeItem(&myQueue, value);
				visualize(myQueue);
				break;
			case 9:
				printf("Even Items\n");
				printf("\nMy Queue before\n");
				visualize(myQueue);
				Queue evenQ = removeEven(&myQueue);
				printf("\nMy Queue\n");
				visualize(myQueue);
				printf("\nEven Queue\n");
				visualize(evenQ);
				display(evenQ);
				break;
			case 10:
				printf("Double the Multiple of the Item\n");
				printf("Enter a number: ");
				scanf("%d", &value);
				visualize(myQueue);
				int count = doubleTheValue(&myQueue, value);
				printf("\nNumber of double items: %d\n", count);
				visualize(myQueue);
				break;
			case 0:
				printf("Thank you!\n");
				break;
			default:
				printf("Invalid choice...\n");
		}
		printf("\n");
		system("pause");


	} while(choice != 0);
	printf("Bye!!\n");
	
	return 0;
}
