#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CursorBased.h"

Student newStudent(int studID, String studName, char sex, String program){
	Student s;
	
	s.studID = studID;
	strcpy(s.studName, studName);
	s.sex = sex;
	strcpy(s.program, program);
	
	return s;
}

VirtualHeap newVirtualHeap(){
	VirtualHeap vh;
	
	int i;
	
	for(i = 0; i < MAX; i++){
		vh.elems[i].elem = newStudent(0,"",' ',"");
		vh.elems[i].next = i - 1;
	}
	
	vh.avail = MAX - 1;
	
	return vh;
}
int allocSpace(VirtualHeap *vh){
	int retVal = vh->avail;
	
	if(retVal != -1){
		vh->avail = vh->elems[vh->avail].next;
	}
	
	return retVal;
}
void insertFront(VirtualHeap *vh, List *list, Student s){
	List temp = allocSpace(vh);
	
	if(temp == -1){
		printf("\n\nNOT ENOUGH SPACE IN THE VIRTUAL HEAP\n");
		printf("Cannot add - %s\n\n", s.studName);
		return;
	}
	vh->elems[temp].elem = s;
	vh->elems[temp].next = *list;
	*list = temp;
}

void displayList(VirtualHeap vh, List list){		//display the data in the list
	 int i;
	printf("LIST\n");
	printf("%5s | %30s | %s\n", "INDEX", "ELEMENTS", "NEXT");
	printf("---------------------------------------------\n");
	
	while(list != -1){
		printf("%5d | ", list);
	
		if(vh.elems[list].elem.studID != 0){
			printf("%4d - %-23s | ", vh.elems[list].elem.studID, vh.elems[list].elem.studName);
		}
		printf("%d\n", vh.elems[list].next);
		list = vh.elems[list].next;
	}
	printf("---------------------------------------------\n");
	
}

void visualizeSpace(VirtualHeap vh){
	int i;
	printf("\nVISUALIZE\n");
	printf("%5s | %30s | %s\n", "INDEX", "ELEMENTS", "NEXT");
	printf("---------------------------------------------\n");
	for(i = 0; i < MAX; i++){
		printf("%5d | ", i);
		if(vh.elems[i].elem.studID == 0){
			printf("%30s | ", "EMPTY"); 
		} else {
			printf("%4d - %-23s | ", vh.elems[i].elem.studID, vh.elems[i].elem.studName);
		}
		printf("%d\n", vh.elems[i].next);
	}
	printf("---------------------------------------------\n");
	printf("AVAILABLE: %d\n\n", vh.avail);
}

void deallocSpace(VirtualHeap *vh, int index){
	if(index == -1 && index > MAX){
		return;
	}
	deallocUpdateList(vh, index);			// to update the list to where the current index is assigned to
	
	vh->elems[index].next = vh->avail;
	vh->elems[index].elem = newStudent(0,"",' ',"");
	vh->avail = index;

	
	printf("\nINDEX %d FREED\n", index);
}

void deallocUpdateList(VirtualHeap *vh, int index){
	int i;
	int prev = index;
	for(i = 0; i < MAX; i++){
		if(vh->elems[i].next == index){
			prev = i;
		}
	}
	
	vh->elems[prev].next = vh->elems[index].next;
}
Student removeStudent(VirtualHeap *vh, List *list, String keyword){
	Student temp;
	List ctr = *list;
	
	int count = 0;

	while(*list != -1){	
		++count;
		if(strcmp(vh->elems[*list].elem.studName, keyword) == 0){
			int next = vh->elems[ctr].next;
		
			if(vh->elems[ctr].next == -1){
				vh->elems[ctr].next = vh->elems[*list].next;		
			}

			temp = vh->elems[*list].elem;
			deallocSpace(vh, *list);
			
			*list = next;

			if(count != 1){
				*list = ctr;
			} else {
				*list = next;
			}
			
			return temp;
		}
		*list = vh->elems[*list].next;
	}
	
	*list = ctr;
	return newStudent(0,"",' ',"");
}
