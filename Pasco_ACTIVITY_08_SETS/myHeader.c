#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "myHeader.h"

Set newSet(){
	Set newSet;
	memset(newSet.elems, false, MAX);
	newSet.count = 0;
	
	return newSet;
}

bool addElement(Set *s, int item){
	if(item >= MAX || s->elems[item] || item < 0){
		return false;
	}
	
	s->elems[item] = true;
	s->count++;
	return true;
	
}

bool removeElement(Set *s, int item){
	if(item >= MAX || s->elems[item] == false || item < 0){
		return false;
	}
	
	s->elems[item] = false;
	s->count--;
	return true;

}

void displaySet(Set s){
	if(s.count == 0){
		printf("\nSET IS EMPTY\n");
		return;
	}
	
	int i;
	for(i = 0; i < MAX; i++){
		if(s.elems[i]){
			printf("%d ", i);
		}
	}
	printf("\n");
}

Set unionSet(Set a, Set b){
	int i;
	Set unionSet = newSet();
	
	for(i = 0; i < MAX; i++){
		if(a.elems[i] || b.elems[i]){
			unionSet.elems[i] = true;
		unionSet.count++;
		}
	}
	
	return unionSet;
}

Set intersectionSet(Set a, Set b){
	int i;
	Set intersectSet = newSet();
	
	for(i = 0; i < MAX; i++){
		if(a.elems[i] && b.elems[i]){
			intersectSet.elems[i] = true;
			intersectSet.count++;
		}
	}
	
	return intersectSet;
}

Set differenceSet(Set a, Set b){
	int i;
	Set difSet = newSet();
	
	for(i = 0; i < MAX; i++){
		if(a.elems[i] && !(b.elems[i])){
			difSet.elems[i] = true;
			difSet.count++;
		}
	}
	
	return difSet;
}

Set symmetricDiffSet(Set a, Set b){
	int i;
	Set symDifSet = newSet();
	
	for (i = 0; i < MAX; i++) {
	    if (a.elems[i] != b.elems[i]) {
	        symDifSet.elems[i] = true;
	        symDifSet.count++;
	    }
	}
	
	return symDifSet;
}

int cardinalitySet(Set s){
	return s.count;
}
