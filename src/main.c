/*
 ============================================================================
 Name        : AddressBook.c
 Author      : Ryan Lindberg
 Version     :
 Copyright   : April 26 2023
 Description : 
 ============================================================================
 */

#include "addressbook.h"

//*****
//MAIN
//*****
int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);

	char buffer[MAXSIZ];
	int index = 0;
	char contactInfo[MAXSIZ] = "";
	char field[MAXSIZ];
	char filePath[MAXSIZ];

	AddressBook myList;
	myList.pFirst = NULL;

	puts("Ready");

	do {
		fgets(buffer, MAXSIZ, stdin);
		switch (buffer[0]) {
		case 'a':
			//insert contact
			index = atoi(fgets(buffer, MAXSIZ, stdin));	//index to edit
			fgets(contactInfo, MAXSIZ, stdin);
			contactInfo[strlen(contactInfo) - 1] = '\0';
			insert(index, contactInfo, &myList);
			break;
		case 'd':
			//delete contact
			index = atoi(fgets(buffer, MAXSIZ, stdin));	//index to delete
			delete(index, &myList);
			break;
		case 'g':
			//get contact
			index = atoi(fgets(buffer, MAXSIZ, stdin));	//index to get
			getContact(index, &myList);
			break;
		case 'f':
			//get contact field
			index = atoi(fgets(buffer, MAXSIZ, stdin));	//index to edit
			fgets(field, MAXSIZ, stdin);
			field[strlen(field) - 1] = '\0';	//field to get
			getField(index, field, &myList);
			break;
		case 'n':
			//get number of contacts
			printf("%d\n", countContacts(&myList));
			break;
		case 'l':
			//load a file
			//l
			//sbcctestdata/in_20230429_22_17_13_003.txt
			//a
			//4
			//PEREZ,SIMONE,PEREZign.com,8001267271

			fgets(filePath, MAXSIZ, stdin);
			filePath[strlen(field) - 1] = '\0';
			loadFile(filePath, &myList);
			break;
		case 's':
			//save contacts to a file
			fgets(filePath, MAXSIZ, stdin);
			filePath[strlen(field) - 1] = '\0';
			saveFile(filePath, &myList);
			break;
		case 'e':
			//edit a contact
			index = atoi(fgets(buffer, MAXSIZ, stdin));	//index to edit
			fgets(field, MAXSIZ, stdin);
			field[strlen(field) - 1] = '\0';
			char newValue[MAXSIZ];	//new value for field
			fgets(newValue, MAXSIZ, stdin);
			newValue[strlen(newValue) - 1] = '\0';
			editContact(index, field, newValue, &myList);
			break;
		case 'o':
			//sort contacts
			sortList(&myList);
			break;
		case 'p':
			//print contacts
			printContacts(&myList);
			break;
		case 'c':
			//print contact count
			printf("Count: %d\n", countContacts(&myList));
			break;
		case 'q':
			//quit program
			printf("Complete\n");
			deallocate(&myList);
			break;
		}
	} while (buffer[0] != 'q');
	return EXIT_SUCCESS;
}
