#include "dz5.h"

int main(int argc, const char *argv[]) {
	FILE *in, *out;
	clock_t t1, t2;
	double d;

	t1 = clock();
	printCurrentTime();

	if (argc < 3) error(3);

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if (!in || !out) error(2);
	initFile(in, 2);

	List lst = loadList(in);
	savePLS(out, lst);
	deleteList(&lst);

	printCurrentTime();
	t2 = clock();

	d = (double)(t2 - t1) / CLOCKS_PER_SEC * 1000;
	printf("Utroseno vreme: %lgms\n", d);
}