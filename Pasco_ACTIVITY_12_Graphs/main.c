#include <stdio.h>
#include <stdlib.h>
#include "Graphs.h"

int main(int argc, char *argv[]) {
	
	Dictionary myDic = newDictionary();
	
	addVertex(&myDic, "Zoo");
	addVertex(&myDic, "Japan");
	addVertex(&myDic, "Korea");
	addVertex(&myDic, "Cebu");
	addVertex(&myDic, "Siargao");
	addVertex(&myDic, "Vinland");
	addVertex(&myDic, "Spain");
	addVertex(&myDic, "Zimzalabim");

	
	addEdge(&myDic, "Japan", "Vinland");
	addEdge(&myDic, "Japan", "Cebu");
	addEdge(&myDic, "Vinland", "Cebu");
	addEdge(&myDic, "Korea", "Cebu");
	addEdge(&myDic, "Japan", "Korea");
	addEdge(&myDic, "Japan", "Siargao");
	addEdge(&myDic, "Korea", "Siargao");
	addEdge(&myDic, "Korea", "Philippines");
	addEdge(&myDic, "Spain", "Vinland");

	/*
	Zimzalabim
	Cebu - Japan, Vinland, Korea
	Japan - Vinland, Cebu, Korea, Siargao
	Korea - Cebu, Japan, Siargao
	Siargao - Japan, Korea
	Spain - Vinland
	Vinland - Japan, Cebu, Spain
	Zoo 
	*/
	
	visualize(myDic);
	depthFirst(myDic);
	//ANSWER
	//Cebu, Japan, Korea, Siargao, Vinland, Spain

	breadthFirst(myDic);
	//ANSWER
	//Cebu, Japan, Korea, Vinland, Siargao, Spain
	printf("\n\n"); system("read -n 1 -s -p \"Press any key to continue...\"");printf("\n");

	removeEdge(&myDic, "Japan", "Cebu");
	removeEdge(&myDic, "USA", "Manila");
	
	// /*
	// Zimzalabim
	// Cebu - Vinland, Korea
	// Japan - Vinland, Korea, Siargao
	// Korea - Cebu, Japan, Siargao
	// Siargao - Japan, Korea
	// Spain - Vinland
	// Vinland - Cebu, Spain
	// Zoo 
	// */
	
	visualize(myDic);
	depthFirst(myDic);
	//ANSWER
	//Cebu, Korea, Japan, Siargao, Vinland, Spain

	breadthFirst(myDic);
	//ANSWER
	//Cebu, Korea, Vinland, Japan, Siargao, Spain
	printf("\n\n"); system("read -n 1 -s -p \"Press any key to continue...\""); printf("\n");

	removeVertex(&myDic, "Japan");

	// /*
	// Zimzalabim
	// Cebu - Vinland, Korea
	// Korea - Cebu, Siargao
	// Siargao - Korea
	// Spain - Vinland
	// Vinland - Cebu, Spain
	// Zoo 
	// */
	visualize(myDic);
	depthFirst(myDic);
	//ANSWERS
	//Cebu, Korea, Siargao, Vinland, Spain

	breadthFirst(myDic);
	//ANSWER
	//Cebu, Korea, Vinland, Siargao, Spain

	freeEdges(&myDic);

	return 0;
}
