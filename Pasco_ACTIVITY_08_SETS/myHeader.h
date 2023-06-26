#ifndef MYHEADER_H
#define MYHEADER_H

#define MAX 20

#include <stdbool.h>

typedef char String[5];

typedef struct {
	bool elems[MAX];
	int count;
}Set;

Set newSet();
bool addElement(Set *s, int item);
bool removeElement(Set *s, int item);
void displaySet(Set s);

Set unionSet(Set a, Set b);
Set intersectionSet(Set a, Set b);
Set differenceSet(Set a, Set b);
Set symmetricDiffSet(Set a, Set b);

#include "myHeader.c"

#endif
