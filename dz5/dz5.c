#include "dz5.h"

int main(int argc, const char *argv[]) {
	FILE *in, *out;
	List lst;
	char path[255] = "C:\\Music\\Compilation";
	clock_t t1, t2;
	double d;

	t1 = clock();
	printCurrentTime();

	if (argc < 3) error(3);

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if (!in || !out) error(2);
	initFile(in, 2);

	lst = loadList(in);

	//printf("Unesite novu putanju: ");
	//scanf("%s", path);
	changePath(lst, path);

	savePLS(out, lst);

	sort(lst);
	printf("Broj pesama: %d\n", lst.len);
	mostSongs(lst);

	deleteList(&lst);

	printCurrentTime();
	t2 = clock();
	d = (double)(t2 - t1) / CLOCKS_PER_SEC * 1000;
	printf("Utroseno vreme: %lgms\n", d);
}