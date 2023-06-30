#ifndef OPEN_HASHING_H
#define OPEN_HASHING_H

typedef char String[30];
typedef int List;

typedef struct{
	String fName;
	String mName;
	String lName;
}Name;

typedef struct {
	int date;
	int month;
	int year;
}MyDate;

typedef struct {
	String studID;	
	Name studName;
	char sex;
	MyDate birthdate;
	String program;
	int year ;
}Student;

typedef struct node{
	Student data;		
	struct node *next;		
} SType;		

typedef struct {
	SType* *elems;
	int count;
	int max;	//max should be 26
} Dictionary;

Name FullName(String fName, String mName, String lName);
MyDate BirthDate(int date, int month, int year);
Student newStudent(String studID ,Name studName, char sex, MyDate birthdate, String program, int year);

void initDict(Dictionary *d);	//all array should be intialize and pointing to null
int hashing(String lName); //first letter of the last name - hash number 

//inserting insert sorted base on lastname if not firstname if not middlename if not ID number

// Manipulating funcitons
bool insertSorted(Dictionary *d, Student stud);	//last name -> first name -> middle name -> ID number
int CompareStudentInfo(Student s1, Student s2); // function to compare the last name -> first name -> middle name -> ID number

bool removeData(Dictionary *d, String lName, String ID);	//delete by Lastname and student ID
Student accessInfo(Dictionary d, String lName, String ID);	//search by student

void visualize(Dictionary d);

#include "OpenHashing.c"
#endif
