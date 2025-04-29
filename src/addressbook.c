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

Contact* createContact(char contactInfo[MAXSIZ]) {

	Contact *pNew = malloc(sizeof(Contact));

	memset(pNew->first_name,'\0',MAXSIZ);
	memset(pNew->last_name,'\0',MAXSIZ);
	memset(pNew->email,'\0',MAXSIZ);
	memset(pNew->phone_number,'\0',MAXSIZ);


	char *stringPtr1 = contactInfo;
	char *stringPtr2 = NULL;

	//get first name
	stringPtr2 = strstr(stringPtr1, ",");
	strncpy(pNew->first_name, stringPtr1, (stringPtr2) - stringPtr1);
	stringPtr2++;
	stringPtr1 = stringPtr2;
	pNew->first_name[strlen(pNew->first_name)] = '\0';

	//get last name
	stringPtr2 = strstr(stringPtr1, ",");
	strncpy(pNew->last_name, stringPtr1, (stringPtr2) - stringPtr1);
	stringPtr2++;
	stringPtr1 = stringPtr2;
	pNew->last_name[strlen(pNew->last_name)] = '\0';

	//get email
	stringPtr2 = strstr(stringPtr1, ",");
	strncpy(pNew->email, stringPtr1, (stringPtr2) - stringPtr1);
	stringPtr2++;
	stringPtr1 = stringPtr2;
	pNew->email[strlen(pNew->email)] = '\0';

	while (*stringPtr2 != '\0') {
		stringPtr2++;
	}

	//get phone number
	strncpy(pNew->phone_number, stringPtr1, (stringPtr2) - stringPtr1);

	return (pNew);
}

void insert(int index, char contactInfo[MAXSIZ], AddressBook *pList) {

	// Inserting the contact node into linked list

	Contact *pNew = createContact(contactInfo);
	Contact *pCur = pList->pFirst;
	Contact *pCurPrev = NULL;

	if (pNew) { //If malloc successful

		if (pCur == NULL) { //inserting to empty list
			pNew->pNext = pCur;
			pList->pFirst = pNew;
			pNew->pPrev = NULL;

		} else { //inserting anywhere else

			//traverse list so that pCur = index.
			int i = 0;
			while (i < index) {
				if (i == countContacts(pList) - 1) {
					pCurPrev = pCur;
				}
				pCur = pCur->pNext;
				i++;
			}

			//inserting pNew

			if (pCur != NULL) {
				if (pCur->pPrev != NULL) { //inserting in middle of list
					Contact *pCurPrev1 = pCur->pPrev; //Contact *pCurNext = pCur->pNext;
					pNew->pNext = pCur; //pCur->pNext = pNew;
					pCur->pPrev = pNew; //pNew->pPrev = pCur;
					pNew->pPrev = pCurPrev1; //pCurNext->pPrev = pNew;
					pCurPrev1->pNext = pNew; //pNew->pNext = pCurNext;
				} else { //inserting at start of list
					pList->pFirst = pNew;
					pCur->pPrev = pNew;
					pNew->pNext = pCur;
					pNew->pPrev = NULL;
				}
			} else { //inserting at end of list
				pNew->pPrev = pCurPrev;
				pNew->pPrev->pNext = pNew;
				pNew->pNext = pCur;
			}
		}
	}
}

void delete(int index, AddressBook *pList) {

	//index > number of contacts, do nothing
	if (index <= countContacts(pList) - 1) {

		Contact *pCur = pList->pFirst;

		//traverse list so that pCur = index.
		int i = 0;
		while (i < index) {
			pCur = pCur->pNext;
			i++;
		}

		if (pCur->pPrev == NULL) { //deleting at start of list
			pList->pFirst = pCur->pNext;
			if (pList->pFirst != NULL) {
				pList->pFirst->pPrev = NULL;
			}
			free(pCur);
		} else if (pCur->pNext == NULL) {  //deleting at end of list
			pCur->pPrev->pNext = NULL;
			free(pCur);
		} else { //deleting in the middle of the list
			Contact *pCurPrev = pCur->pPrev;
			Contact *pCurNext = pCur->pNext;
			pCurPrev->pNext = pCurNext;
			pCurNext->pPrev = pCurPrev;
			free(pCur);
		}

	}
}

void printContacts(AddressBook *pList) {

	printf("\n----- Contacts List -----\n");

	Contact *pCur = pList->pFirst;

	if (pCur != NULL) { //if list not empty
		int i = 0;
		while (pCur) {
			printf("Contact: %d\nName: %s %s\nEmail: %s\nPhone Number: %s\n", i,
					pCur->first_name, pCur->last_name, pCur->email,
					pCur->phone_number);
			i++;
			pCur = pCur->pNext;
		}
	} else {
		printf("No contacts.\n");
	}
}

int countContacts(AddressBook *pList) {
	Contact *pCur = pList->pFirst;

	if (pCur != NULL) { //if list is not empty
		int i = 1;
		while (pCur->pNext != NULL) {
			i++;
			pCur = pCur->pNext;
		}
		return (i);
	} else {
		return (0);
	}
}

void getContact(int index, AddressBook *pList) {
	//string to hold info
	char info[MAXSIZ] = "";

	//index > number of contacts, do nothing
	if (index <= countContacts(pList) - 1) {

		Contact *pCur = pList->pFirst;

		//traverse list so that pCur = index.
		int i = 0;
		while (i < index) {
			pCur = pCur->pNext;
			i++;
		}

		strcat(info, pCur->first_name); // Concatenate pCur->first_name to info string
		strcat(info, ",");   // Add a comma to info
		strcat(info, pCur->last_name);
		strcat(info, ",");
		strcat(info, pCur->email);
		strcat(info, ",");
		strcat(info, pCur->phone_number);
	}
	printf("%s\n", info);
}

void getField(int index, char field[MAXSIZ], AddressBook *pList) {
	//string to hold info
	char info[MAXSIZ] = "";

	//index > number of contacts, do nothing
	if (index <= countContacts(pList) - 1) {

		Contact *pCur = pList->pFirst;

		//traverse list so that pCur = index.
		int i = 0;
		while (i < index) {
			pCur = pCur->pNext;
			i++;
		}

		//if statements to get specific field of user input
		if (strcmp(field, "firstName") == 0) { //if input == "firstName"
			strcat(info, pCur->last_name); // Concatenate pCur->first_name to info string
		}
		if (strcmp(field, "lastName") == 0) {
			strcat(info, pCur->first_name);
		}
		if (strcmp(field, "email") == 0) {
			strcat(info, pCur->email);
		}
		if (strcmp(field, "phoneNumber") == 0) {
			strcat(info, pCur->phone_number);
		}

	}
	printf("%s\n", info);
}

void editContact(int index, char field[MAXSIZ], char newValue[MAXSIZ],
		AddressBook *pList) {

	//index > number of contacts, do nothing
	if (index <= countContacts(pList) - 1) {

		Contact *pCur = pList->pFirst;

		//traverse list so that pCur = index.
		int i = 0;
		while (i < index) {
			pCur = pCur->pNext;
			i++;
		}

		if (strcmp(field, "firstName") == 0) {
			strcpy(pCur->last_name, newValue);
		}
		if (strcmp(field, "lastName") == 0) {
			strcpy(pCur->first_name, newValue);
		}
		if (strcmp(field, "email") == 0) {
			strcpy(pCur->email, newValue);
		}
		if (strcmp(field, "phoneNumber") == 0) {
			strcpy(pCur->phone_number, newValue);
		}

	}
}

void saveFile(char filePath[MAXSIZ], AddressBook *pList) {
	filePath[strlen(filePath) - 1] = '\0';

	Contact *pCur = pList->pFirst;
	FILE *pFile = fopen(filePath, "w");

	fprintf(pFile, "lastName,firstName,email,phoneNumber\n");

	int i = 0;

	if (pFile) {	//if file opened
		if (pCur != NULL) { //if list not empty
			while (pCur) { //iterate over list
				char info[MAXSIZ] = "";
				fprintf(pFile, "%s\n", getContactForSave(i, info, pList)); //write all contact fields to pFile
				pCur = pCur->pNext;
				i++;
			}
		}
	}
	fclose(pFile);
}

char* getContactForSave(int index, char info[MAXSIZ], AddressBook *pList) {

	//index > number of contacts, do nothing
	if (index <= countContacts(pList) - 1) {

		Contact *pCur = pList->pFirst;

		//traverse list so that pCur = index.
		int i = 0;
		while (i < index) {
			pCur = pCur->pNext;
			i++;
		}

		strcat(info, pCur->first_name); // Concatenate pCur->first_name to info string
		strcat(info, ",");   // Add a comma to info
		strcat(info, pCur->last_name);
		strcat(info, ",");
		strcat(info, pCur->email);
		strcat(info, ",");
		strcat(info, pCur->phone_number);

	}
	return info;
}

void loadFile(char filePath[MAXSIZ], AddressBook *pList) {

	filePath[strlen(filePath) - 1] = '\0'; //edit filePath for opening

	FILE *pFile = fopen(filePath, "r"); //open file path for reading

	char buffer[1024];
	fgets(buffer, MAXSIZ, pFile); //skip first line of csv file
	if (pFile) { //if file opened
		int index = countContacts(pList); //set index so that contact is added at the end of list
		while (fgets(buffer, MAXSIZ, pFile)) { //while not at end of file
			buffer[strlen(buffer) - 1] = '\0';
			insert(index, buffer, pList); //insert contact with information from file to list
			index++;
		}

	}
	fclose(pFile);
}

void sortList(AddressBook *pList) {
	Contact *pCur = pList->pFirst->pNext; // pCur starts from the second element
	while (pCur) {
		Contact *pPrev = pCur->pPrev; // set pPrev to pCur's previous node
		while (pPrev && compare(pPrev, pCur) > 0) { // move pCur back as long as its previous node is larger
			swap(pPrev, pCur, pList);
			pPrev = pCur->pPrev;
		}
		pCur = pCur->pNext; // move pCur to the next node
	}
}

//swap. takes in two nodes from contact and must swap them.
void swap(Contact *pCur, Contact *pCurNext, AddressBook *pList) {

	if (pCur->pPrev == NULL) { // swapping at start of list
		Contact *pNextNext = pCurNext->pNext;
		pCur->pNext = pNextNext;
		if (pNextNext != NULL) { // check if pNextNext is not NULL
			pNextNext->pPrev = pCur;
		}
		pCurNext->pNext = pCur;
		pCur->pPrev = pCurNext;
		pCurNext->pPrev = NULL;

		// update pList->pFirst if necessary
		if (pList->pFirst == pCur) {
			pList->pFirst = pCurNext;
		}

	} else if (pCur->pNext == NULL) {  // swapping at end of list
		Contact *pCurPrev = pCur->pPrev;
		pCurPrev->pNext = pCurNext;
		pCurNext->pPrev = pCur->pPrev;
		pCurNext->pNext = pCur;
		pCur->pPrev = pCurNext;
		pCur->pNext = NULL;

	} else { // swapping in the middle of the list
		Contact *pCurPrev = pCur->pPrev;
		Contact *pNextNext = pCurNext->pNext;
		pCur->pNext = pNextNext;
		if (pNextNext != NULL) { // check if pNextNext is not NULL
			pNextNext->pPrev = pCur;
		}
		pCurNext->pNext = pCur;
		pCur->pPrev = pCurNext;
		pCurPrev->pNext = pCurNext;
		pCurNext->pPrev = pCurPrev;
	}
}

//compare. takes in two nodes from contact and must compare them  Sort order is ascending based on last name, then first name, then email, then phone number.
int compare(Contact *pCur, Contact *pCurNext) {
    int result = strcmp(pCur->first_name, pCurNext->first_name);
    if (result != 0) {
        return result;
    }
    result = strcmp(pCur->last_name, pCurNext->last_name);
    if (result != 0) {
        return result;
    }
    result = strcmp(pCur->email, pCurNext->email);
    if (result != 0) {
        return result;
    }
    result = strcmp(pCur->phone_number, pCurNext->phone_number);
    return result;
}

void deallocate(AddressBook *pList) {
    Contact *pCur = pList->pFirst;
    Contact *pNext;

    while (pCur != NULL) {
        pNext = pCur->pNext;
        free(pCur);
        pCur = pNext;
    }
}
