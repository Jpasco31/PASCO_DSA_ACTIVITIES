#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	BST *myBST = newBST();
//	insertBST(&myBST, createProduct(100, "Chicken", 3, 50));
//	insertBST(&myBST, createProduct(50, "Chicken", 3, 50));
//	insertBST(&myBST, createProduct(121, "Chicken", 3, 50));
//	insertBST(&myBST, createProduct(200, "Chicken", 3, 50));
//	insertBST(&myBST, createProduct(81, "Chicken", 3, 50));
//	insertBST(&myBST, createProduct(112, "Chicken", 3, 50));
//	insertBST(&myBST, createProduct(25, "Chicken", 3, 50));
	
	myBST = addElement(myBST, createProduct(100, "Chicken", 3, 50));
	myBST = addElement(myBST, createProduct(50, "Chicken", 3, 50));
	myBST = addElement(myBST, createProduct(121, "Chicken", 3, 50));
	myBST = addElement(myBST, createProduct(200, "Chicken", 3, 50));
	myBST = addElement(myBST, createProduct(81, "Chicken", 3, 50));
	myBST = addElement(myBST, createProduct(112, "Chicken", 3, 50));
	myBST = addElement(myBST, createProduct(25, "Chicken", 3, 50));
	myBST = addElement(myBST, createProduct(111, "Chicken", 3, 50));
	myBST = addElement(myBST, createProduct(88, "Chicken", 3, 50));
	myBST = addElement(myBST, createProduct(86, "Chicken", 3, 50));

	printf("IN ORDER\n");
	inorderBST(myBST);
	printf("\nPRE ORDER\n");
	preorderBST(myBST);
	printf("\nPOST ORDER\n");
	postorderBST(myBST);
	
	// removeElement(&myBST, 121);
	deleteElement(myBST, 100);
	printf("\nPRE ORDER\n");
	preorderBST(myBST);
	printf("\nIN ORDER\n");
	inorderBST(myBST);
	

	return 0;
}
