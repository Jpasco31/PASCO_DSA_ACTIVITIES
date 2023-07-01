#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "OpenHashing.h"

Name FullName(String fName, String mName, String lName){
	Name newName;
	
	strcpy(newName.fName, fName);
	strcpy(newName.mName, mName);
	strcpy(newName.lName, lName);
	
	return newName;
}

MyDate BirthDate(int date, int month, int year){
	MyDate birthDate;
	
	birthDate.date = date;
	birthDate.month = month - 1;
	birthDate.year = year;
	
	return birthDate;
}

Student newStudent(String studID ,Name studName, char sex, MyDate birthdate, String program, int year){
	Student newStudent;
	
	strcpy(newStudent.studID, studID);
	newStudent.studName = studName;
	newStudent.sex = sex;
	newStudent.birthdate = birthdate;
	strcpy(newStudent.program, program);
	newStudent.year = year;

	return newStudent;
}

void initDict(Dictionary *d){	//all array should be intialize and pointing to null
	d->max = 26;
	d->count = 0;
	d->elems = malloc(sizeof(SType) * d->max);	//dynamic sizing for array

	int i;
	for(i = 0; i <  d->max; i++){
		d->elems[i] = NULL;
	}
}	
int hashing(String lName){	//first letter of the last name - hash number 
	return toupper(lName[0]) - 'A';
} 

//inserting insert sorted base on lastname if not firstname if not middlename if not ID number

// Manipulating funcitons
bool insertSorted(Dictionary *d, Student stud){	//last name -> first name -> middle name -> ID number
	SType *newNode = malloc(sizeof(SType));

	if(newNode == NULL){
		return false;		//check if memoery is allocated 
	}

	newNode->data = stud;
	newNode->next = NULL;

	int index = hashing(stud.studName.lName);		//hash map function

	if (d->elems[index] == NULL) {		//check if it is the first node in the index
        d->elems[index] = newNode;
		d->count++;
		return true;
    } 
	
	
	SType *current = d->elems[index];
	SType *prev = NULL;
	
	while (current != NULL && CompareStudentInfo(current->data, newNode->data) < 0) {
		prev = current;
		current = current->next;
	}

	if(prev == NULL){	//insert front
		newNode->next = d->elems[index];
		d->elems[index] = newNode;
	} else {			//insert At the sorted position
		prev->next = newNode;
		newNode->next = current;
	}
	

	return true;
}	

int CompareStudentInfo(Student s1, Student s2){
	int lastNameCompare = strcmp(s1.studName.lName, s2.studName.lName);
	if(lastNameCompare != 0){
		return lastNameCompare;
	}

	int firstNameCompare = strcmp(s1.studName.fName, s2.studName.fName);
	if(firstNameCompare != 0){
		return firstNameCompare;
	}

	int middleNameCompare = strcmp(s1.studName.mName, s2.studName.mName);
	if(middleNameCompare != 0){
		return middleNameCompare;
	}

	return strcmp(s1.studID, s2.studID);

}

bool removeData(Dictionary *d, String lName, String ID){		//delete by Lastname and student ID
	int index = hashing(lName);
	SType *current = d->elems[index];
	bool removed = false;

	SType *prev = NULL;
	while(current != NULL && removed == false){
		if(!strcmp(current->data.studID, ID)){
			removed = true;
			if(prev == NULL){
				d->elems[index] = current->next;
			} else {
				prev->next = current->next;
			}
			free(current);
		} else {
			prev = current;
			current = current->next;
		}	
	}
	
	return removed;
}	

Student accessInfo(Dictionary d, String lName, String ID){	//search by student
	int index = hashing(lName);
	Student studentInfoEmpty = newStudent("0", FullName("EMPTY","",""), ' ', BirthDate(0, 0, 0),"", 0);

	if(index >= d.max || d.elems[index] == NULL){
		return studentInfoEmpty;
	}
	SType *current = d.elems[index];

	while(current != NULL && strcmp(current->data.studID, ID) != 0){
		current = current->next;
	}

	if(current != NULL){
		return current->data;
	}

	return studentInfoEmpty; 
}	


void visualize(Dictionary d){
	printf("\n\nVISUALIZE\n");
	printf("%6s | (%s,%s, %s)\n", "INDEX", "ID", "LAST NAME", "FIRSTNAME");
	printf("-------------------------\n");
	
	int i;
	for(i = 0; i < d.max; i++){
		printf("%6d | ", i + 1);
		if(d.elems[i] == NULL){
			printf("EMPTY\n");
		} else {
			SType *current = d.elems[i];
			while(current != NULL){
				printf("(%s, %s, %s) ", current->data.studID, current->data.studName.lName, current->data.studName.fName);
				current = current->next;
			}
			printf("\n");
		}
	}

	printf("Number of Index used: %d\n", d.count);
}

void freeDictionary(Dictionary *d){
	int i;
	for(i = 0; i < d->max; i++){
		if(d->elems[i] != NULL){
			SType *current = d->elems[i];
			SType *toFree = NULL;
			while(current != NULL){
				toFree = current;
				current = current->next;
				free(toFree);
			}
		}
	}

	free(d->elems);

	printf("\nDICTIONARY FREED\n");
}
