#include "spiskovi.h"

int main(int argc, char *argv[]) {
	clock_t t1 = clock(), t2;
	double d;
	FILE *ulaz_studenti, *ulaz_termini, *izlaz_studenti, *izlaz_termini, *spisak;
	Elem *lst;

	printCurrentTime();

	if (argc < 3) error(3);

	ulaz_studenti = fopen(argv[1], "r");
	ulaz_termini = fopen(argv[2], "r");
	izlaz_studenti = fopen("res/studenti.txt", "w");
	izlaz_termini = fopen("res/termini.txt", "w");
	if (!ulaz_studenti || !ulaz_termini || !izlaz_studenti || !izlaz_termini) error(2);

	lst = loadList(ulaz_studenti);
	printList(lst);
	exportList(izlaz_studenti, lst);

	formirajTermine(ulaz_termini, izlaz_termini);
	fclose(izlaz_termini);
	spisak = fopen("res/termini.txt", "r");
	if (!spisak) error(2);

	nDatoteka(spisak, lst);

	deleteList(lst);

	fclose(ulaz_studenti);
	fclose(ulaz_termini);
	fclose(izlaz_studenti);
	fclose(spisak);

	printCurrentTime();
	t2 = clock();
	d = (double)(t2 - t1) / CLOCKS_PER_SEC * 1000;
	printf("Utroseno vreme: %lgms\n", d);
}