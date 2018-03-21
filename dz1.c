#include <stdio.h>
#include <math.h>

#define MAX 100

void printArray(char arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void complement(char a[], int n) {
	char t = 0;		//oznacava da li smo naisli na '1' sa desne strane
	for (int i = n - 1; i >= 0; i--) {
		if (!t) {
			if (a[i]) {
				t = 1;
			}
		}
		else {
			a[i] = (a[i]) ? 0 : 1;
		}
	}
}

//racuna vrednost celog broja
int calculate(char a[], int n) {
	int val = 0;
	char b[MAX], c = 0;		//c ima vrednost 0 ako broj nije komplementiran, tj. ako je pozitivan
	
	for (int i = 0; i < n; i++) b[i] = a[i];

	if (b[0]) {
		complement(b, n);
		c = 1;
		printf("%10s", "b_kompl: ");
		printArray(b, n);
	}

	for (int i = 0; i < n; i++) {
		if (b[i]) {
			val += pow(2, (n - i - 1));
		}
	}

	return c ? -val : val;
}

//formira niz dst dobijen pomeranjem niza src duzine n za k mesta ulevo
void shiftLeft(char src[], char dst[], int n, int k) {
	for (int i = k; i < n; i++) {
		dst[i - k] = src[i];
	}
	for (int i = (n > k) ? (n - k) : 0 ; i < n; i++) {
		dst[i] = 0;
	}
}

//formira niz dst dobijen pomeranjem niza src duzine n za k mesta udesno
void shiftRight(char arr[], char dst[], int n, int k) {
	char c = arr[0];	//cifra koja se dodaje na k bitova najvece duzine, 0 za pozitivne brojeve, 1 za negativne
	for (int i = n - k; i >= 0; i--) {
		dst[i + k] = arr[i];
	}
	for (int i = 0; i < k && i < n; i++) {		//uslov i < n, za slucaj da je k > n
		dst[i] = c;
	}
}

int main() {
	char a[MAX], b[MAX];
	int n, val;

	while (1) {
		printf("Unesite duzinu niza: ");
		scanf("%d", &n);

		if (n <= 0 || n > MAX) break;

		for (int i = 0; i < n; i++) scanf("%d", &a[i]);

		int s;
		printf("Shift za: ");
		scanf("%d", &s);

		if (s > 0) {
			//printf("shifting right... %d\n", s);
			shiftRight(a, b, n, s);
		}
		else {
			//printf("shifting left... %d\n", s);
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
