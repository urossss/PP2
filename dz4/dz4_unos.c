#include "dz4.h"

/* Greska u alokaciji. */
void error() {
	printf("Error in allocation!\n");
	exit(1);
}

/* Ucitava tekst do kraja reda i vraca pokazivac na dobijeni string. */
char* readLine() {
	char *s = NULL, c;
	int n = 1;
	while ((c = getchar()) != '\n') {
		s = realloc(s, (++n) * sizeof(*s));
		if (s == NULL) error();
		*(s + n - 2) = c;
	}
	if (s == NULL) return s;
	*(s + n - 1) = '\0';
	return s;
}

/* Ucitava jednu rec do razmaka ili do kraja reda i vraca pokazivac na dobijeni string. */
char* readWord() {
	char *s = NULL, c;
	int n = 1;
	while ((c = getchar()) != '\n' && c != ' ') {
		s = realloc(s, (++n) * sizeof(*s));
		if (s == NULL) error();
		*(s + n - 2) = c;
	}
	if (s == NULL) return s;
	*(s + n - 1) = '\0';
	return s;
}

/* Ucitava podatke o jednom glasacu iz jednog reda. */
Person* readPerson() {
	Person *p = malloc(sizeof(Person));
	if (p == NULL) error();
	p->name = readWord();
	if (p->name == NULL) {
		free(p);
		return NULL;
	}
	p->surname = readWord();
	p->id = readWord();
	p->city = readWord();
	p->voting = NULL;
	return p;
}

/* Dodavanje na pocetak liste. */
void add_beg(List *plst, Person *p) {
	Elem *newElem = malloc(sizeof(Elem));
	newElem->person = p;
	newElem->next = plst->first;
	if (!plst->last) plst->last = newElem;
	plst->first = newElem;
}

/* Dodavanje na kraj liste. */
void add_end(List *plst, Person *p) {
	Elem *newElem = malloc(sizeof(Elem));
	newElem->person = p;
	newElem->next = NULL;
	if (!plst->first) plst->first = newElem;
	else plst->last->next = newElem;
	plst->last = newElem;
}

/* Ucitava podatke o glasacima dok se ne unese prazan red i formira listu glasaca. */
List loadList() {
	List lst = { NULL, NULL };
	Person *p;
	while (1) {
		p = readPerson();
		if (p == NULL) break;
		add_beg(&lst, p);
	}
	return lst;
}
