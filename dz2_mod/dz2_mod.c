#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int **m, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			printf("%d%c", *(*(m + i) + j), j == n - 1 ? '\n' : ' ');
}

void error() {
	printf("Doslo je do greske!\n");
	exit(1);
}

int main() {
	int n, **m, i, j, k, row, col, len, s, smax, high, low;
	srand(time(NULL));

	while (1) {
		scanf("%d", &n);
		if (n <= 0) break;

		scanf("%d%d", &low, &high);

		m = malloc(n * sizeof(*m));
		if (m == NULL) error();
		for (i = 0; i < n; i++) {
			*(m + i) = malloc(n * sizeof(**m));
			if (*(m + i) == NULL) error();
			for (j = 0; j < n; j++)
				*(*(m + i) + j) = rand() / (RAND_MAX + 1.0) * (high - low + 1) + low;
		}

		printMatrix(m, n);

		smax = m[0][0];
		row = col = 0;
		for (k = 0; k < 2 * n - 1; k++) {
			i = k < n ? k : n - 1;
			for (j = k - i, s = 0; i >= 0 && j < n; j++, i--) {
				s += m[i][j];
			}
			if (s > smax) {
				smax = s;
				row = k < n ? k : n - 1;
				col = k - row;
			}
		}
		for (i = row, j = col, len = 0; i >= 0 && j < n; j++, i--, len++) {
			printf("%d ", m[i][j]);
		}
		printf("\b, %d\n", len);


		for (i = 0; i < n; i++)
			free(*(m + i));
		free(m);
	}
}