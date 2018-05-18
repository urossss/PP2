#include "dz4.h"


void swap(Person *a, Person *b) {
	Person p = *a;
	*a = *b;
	*b = p;
}

/* Sortira listu glasaca po mestu stanovanja, pa po leksikografskom pretku. */
void sort(List lst) {
	Elem *i, *j;
	for (i = lst.first; i; i = i->next)
		for (j = i->next; j; j = j->next) {
			int x = strcmp(i->person->city, j->person->city);
			if (x > 0) {
				swap(i->person, j->person);
			}
			else if (x == 0) {
				x = strcmp(i->person->surname, j->person->surname);
				if (x > 0) {
					swap(i->person, j->person);
				}
				else if (x == 0) {
					x = strcmp(i->person->name, j->person->name);
					if (x > 0) {
						swap(i->person, j->person);
					}
				}
			}
		}
}

/* Brisanje liste. */
void deleteList(List *plst) {
	Elem *curr = plst->first, *old;
	while (curr) {
		old = curr;
		curr = curr->next;
		free(old);
	}
	plst->first = plst->last = NULL;
}
