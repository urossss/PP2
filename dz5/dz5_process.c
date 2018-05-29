#include "dz5.h"

// promena pocetnog dela putanje

void swap(Song *s1, Song *s2) {
	Song s = *s1;
	*s1 = *s2;
	*s2 = s;
}

/* Sortira listu po imenu autora. */
void sort(List lst) {
	Elem *i, *j;
	for (i = lst.first; i; i = i->next)
		for (j = i->next; j; j = j->next)
			if (strcmp(i->song->author, j->song->author) > 0)
				swap(i->song, j->song);
}

/* Ispisuje ime izvodjaca sa najvise pesama. */
void mostSongs(List lst) {
	Elem *maxElem = NULL, *curr = lst.first, *prev;
	int maxCnt = -1, n = 0;
	while (curr) {
		prev = curr->prev;
		if (!prev || strcmp(prev->song->author, curr->song->author)) n = 0;
		if (!maxElem) maxElem = curr;
		if (++n > maxCnt) {
			maxCnt = n;
			maxElem = curr;
		}
		curr = curr->next;
	}
	if (!maxElem) {
		printf("Lista je prazna!\n");
		return;
	}
	printf("Izvodjac sa najvise pesama: %s\n", maxElem->song->author);
}

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
