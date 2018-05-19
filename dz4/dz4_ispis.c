#include "dz4.h"

/* Ispisuje podatke o jednom glasacu. */
void printPerson(Person *p) {
	printf("%s %s, %s, %s, %s\n", p->surname, p->name, p->id, p->city, (p->voting) ? p->voting : "nije rasporedjen");
}

/* Ispis cele liste. */
void printList(List lst) {
	printf("\n");
	Elem *curr = lst.first;
	for (; curr; curr = curr->next)
		printPerson(curr->person);
	printf("\n");
}
