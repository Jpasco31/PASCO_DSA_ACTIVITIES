#ifndef MYHEADER_H
#define MYHEADER_H

#include <stdbool.h>

#define EMPTY 0
#define DELETED -1
//NOTE: dont use this numbers as data

typedef struct {
	int elem;
	int link;
} Data;

typedef struct {
	Data *data;	
	int avail;
	int max;		//if max is reached increase the size max * 2
	int count; //counter for the number of inserted 
} VSpace;


VSpace newVSpace(int max);
int allocSpace(VSpace *vs);
void freeSpace(VSpace *vs, int loc);
bool isFull(VSpace vs); // function to chec if VS space is full -> if full call a function to resize VSpace and rehash all the values in the dictiionary to the new space 
int hash(int val, int size);	// formula = data % (max/2)

bool addElement(VSpace *vs, int elem);
bool removeElement(VSpace *vs, int elem);
void visualize(VSpace vs);

//make a function that will take in consideration if count is 70% of max or if synonym indexes are full, increase the max by x 2;
bool increasePackingDensity(VSpace *vs);

#include "MyHeader.c"

#endif
