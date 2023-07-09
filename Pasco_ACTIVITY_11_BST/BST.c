#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "BST.h"

// Add element to the BST based on the product ID
BST *addElement(BST *list, Product item){	// using recursive method
	
	if(isEmpty(list)){
		BST* newProd = malloc(sizeof(BST));
		newProd->data = item;
		newProd->left = NULL;
		newProd->right = NULL;
		return newProd;
	}
	
	if(item.prodID < list->data.prodID){
		// Recursively add to the left subtree
		list->left = addElement(list->left, item);
	} else if(item.prodID > list->data.prodID){
		// Recursively add to the right subtree
		list->right = addElement(list->right, item);
	} 
	
	// If item.prodID is equal to list->data.prodID, do nothing (assuming no duplicates)
	return list;
} 

void insertBST(BSTPtr *list, Product item){	//using iterative method
	BST* newProd = malloc(sizeof(BST));
	newProd->data = item;
	newProd->left = NULL;
	newProd->right = NULL;
	
	
	BST* current = *list;
	BST* prev = NULL;
	while(current != NULL){
		prev = current;
		if(item.prodID < current->data.prodID){
			current = current->left;
		} else if(item.prodID > current->data.prodID){
			current = current->right;
		} else {	// if product ID exist
			free(newProd);
			return;
		}
	}
	
	if(isEmpty(*list)){
		*list =newProd;
	} else if(item.prodID < prev->data.prodID){
		prev->left = newProd;
	} else {
		prev->right = newProd;
	}
	
	//end
} 

//Delete element in the BST base o nthe product ID
void removeElement(BST **list, int prodID){	// using iterative method
	if(isEmpty(*list)){			//if list is empty do return
		return;
	}

	BST *current = *list;		// for traversal
	BST *prev = NULL;			// storing the previous node to maintain the links

	//loop to locate the data to be deleted
	while(current != NULL && current->data.prodID != prodID){
		prev = current;
		if(prodID < current->data.prodID){
			current = current->left;
		} else if(prodID > current->data.prodID){
			current = current->right;
		} 
	}

	if(current == NULL){		//return if ID does not exist
		return;
	}

	//if node has atmost 1 child
	if(current->left == NULL || current->right == NULL){
		BST *successor;			//successor will replace the current node to be deleted
		if(current->left == NULL){
			successor = current->right;
		} else {
			successor = current->left;
		}

		//if node to delete is thee root
		if(prev == NULL){
			free(current);
			(*list) = successor;
			return;
		}

		//Check if the node to be deleted is prev's left or right child and replace this with the successor
		if(current == prev->left){
			prev->left = successor;
		} else {
			prev->right = successor;
		}

		free(current);
	} else {
		//find the successor
		BST *successorParent = NULL;	//initialize to NULL, parents is needed to fix the loop
		BST *successor = current->left;			//initialize to the left subtree
		while (successor->right != NULL) {		//loop to the MAX value in the left subtree
            successorParent = successor;
            successor = successor->right;
        }

		//adjust pointer variables of successor parents to maintain link
		if(successorParent != NULL){						//make the left child of the successor be the right of its parents
			successorParent->right = successor->left;
		} else {
			current->left = successor->left;			//if current node is the parents let it point to the succesor left
		}
		current->data = successor->data;
		free(successor);
	}
} 


BST *deleteElement(BST *list, int prodID){	//using recursive
	//base case 
	if(isEmpty(list)){
		return NULL;
	}

	//recursive calls for ancestors of node to be deleted
	if(list->data.prodID > prodID){						
		list->left = deleteElement(list->left, prodID);			//traverse to the left
		return list;
	} else if(list->data.prodID < prodID) {
		list->right = deleteElement(list->right, prodID);		//traverse to the right
		return list;
	}

	//if one of the children is empty or both are empty
	if(list->left == NULL){					
		BST *temp = list->right;
		free(list);
		return temp;
	} else if(list->right == NULL){
		BST *temp = list->left;
		free(list);
		return temp;
	} 
	
	else {	//if both children exist
		BST *successorParent = list;						
		BST *successor = list->left;				//successor
		while (successor->right != NULL) {			//traverse to the successor, finding MAX of left subtree
            successorParent = successor;
            successor = successor->right;
        }

		if(successorParent != list){					//successor parents should adjust its right pointer to the left pointer of successor to maintain link
			successorParent->right = successor->left;
		} else {										//root is the one to be deleted
			successorParent->left = successor->left;
		}

		list->data = successor->data;				//copy data of successor to the current node
		free(successor);							//free sucessor
		return list;								//return list
    } 
	
} 

// Display BST all in recursive method
void inorderBST(BST *list){
	if((isEmpty(list))){
		return;
	}
	
	if(list->left != NULL){
		inorderBST(list->left);
	}
	
	displayProduct(list->data);
	
	if(list->right != NULL){
		inorderBST(list->right);
	}
}

void preorderBST(BST *list){
	if((isEmpty(list))){
		return;
	}
	displayProduct(list->data);
	
	if(list->left != NULL){
		preorderBST(list->left);
	}
	if(list->right != NULL){
		preorderBST(list->right);
	}
}

void postorderBST(BST *list){
	if((isEmpty(list))){
		return;
	}
	
	if(list->left != NULL){
		postorderBST(list->left);
	}
	if(list->right != NULL){
		postorderBST(list->right);
	}
	
	displayProduct(list->data);
}

//Other functions
BST *newBST(){
	BST* newBST = NULL;
	
	return newBST;
}

void initBST(BST **list){
	*list = NULL;
}

bool isEmpty(BST *list){
	if(list == NULL){
		return true;
	}
	return false;
}

Product createProduct(int id, char *name, int qty, float price){
	Product newProd;
	
	newProd.prodID = id;
	strcpy(newProd.prodName, name);
	newProd.prodQty = qty;
	newProd.prodPrice = price;
	
	return newProd;
}

//use following format {<id> / <prodName>} replacing the angular bracket with data
void displayProduct(Product prod){
	printf("{%d / %s}\n", prod.prodID, prod.prodName);
}

BST *max(BST *list){
	BST *max;

	max = list;
	while(max->right != NULL){
		max = max->right;
	}

	return max;
}

BST *min(BST *list){
	BST *min;

	min = list;
	while(min->left != NULL){
		min = min->left;
	}
	
	return min;
}

bool isMember(BST *list, int prodID){
	BST *current = list;

	while(current != NULL){
		if(prodID == current->data.prodID){
			printf("MEMBERn\n");
			return true;
		} else if(prodID < current->data.prodID){
			printf("left\n");
			current = current->left;
		} else {
			printf("right\n");
			current = current->right;
		}
	}

	return false;
}


// WORKING BUT NOT EFFICIENT
// void removeElement(BST **list, int prodID){	// using iterative method
// 	if(isEmpty(*list)){			//if list is empty do return
// 		return;
// 	}

// 	BST *current = *list;		// for traversal
// 	BST *prev = NULL;			// storing the previous node to maintain the links

// 	//loop to locate the data to be deleted
// 	while(current != NULL && current->data.prodID != prodID){
// 		prev = current;
// 		if(prodID < current->data.prodID){
// 			current = current->left;
// 		} else if(prodID > current->data.prodID){
// 			current = current->right;
// 		} 
// 	}

// 	if(current == NULL){		//return if ID does not exist
// 		return;
// 	}

// 	//find the successor
// 	BST *successor = NULL;			//initialize to NULL
//     BST *successorParent = NULL;	//initialize to NULL, parents is needed to fix the loop

// 	//find the successor - the predecessor 
//     if (current->left != NULL) {		//based on the MAX value of the left subtree first
//         successorParent = current;
//         successor = current->left;
//         while (successor->right != NULL) {		//loop to the MAX value
//             successorParent = successor;
//             successor = successor->right;
//         }
//     } else if (current->right != NULL) {	//if left subtree is empty locate the successor in right subtree, by MINIMUM value
//         successorParent = current;
//         successor = current->right;
//         while (successor->left != NULL) {	//loop to the minimum value
//             successorParent = successor;
//             successor = successor->left;
//         }
//     } 

// 	//detach the successor node to its Parents node
//     if (successorParent != NULL) {		
//         if (successorParent->left == successor) {		//sucessor is in the left, then parent->left points to NULL
//             successorParent->left = NULL;
//         } else {
//             successorParent->right = NULL;				//sucessor is in the right, then parent->right points to NULL
//         }
//     }

// 	if (successor != NULL) {				//point the successor left and right to the current left and right
//         successor->left = current->left;
//         successor->right = current->right;
//     }

// 	//point the previous node to the new sucessor
//     if (prev == NULL) {						//if prev NULL meaning it the the ROOT of the tree to be deleted
//         *list = successor;
//     } else if (prev->left == current) {		//current is in the left, point the prev->left to the successor 
//         prev->left = successor;
//     } else {								//current is in the right, point the prev->right to the successor
//         prev->right = successor;
//     }

// 	free(current);							//free the current
// } 