#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MyHeader.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	VSpace myVS = newVSpace(10);
	
	addElement(&myVS, 4);
	addElement(&myVS, 2);
	addElement(&myVS, 14);
	addElement(&myVS, 7);
	addElement(&myVS, 9);
	addElement(&myVS, 19);
	visualize(myVS);
	printf("Available Space for Synonym: %d\n", myVS.avail);
	printf("Count: %d\n", myVS.count);
	addElement(&myVS, 22);
	
	//rehash here
	addElement(&myVS, 33);
	removeElement(&myVS, 9);
	addElement(&myVS, 19);
	addElement(&myVS, 11);
	addElement(&myVS, 5);
	addElement(&myVS, 26);
	addElement(&myVS, 38);
	addElement(&myVS, 29);
	addElement(&myVS, 39);
	removeElement(&myVS, 39);
	addElement(&myVS, 10);

	
	//re hash here
	addElement(&myVS, 20);
	addElement(&myVS, 28);
	addElement(&myVS, 8);
	visualize(myVS);
	printf("Available Space for Synonym: %d\n", myVS.avail);
	printf("Count: %d\n", myVS.count);

	free(myVS.data);
	return 0;
}
