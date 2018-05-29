#include "dz5.h"

/* Ispisuje odgovarajucu poruku o gresci i prekida rad programa. */
void error(int e) {
	switch (e) {
	case 1:
		printf("Error in allocation!\n");
		break;
	case 2:
		printf("Error opening files!\n");
		break;
	case 3:
		printf("Not enough command line arguments!\n");
		break;
	case 4:
		printf("Invalid file format!\n");
		break;
	}
	exit(e);
}

/* Ucitava podatke o jednoj pesmi iz datoteke stream u formatu ASX */
Song* readSong(FILE *stream) {
	Song *s = malloc(sizeof(Song));
	if (!s) error(1);
	s->title = malloc(256);
	s->path = malloc(256);
	s->author = malloc(256);
	if (!s->title || !s->path || !s->author) error(1);
	char *p, tmp[10];

	fgets(tmp, 10, stream);
	if (strcmp(tmp, "<Entry>\n")) {
		free(s->title);
		free(s->path);
		free(s);
		return NULL;	// u slucaju da format nije kao sto se ocekuje ili se cita sa pogresnog mesta, nama indikator za kraj datoteke
	}

	fscanf(stream, "<Title>\"");
	fgets(s->title, 255, stream);
	p = strrchr(s->title, '"');
	if (p == NULL) error(4);
	*p = '\0';
	p = strchr(s->title, '-');
	if (p == NULL) error(4);
	strncpy(s->author, s->title, p - s->title);
	s->author[p - s->title - 1] = '\0';
	fscanf(stream, "<Ref href = \"");
	fgets(s->path, 255, stream);
	p = strrchr(s->path, '"');
	if (p == NULL) error(4);
	*p = '\0';
	fscanf(stream, "</Entry>\n");

	s->title = realloc(s->title, sizeof(char) * (strlen(s->title) + 1));
	s->path = realloc(s->path, sizeof(char) * (strlen(s->path) + 1));
	s->author = realloc(s->author, sizeof(char) * (strlen(s->author) + 1));
	if (!s->title || !s->author || !s->path) error(1);

	return s;
}

/* Ucitava listu pesama iz datoteke stream. */
List loadList(FILE *stream) {
	List lst = { NULL, NULL, 0 };
	Song *song;
	Elem *newElem;
	while (1) {
		song = readSong(stream);
		if (!song) break;
		newElem = malloc(sizeof(Elem));
		newElem->next = NULL;
		newElem->song = song;
		newElem->prev = lst.last;
		if (!lst.last) lst.first = newElem;
		else lst.last->next = newElem;
		lst.last = newElem;
		lst.len++;

		/*puts(song->author);
		puts(song->title);
		puts(song->path);*/
	}
	return lst;
}
