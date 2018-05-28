#ifndef _HEADER_
#define _HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	char *title, *path, *author;
} Song;

typedef struct elem {
	Song *song;
	struct elem *prev, *next;
} Elem;

typedef struct {
	Elem *first, *last;
	int len;
} List;

/* init */
void initFile(FILE *);
void printCurrentTime();

/* save */
void savePLS(FILE *, List);

/* load */
void error(int);
Song* readSong(FILE *);
List loadList(FILE *);

/* process */
void deleteSong(Song *);
void deleteList(List *);

#endif