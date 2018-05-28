#include "dz5.h"

// promena pocetnog dela putanje

// sort po autoru, autor sa najvise pesama

/* Oslobadjanje prostora jedne pesme. */
void deleteSong(Song *s) {
	free(s->author);
	free(s->title);
	free(s->path);
}

/* Brisanje liste. */
void deleteList(List *plst) {
	Elem *curr = plst->first, *old;
	while (curr) {
		old = curr;
		curr = curr->next;
		deleteSong(old->song);
		free(old);
	}
	plst->first = plst->last = NULL;
	plst->len = 0;
}
