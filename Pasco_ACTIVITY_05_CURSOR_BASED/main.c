#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CursorBased.h"


int main(int argc, char* argv[]) {
	VirtualHeap myHeap = newVirtualHeap();
	
	visualizeSpace(myHeap);
	
	List myList = -1;
	List anotherList = -1;
	
	insertFront(&myHeap, &myList, newStudent(101, "Jonathan", 'm', "BSCS"));
	insertFront(&myHeap, &myList, newStudent(105, "Jericho", 'm', "BSCS"));
	insertFront(&myHeap, &myList, newStudent(103, "John", 'f', "BSIT"));
	insertFront(&myHeap, &anotherList, newStudent(108, "Mikaela", 'f', "BSIT"));
	insertFront(&myHeap, &anotherList, newStudent(111, "Jane", 'm', "BSCS"));
	insertFront(&myHeap, &myList, newStudent(112, "Jerry", 'f', "BSCS"));
	insertFront(&myHeap, &myList, newStudent(133, "Angelica", 'f', "BSIT"));
	insertFront(&myHeap, &myList, newStudent(102, "Heaven", 'f', "BSIT"));
	insertFront(&myHeap, &anotherList, newStudent(121, "Jose", 'm', "BSCS"));
	insertFront(&myHeap, &anotherList, newStudent(122, "Juan", 'm', "BSCS"));
	insertFront(&myHeap, &anotherList, newStudent(126, "Venus", 'f', "BSCS"));

	visualizeSpace(myHeap);

	printf("Current index of myList : %d\n\n", myList);
	printf("Current index of anotherList : %d\n\n", anotherList);

	printf("MY HEAP\n");
	displayList(myHeap, myList);
	printf("\n");
	printf("ANOTHER HEAP\n");
	displayList(myHeap, anotherList);
	
	deallocSpace(&myHeap, 8);
	
	// visualizeSpace(myHeap);
	// printf("Current index of myList : %d\n\n", myList);
	// displayList(myHeap, myList);
	Student removedStud2 = removeStudent(&myHeap, &myList, "Jerry");
	printf("Removed Student by key: %s\n", removedStud2.studName);
	// visualizeSpace(myHeap);

	// printf("Current index of myList : %d\n\n", myList);

	printf("MY HEAP\n");
	displayList(myHeap, myList);

	Student removedStud = removeStudent(&myHeap, &anotherList, "Juan");
	printf("Removed Student by key: %s\n", removedStud.studName);

	printf("ANOTHER HEAP\n");
	displayList(myHeap, anotherList);

	visualizeSpace(myHeap);

	
	
	return 0;
}
