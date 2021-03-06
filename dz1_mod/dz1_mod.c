#include <stdio.h>
#include <math.h>

#define MAX 100

void printArray(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void complement(int a[], int n) {
	char t = 0;		// oznacava da li smo naisli na '1' sa desne strane
	for (int i = n - 1; i >= 0; i--) {
		if (!t) {	// ako jos nije bilo jedinice, nista se ne menja
			if (a[i]) {		// ako je trenutno jedinica
				t = 1;		// pamtimo da smo dosli do nje
			}
		}
		else {		// kad se prodje jedna jedinica, svi biti se komplementiraju
			a[i] = (a[i]) ? 0 : 1;
		}
	}
}

// racuna vrednost celog broja, cija je predstava niz a
int calculate(int a[], int n) {
	int val = 0;
	char c = 0;		// c ima vrednost 0 ako broj nije komplementiran, tj. ako je pozitivan

	if (a[0]) {
		complement(a, n);
		c = 1;
		printf("%10s", "b_kompl: ");
		printArray(a, n);
	}

	for (int i = 0; i < n; i++) {
		if (a[i]) {
			val += pow(2, (n - i - 1));
		}
	}

	return c ? -val : val;
}

// formira niz dst dobijen pomeranjem niza src duzine n za k mesta ulevo
void shiftLeft(int src[], int dst[], int n, int k) {
	for (int i = k; i < n; i++) {
		dst[i - k] = src[i];
	}
	for (int i = (n > k) ? (n - k) : 0; i < n; i++) {
		dst[i] = 0;
	}
}

// formira niz dst dobijen pomeranjem niza src duzine n za k mesta udesno
void shiftRight(int arr[], int dst[], int n, int k) {
	char c = arr[0];	// cifra koja se dodaje na k bitova najvece duzine, 0 za pozitivne brojeve, 1 za negativne
	for (int i = n - k - 1; i >= 0; i--) {
		dst[i + k] = arr[i];
	}
	for (int i = 0; i < k && i < n; i++) {		// uslov i < n, za slucaj da je k > n
		dst[i] = c;
	}
}

// sortira niz a duzine n rastuce ili opadajuce u zavisnosti od parametra k
void sort(int a[], int n, int k) {
	char t;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (k) {	// rastuci (neopadajuci) poredak
				if (a[j] < a[i]) {
					t = a[i];
					a[i] = a[j];
					a[j] = t;
				}
			}
			else {		// opadajuci (nerastuci) poredak
				if (a[j] > a[i]) {
					t = a[i];
					a[i] = a[j];
					a[j] = t;
				}
			}
		}
	}
}

int main() {
	int a[MAX], b[MAX], k;	// a je pocetni niz, b je novi niz dobijen pomeranjem niza a, k je kriterijum sortiranja
	int n, val, i, s;		// n - broj elemenata niza, val - vrednost broja cija je predstava niz b, s - broj mesta za koje se pomera

	while (1) {
		printf("Unesite duzinu niza: ");
		scanf("%d", &n);

		if (n <= 0 || n > MAX) break;

		for (i = 0; i < n; i++) scanf("%d", &a[i]);

		printf("Kriterijum sortiranja (0 za opadajuci ili 1 za rastuci): ");
		scanf("%d", &k);

		sort(a, n, k);

		printf("%10s", "a: ");
		printArray(a, n);		// sortiran pocetni broj

		printf("Shift za: ");
		scanf("%d", &s);

		if (s > 0) {
			shiftRight(a, b, n, s);
		}
		else {
			shiftLeft(a, b, n, -s);
		}

		printf("%10s", "a: ");
		printArray(a, n);		// pocetni broj
		printf("%10s", "b: ");
		printArray(b, n);		// pomeren broj

		val = calculate(b, n);
		printf("%d\n", val);	// vrednost pomerenog broja
	}
}
