#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "OpenHashing.h"

int main(int argc, char *argv[]) {

	Dictionary myD;
	initDict(&myD);

	bool exec;

	insertSorted(&myD, newStudent("30004176", FullName("John Ismael","Clam","Arroya"), 'M', BirthDate(10, 8, 2002),"BS DENT", 3));
	insertSorted(&myD, newStudent("30004176", FullName("John Ismael","Clam","Bueno"), 'M', BirthDate(10, 8, 2002),"BS DENT", 3));
	insertSorted(&myD, newStudent("30004176", FullName("John Ismael","Clam","Co"), 'M', BirthDate(10, 8, 2002),"BS DENT", 3));
	insertSorted(&myD, newStudent("30004176", FullName("John Ismael","Clam","Cander"), 'M', BirthDate(10, 8, 2002),"BS DENT", 3));

	exec = insertSorted(&myD, newStudent("19104176", FullName("Rynne","Clam","Pasco"), 'M', BirthDate(10, 8, 2002),"BS DENT", 3));
	exec = insertSorted(&myD, newStudent("16104176", FullName("Jerry","Lumancas","Pacco"), 'M', BirthDate(11, 3, 1963),"BS DENT", 1));
	exec = insertSorted(&myD, newStudent("20101082", FullName("Jericho","Clam","Pecco"), 'M', BirthDate(12, 31, 2000),"BSCS", 2));
	exec = insertSorted(&myD, newStudent("21104176", FullName("John Ysmael","Clam","Pasco"), 'M', BirthDate(10, 8, 2002),"BS DENT", 3));
	insertSorted(&myD, newStudent("30004176", FullName("John Ismael","Clam","Pasco"), 'M', BirthDate(10, 8, 2002),"BS DENT", 3));
	insertSorted(&myD, newStudent("21004176", FullName("John Ismael","Klam","Pasco"), 'M', BirthDate(10, 8, 2002),"BS DENT", 3));
	insertSorted(&myD, newStudent("20004176", FullName("John Ismael","Clam","Pasco"), 'M', BirthDate(10, 8, 2002),"BS DENT", 3));
	insertSorted(&myD, newStudent("10004176", FullName("John Ismael","Clam","Pasco"), 'M', BirthDate(10, 8, 2002),"BS DENT", 3));
	insertSorted(&myD, newStudent("21004176", FullName("John Osmael","Clam","Pasco"), 'M', BirthDate(10, 8, 2002),"BS DENT", 3));
	
	exec = insertSorted(&myD, newStudent("19104176", FullName("Angeica","Clam","Rasko"), 'M', BirthDate(10, 8, 2002),"BS DENT", 3));

	// exec = removeData(&myD, "Pesco", "17101082");
	// printf("\n%s\n", (exec == 1) ? "Removed": "Not");
	// exec = removeData(&myD, "Pesco", "211101082");
	// printf("\n%s\n", (exec == 1) ? "Removed": "Not");
	// exec = removeData(&myD, "Rasko", "19104176");
	// printf("\n%s\n", (exec == 1) ? "Removed": "Not");

	visualize(myD);

	Student myStudent = accessInfo(myD, "Pasco", "21176");
	Student myStudent2 = accessInfo(myD, "Pasco", "21104176");
	printf("My student 1: %s %s\n", myStudent.studName.fName, myStudent.studName.lName);
	printf("My student 2: %s %s\n", myStudent2.studName.fName, myStudent2.studName.lName);

	free(myD.elems);

	return 0;
}
