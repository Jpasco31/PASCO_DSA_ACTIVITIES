#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MyHeader.h"


VSpace newVSpace(int max){
	VSpace vs;
	vs.max = max % 2 == 0 ? max: max + 1;
	vs.count = 0;
	vs.data = malloc(sizeof(Data) * vs.max);
	if(vs.data == NULL){
		printf("\nNOT ENOUGH SPACE\n");
		vs.max = 0;
		vs.count = 0;
		vs.avail = 0;
		return vs;
	}

	vs.avail = vs.max / 2;

	
	int i;
	for(i = 0; i < vs.avail; i++){
		vs.data[i].elem = EMPTY;
		vs.data[i].link = -1;
	}
	
	for(; i < vs.max - 1; i++){
		vs.data[i].elem = EMPTY;
		vs.data[i].link = i + 1;
	}
	vs.data[i].elem = EMPTY;
	vs.data[i].link = -1;
	
	return vs;
}

int allocSpace(VSpace *vs){
	int retVal = vs->avail;
	
	if(retVal != -1){
		vs->avail = vs->data[vs->avail].link;
	}
	
	return retVal;
}

void freeSpace(VSpace *vs, int loc){
	vs->data[loc].link = vs->avail;
	vs->data[loc].elem = EMPTY;
	vs->avail = loc; 
}
bool isFull(VSpace vs){	// function to chec if VS space is full
	if(vs.count == 0){
		return false;
	}
	float occupied = (float)vs.count/ vs.max * 100;

	if(vs.avail != -1 && occupied < 70){
		return false;
	}
	
	return true;
} 

int hash(int val, int max){	// formula = data % (max/2)
	return val % (max/2);
}	

bool addElement(VSpace *vs, int elem){
	if(isFull(*vs)){
		// printf("\nFULL rehashing %d\n", vs->count);
		if(!increasePackingDensity(vs)){
			printf("\nSPACE NOT ALLOCATED");
			return false;
		}
	}

	int loc = hash(elem, vs->max);
	
	if(vs->data[loc].elem == EMPTY){
		vs->data[loc].elem = elem;
		vs->count++;
		return true;
	}

	if(vs->data[loc].elem == DELETED){
		int current = loc;
		while(vs->data[current].link != -1){
			if(vs->data[current].elem == elem){
			return false;
			}
		current = vs->data[current].link;
		}
		if(vs->data[current].elem == elem){
			return false;
		}

		vs->data[loc].elem = elem;
		vs->count++;
		return true;
	}
	
	int prev = loc;
	
	while(vs->data[loc].link != -1){
		if(vs->data[loc].elem == elem){
			return false;
		}
		prev = loc;
		loc = vs->data[loc].link;
	}
	
	if(vs->data[loc].link == -1 && vs->data[loc].elem != EMPTY){
		vs->data[loc].link = vs->avail;
	}

	int avail = allocSpace(vs);
	
	vs->data[avail].elem = elem;
	vs->data[avail].link = -1;
	vs->count++;
	return true;
}
bool removeElement(VSpace *vs, int elem){
	int loc = hash(elem, vs->max);
	
	if(vs->data[loc].elem == EMPTY){
		return false;
	}

	if(vs->data[loc].elem == elem){
		if(vs->data[loc].link == -1){
			vs->data[loc].elem = EMPTY;
		} else {
			vs->data[loc].elem = DELETED;
		}
		vs->count--;
		return true;
	}

	int prev = loc;

	while(vs->data[loc].elem != elem){
		if(vs->data[loc].link == -1){
			return false;
		}
		prev = loc;
		loc = vs->data[loc].link;
	}
	
	vs->data[prev].link = vs->data[loc].link;
	freeSpace(vs, loc);
	vs->count--;
	return true;
}

void visualize(VSpace vs){
		int i; 
		int half = vs.max/2;
		printf("%5s | %5s | %5s %10s %5s | %5s | %5s \n", "INDEX", "DATA", "LINK", "","INDEX", "DATA", "LINK");
		printf("---------------------            ---------------------\n");
		
		for(i = 0; i < half; i++){
			printf("%5d | %5d | %5d %10s %5d | %5d | %5d \n", 
			i, vs.data[i].elem , vs.data[i].link, "",
			i + half, vs.data[i+half].elem, vs.data[i+half].link);
		}
		
		printf("\n");
}

//make a function that will take in consideration if count is 70% of max or if synonym indexes are full, increase the max by x 2; //packing density
bool increasePackingDensity(VSpace *vs){
	int prevMax = vs->max;
    Data *prevData = vs->data;
    int countData = vs->count;

    vs->max *= 2;
    vs->avail = vs->max / 2;
    vs->data = malloc(sizeof(Data) * vs->max);
    vs->count = 0;

    if (vs->data == NULL) {
        printf("\nNOT ENOUGH SPACE\n");
        return false;
    }

    // Initialize the new memory block
    int i;
    for (i = 0; i < vs->avail; i++) {
        vs->data[i].elem = EMPTY;
        vs->data[i].link = -1;
    }

    for (; i < vs->max - 1; i++) {
        vs->data[i].elem = EMPTY;
        vs->data[i].link = i + 1;
    }
    vs->data[i].elem = EMPTY;
    vs->data[i].link = -1;

    // Copy the data from the previous array to the new one
    for (i = 0; i < prevMax; i++) {
		if(prevData[i].elem != EMPTY && prevData[i].elem != DELETED){
			 addElement(vs, prevData[i].elem);
			//  printf("%d ", vs->count);
		}
    }
	// printf("\n");

    // Free the memory of the previous array
    free(prevData);

    return true;
}

