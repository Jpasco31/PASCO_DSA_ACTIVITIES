#include <stdio.h>
#include <stdlib.h>
#include "myHeader.h"


int main(int argc, char *argv[]) {
	
	Set a = newSet();
	Set b = newSet();
	
	addElement(&a, 1);
	addElement(&a, 3);
	addElement(&a, 5);
	addElement(&a, 7);
	addElement(&a, 9);
	addElement(&a, 11);
	addElement(&a, 13);
	addElement(&a, 15);
	addElement(&a, 17);
	addElement(&a, 19);
	removeElement(&a, 11);
	printf("A\n");
	displaySet(a);
		
	addElement(&b, 1);
	addElement(&b, 3);
	addElement(&b, 5);
	addElement(&b, 7);
	addElement(&b, 10);
	addElement(&b, 12);
	addElement(&b, 14);
	addElement(&b, 16);
	addElement(&b, 18);
	addElement(&b, 19);
	printf("B\n");
	displaySet(b);
	
	Set unionS = newSet();
	
	unionS = unionSet(a, b);
	printf("Union\n");
	displaySet(unionS);
	
	Set intersectS = newSet();
	intersectS = intersectionSet(a, b);
	printf("Intersection\n");
	displaySet(intersectS);
	
	Set diffS = newSet();
	diffS = differenceSet(a, b);
	printf("Difference\n");
	displaySet(diffS);
	
	Set symDiffS = newSet();
	symDiffS = symmetricDiffSet(a, b);
	printf("Symmetric Difference\n");
	displaySet(symDiffS);
	
	return 0;
}
