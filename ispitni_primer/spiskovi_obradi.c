#include "spiskovi.h"

/* Formira N izlaznih datoteka sa spiskom studenata po terminima. */
void nDatoteka(FILE *spisak, Elem *lst) {
	char name_beg[] = "res/term_", name_end[] = ".txt", name[25];
	char line[25];
	int i = 0, n = 0, total = 1;
	while (fscanf(spisak, "%[^\n]\n", line) != EOF) {
		if (!lst) break;	// svi studenti su rasporedjeni po terminima
		sprintf(name, "%s%d%s", name_beg, i, name_end);
		FILE *out = fopen(name, "w");
		fprintf(out, "%s\n", line);
		n = 0;
		while (lst && n < S_MAX) {
			fprintf(out, "%d. %04d/%02d %s\n", total, lst->s->indeks % 10000, lst->s->indeks / 10000, lst->s->ime);
			lst = lst->next;
			n++;
			total++;
		}
		fclose(out);
		i++;
	}
}

/* Oslobadjanje prostora jednog studenta. */
void deleteStudent(Student *s) {
	free(s->ime);
	free(s);
}

/* Brisanje cele liste. */
void deleteList(Elem *lst) {
	Elem *stari;
	while (lst) {
		stari = lst;
		lst = lst->next;
		deleteStudent(stari->s);
		free(stari);
	}
}
