#ifndef CURSOR_BASED_H
#define CURSOR_BASED_H

#define MAX 10

typedef char String[30];
typedef int List;


typedef struct {
	int studID;
	String studName;
	char sex;
	String program;
}Student;

typedef struct {
	Student elem;		//data
	int next;		//link to the next address
} SType;		//structure for the array link

typedef struct {	
	SType elems[MAX];		//contain all the arraylink in the Virtual Heap
	int avail;				//available index in the Heap
}VirtualHeap;		//Virtual Heap

Student newStudent(int studID, String studName, char sex, String program);

VirtualHeap newVirtualHeap();	//create a new Virtual Heap
int allocSpace(VirtualHeap *vh);	//Allocate an available space in the virtual heap
void insertFront(VirtualHeap *vh, List *list, Student s);  //insert data in the allocated space in the virtal heap

void displayList(VirtualHeap vh, List list);	//display the data in the virutal heap beloning to that List
void visualizeSpace(VirtualHeap vh);			//display all the data in virtual heap

void deallocSpace(VirtualHeap *vh, int index);	//free the space in the virutal heap
void deallocUpdateList(VirtualHeap *vh, int index);	// to update the list to where the current deallocated index is assigned to
Student removeStudent(VirtualHeap *vh, List *list, String keyword);	//remove the student in the List by name 
//NOTE: only in the list it should not delete other students in other List in the Virtual HEAP

#include "CursorBased.c"

#endif


