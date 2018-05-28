#include "dz5.h"

/* Snima listu u pls formatu u datoteku dst. */
void savePLS(FILE *dst, List lst) {
	Elem *curr = lst.first;
	int i = 1;
	fprintf(dst, "[playlist]\n\nNumberOfEntries=%d\n\n", lst.len);
	while (curr) {
		fprintf(dst, "File%d=%s\n\n", i, curr->song->path);
		fprintf(dst, "Title%d=%s\n\n", i, curr->song->title);
		i++;
		curr = curr->next;
	}
	fprintf(dst, "Version=2\n\n");
}