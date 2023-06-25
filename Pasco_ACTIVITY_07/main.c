#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "act7Product.h"


int main(int argc, char* argv[]) {

	VirtualSpace myHeap = newVirtualSpace();	//Create virtual Space 

	StackList myStack[MAX];
	Queue myQ[MAX];
	int stackCount = 0;
	int qCount = 0;

	int choice;
	int i;
	String menuOption[3] = {"Stack", "Queue", "Visualize Virtual Space"};

	//Queue options
	String menuQueue[2] = {"Create new Queue", "Choose Queue number to work with"};
	String menuOptionQueue[3] = {"Enqueue", "Dequeue", "Display Queue"};

	do {
		system("cls");
		printf("\nMENU\n");
		for(i = 0; i < 3; ++i){
			printf("[%d] %s\n", i+1, menuOption[i]);
		}
		printf("Enter your choice <0 to EXIT>: ");
		scanf("%d", &choice);
				
		switch(choice){
			case 1: 
				STACK(&myHeap, myStack, &stackCount);
				printf("Stack count - %d\n", stackCount);
				break;
			case 2: 
				QUEUE(&myHeap, myQ, &qCount);
				printf("Q count - %d\n", qCount);
				break;
			case 3:
				visualizeSpace(myHeap);
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
	
	return 0;
}
