#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void error() {
	printf("Error in allocation!\n");
	exit(1);
}

char* readLine() {
	int len = 1;
	char *s = NULL, c;
	while ((c = getchar()) != '\n') {	// do kraja reda
		s = (char *)realloc(s, ++len);
		if (s == NULL) error();
		*(s + len - 2) = c;
	}
	if (s == NULL) return s;
	*(s + len - 1) = '\0';
	return s;
}

void printStrings(char **str, int n) {
	for (int i = 0; i < n; i++) {
		puts(*(str + i));
	}
}

void replace(char *s, char *curr1, char *curr2, char *rate) {
	char *t, *num1, *num2;
	double val1, val2;
	int i, len1, len2, diff, cnt, ind1, ind2;

	t = s;
	cnt = 0;
	while (*t) {
		if (isdigit(*t)) {	// ako se naidje na cifru
			num1 = t;
			val1 = strtod(t, &t);
			len1 = t - num1;	// broj slova koje je zauzimao broj u originalnom stringu
			ind1 = num1 - s;	// index na kom pocinje broj u stringu
			if (t - s >= strlen(s) - 1) break;	// ako posle broja nema vise reci
			if (*t != ' ') {	// ako nakon broja nije razmak, tj. broj je deo neke reci
				t++;
			}
			else {
				t++;
				i = 0;
				while (t - s < strlen(s) && *t == *(curr1 + i) && i < strlen(curr1)) {	// provera da li posle broja sledi druga valuta
					t++;
					i++;
				}
				if (i == strlen(curr1) && (t - s == strlen(s) || *t == ' ')) {	// vrsi se odgovarajuca zamena
					num2 = NULL;
					val2 = val1 * atof(rate);
					int len = 1;
					do {
						num2 = realloc(num2, ++len);
						if (num2 == NULL) error();
						len2 = sprintf(num2, "%lg", val2);
					} while (len2 < 0);

					diff = len2 - len1 + strlen(curr2) - strlen(curr1);

					ind2 = t - s;

					if (diff <= 0) {
						for (i = ind1; i < strlen(s) + diff; i++) {
							if (i - ind1 < len2)
								*(s + i) = *(num2 + i - ind1);
							else if (i - ind1 == len2)
								*(s + i) = ' ';
							else if (i - ind1 < len2 + 1 + strlen(curr2))
								*(s + i) = *(curr2 + i - ind1 - len2 - 1);
							else
								*(s + i) = *(s + i - diff);
						}
						*(s + i) = '\0';

						if (diff < 0) {	// ako je duzina stringa smanjena, vrismo realokaciju da odbacimo nepotrebni prostor
							cnt = t - s + diff;
							s = realloc(s, strlen(s) + 1);
							if (s == NULL) error();
							t = s + cnt;	// jer se posle realokacije s ne mora nalaziti na istoj lokaciji
						}
					}
					else {	// diff > 0
						cnt = t - s + diff;
						s = realloc(s, strlen(s) + 1 + diff);
						if (s == NULL) error();
						t = s + cnt;	// jer se posle realokacije s ne mora nalaziti na istoj lokaciji
						
						*(s + strlen(s) + diff) = '\0';

						for (i = strlen(s) - 1; i >= ind2; i--) {
							*(s + i + diff) = *(s + i);
						}
						for (i = ind1; i < ind2 + diff; i++) {
							if (i - ind1 < len2)
								*(s + i) = *(num2 + i - ind1);
							else if (i - ind1 == len2)
								*(s + i) = ' ';
							else	//if (i - ind1 < len2 + 1 + strlen(curr2))
								*(s + i) = *(curr2 + i - ind1 - len2 - 1);
						}
					}
				}
			}
		}
		else {
			t++;
		}
	}
}

int main() {
	char **str, *s, *tmp, *curr1, * curr2, *rate;
	int n, end, i;

	while (1) {	// dok se ne unese "dosta Brus Li"
		n = end = 0;
		str = NULL;
		while (1) {	// dok se ne unese prazan red
			s = readLine();
			if (s == NULL) break;	// ako je unet prazan red

			if (!strcmp(s, "dosta Brus Li")) {
				end = 1;
				break;
			}

			str = realloc(str, (++n) * sizeof(*str));
			if (str == NULL) error();
			*(str + n - 1) = s;
		}

		if (end) break;

		printStrings(str, n);

		tmp = readLine();
		if (tmp == NULL) exit(2);
		curr1 = strtok(tmp, " ");
		curr2 = strtok(NULL, " ");
		rate = strtok(NULL, " ");

		for (i = 0; i < n; i++) {
			replace(*(str + i), curr1, curr2, rate);
		}

		printStrings(str, n);

		for (i = 0; i < n; i++) {
			free(*(str + i));
		}
		if (str != NULL) free(str);
	}
}