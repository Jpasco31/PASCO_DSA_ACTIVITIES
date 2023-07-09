#ifndef BST_H
#define BST_H

#include <stdbool.h>

typedef struct {
	int prodID;
	char prodName[20];
	int prodQty;
	float prodPrice;
}Product;

typedef struct node {
	Product data;
	struct node *left;
	struct node *right;
}NodeType, *NodePtr, BST,*BSTPtr;

// Add element to the BST based on the product ID
BST *addElement(BST *list, Product item); // using recursive method
void insertBST(BSTPtr *list, Product item); //using iterative method

//Delete element in the BST base o nthe product ID
void removeElement(BST **list, int prodID); // using iterative method
BST *deleteElement(BST *list, int prodID); //using recursive

// Display BST all in recursive method
void inorderBST(BST *list);
void preorderBST(BST *list);
void postorderBST(BST *list);

//Other functions
BST *newBST();
void initBST(BST **list);
bool isEmpty(BST *list);
Product createProduct(int id, char *name, int qty, float price);
//use following format {<id> / <prodName>} replacing the angular bracket with data
void displayProduct(Product prod);
BST *max(BST *list);
BST *min(BST *list);
bool isMember(BST *list, int prodID);

#include "BST.c"

#endif
