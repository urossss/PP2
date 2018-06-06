#include "spiskovi.h"

/* Formira listu studenata na osnovu podataka iz datoteke in. */
Elem *loadList(FILE *in) {
	Elem *lst = NULL, *last = NULL, *novi;
	Student *s;
	char *line = NULL;
	int ind, size;
	while (fscanf(in, "%d ", &ind) != EOF) {
		/* citanje do kraja linije uz realokaciju po blokovima */
		line = malloc(CHUNK + 1);
		if (!line) error(1);
		if (fgets(line, CHUNK + 1, in) != NULL) {
			while (line[strlen(line) - 1] != '\n') {
				size = strlen(line);
				line = realloc(line, size + CHUNK + 1);
				if (!line) error(1);
				if (fgets(line + size, CHUNK + 1, in) == NULL) break;	// ako smo dosli do kraja poslednjeg reda u datoteci
			}
			if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
			/*if (strlen(line) % CHUNK) {
				line = realloc(line, strlen(line) + 1);
				if (!line) error(1);
			}*/
			//puts(line);
		}

		/* formiranje stukture jednog studenta */
		s = malloc(sizeof(Student));
		if (!s) error(1);
		s->indeks = ind;
		strncpy(s->smer, line + strlen(line) - 2, 3);
		//puts(s->smer);
		line[strlen(line) - 3] = '\0';
		line = realloc(line, strlen(line) + 1);
		if (!line) error(1);
		s->ime = line;

		/* dodavanje elementa u listu (na kraj) */
		novi = malloc(sizeof(Elem));
		if (!novi) error(1);
		novi->s = s;
		novi->next = NULL;
		novi->prev = lst;
		if (!lst) lst = novi;
		else last->next = novi;
		last = novi;
	}
	return lst;
}
