#include "dz4.h"

int main() {
	List lst = { NULL, NULL };
	Person *p;

	while (1) {
		system("cls");

		printf("Izaberite jednu od opcija:\n");
		printf("	1 - ucitavanje liste\n");
		printf("	2 - ubacivanje elementa na pocetak liste\n");
		printf("	3 - ubacivanje elementa na kraj liste\n");
		printf("	4 - izbacivanje elementa iz liste\n");
		printf("	5 - ispisivanje liste\n");
		printf("	6 - obrada liste\n");
		printf("	7 - brisanje liste\n");
		printf("	8 - kraj\n");

		int opt;
		scanf("%d", &opt);
		getchar();
		//fflush(stdin);

		if (opt == 8) break;

		switch (opt) {
		case 1:
			lst = loadList();
			break;
		case 2:
			printf("Unesite podatke o glasacu:\n");
			p = NULL;
			while (!p) p = readPerson();
			add_beg(&lst, p);
			break;
		case 3:
			printf("Unesite podatke o glasacu:\n");
			p = NULL;
			while (!p) p = readPerson();
			add_end(&lst, p);
			break;
		case 4:
			printf("Unesite JMBG glasaca kog zelite da izbacite iz liste:\n");
			removePerson(&lst, readWord());
			break;
		case 5:
			printList(lst);
			getch();
			break;
		case 6:
			sort(lst);
			assignVoters(lst);
			break;
		case 7:
			deleteList(&lst);
			break;
		}
	}
}