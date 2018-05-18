#ifndef _HEADER_
#define _HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* jedna osoba */
typedef struct {
	char *name, *surname, *id, *city, *voting;
} Person;

/* element lista osoba */
typedef struct elem {
	Person *person;
	struct elem *next;
} Elem;

/* lista osoba */
typedef struct {
	Elem *first, *last;
} List;

/* unos */
void error();
char* readLine();
char* readWord();
Person* readPerson();
void add_beg(List *, Person *);
void add_end(List *, Person *);
List loadList();

/* ispis */
void printPerson(Person *);
void printList(List);

/* obrada */
void swap(Person *, Person *);
void sort(List);
void deleteList(List *);

#endif