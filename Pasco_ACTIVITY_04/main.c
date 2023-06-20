#include <stdio.h>
#include <stdlib.h>

//Uncomment for Stack ARRAY
// #include "stackarr.h"


//Uncomment for Stack LINKED LIST
#include "stacklink.h"

int main(int argc, char* argv[]) {
	
	Stack list;

	initStack(&list);
	
	push(&list, 3);
	push(&list, 5);
	push(&list, 2);
	push(&list, 7);
	
	printf("VISUALIZE STACK\n");
	visualize(list);
	printf("\n");
	printf("DISPLAY STACK\n");
	display(list);
	printf("\n");
	printf("VISUALIZE STACK\n");
	visualize(list);
	
	//Uncomment for Stack LINKED LIST
	freeStack(list);

	return 0;
}

