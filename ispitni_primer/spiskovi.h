#ifndef _HEADER_
#define _HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CHUNK 10
#define T_MAX 75
#define S_MAX 3

typedef struct {
	char *ime;
	int indeks;
	char smer[3];
} Student;

typedef struct elem {
	Student *s;
	struct elem *prev, *next;
} Elem;

/* citaj */
Elem* loadList(FILE *);

/* pisi */
void printList(Elem *);
void exportList(FILE *, Elem *);
void formirajTermine(FILE *, FILE *);

/* obradi */
void nDatoteka(FILE *, Elem *);
void deleteStudent(Student *);
void deleteList(Elem *);

/* ostalo */
void error(int);
void printCurrentTime();

#endif