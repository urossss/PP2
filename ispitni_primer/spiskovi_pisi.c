#include "spiskovi.h"

/* Ispisuje listu na standardni izlaz. */
void printList(Elem *lst) {
	int i = 1;
	while (lst) {
		printf("%d. %04d/%02d %s\n", i, lst->s->indeks % 10000, lst->s->indeks / 10000, lst->s->ime);
		lst = lst->next;
		i++;
	}
}

/* Ispisuje listu u izlaznu datoteku out. */
void exportList(FILE *out, Elem *lst) {
	int i = 1;
	while (lst) {
		fprintf(out, "%d. %04d/%02d %s\n", i, lst->s->indeks % 10000, lst->s->indeks / 10000, lst->s->ime);
		lst = lst->next;
		i++;
	}
}

/* Od spiska raspolozivih perioda formira spisak termina. */
void formirajTermine(FILE *in, FILE *out) {
	int d, m, y, h1, m1, h2, m2, len, t_start, t_end;
	while (fscanf(in, "%d.%d.%d.-%d:%d#%d:%d\n", &d, &m, &y, &h1, &m1, &h2, &m2) != EOF) {
		t_end = h2 * 60 + m2;
		t_start = h1 * 60 + m1;
		while (t_end - t_start >= T_MAX) {
			fprintf(out, "%02d.%02d.%02d.-%02d:%02d#%02d:%02d\n", d, m, y, t_start / 60, t_start % 60, (t_start + T_MAX) / 60, (t_start + T_MAX) % 60);
			t_start += T_MAX;
		}
	}
}
