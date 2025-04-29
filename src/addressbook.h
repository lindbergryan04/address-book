/*
 * addressbook.h
 *
 *  Created on: Apr 26, 2023
 *      Author: rlindberg
 */


#ifndef ADDRESSBOOK_H_
#define ADDRESSBOOK_H_

//**********
//LIBRARIES
//**********
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//**********
//CONSTANTS
//**********
#define MAXSIZ 255

//*********************
//STRUCTURE DEFINITIONS
//*********************
typedef struct contact {
	char last_name[MAXSIZ];
	char first_name[MAXSIZ];
	char email[MAXSIZ];
	char phone_number[MAXSIZ];

	struct contact *pNext;
	struct contact *pPrev;
}Contact;

typedef struct {
	Contact * pFirst;
}AddressBook;

//*********************
//FUNCTION DECLARATIONS
//*********************
void insert(int index, char contactInfo[MAXSIZ], AddressBook * pList);

Contact * createContact(char contactInfo[MAXSIZ]);

void delete(int index, AddressBook * pList);

void printContacts (AddressBook * pList);

int countContacts (AddressBook *  pList);

void getContact(int index, AddressBook *pList);

char* getContactForSave(int index, char info[MAXSIZ], AddressBook *pList);

void getField(int index, char field[255], AddressBook *pList);

void saveFile(char filePath[MAXSIZ], AddressBook *pList);

void loadFile(char filePath[MAXSIZ], AddressBook *pList);

void swap(Contact * pCur, Contact * pCurNext, AddressBook *pList);

int compare(Contact *pCur, Contact *pCurNext);

void sortList(AddressBook *pList);

void editContact(int index, char field[MAXSIZ], char newValue[MAXSIZ],AddressBook *pList);

void deallocate(AddressBook *pList);


#endif /* ADDRESSBOOK_H_ */
