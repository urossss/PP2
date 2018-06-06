#include "spiskovi.h"

/* Ispisuje odgovarajucu poruku o gresci i prekida izvrsavanje programa. */
void error(int e) {
	switch (e) {
	case 1:
		fprintf(stderr, "Error in allocation!\n");
		break;
	case 2:
		fprintf(stderr, "Error opening files!\n");
		break;
	case 3:
		fprintf(stderr, "Not enough commad line arguments!\n");
		break;
	}
	exit(e);
}

/* Ispisuje trenutno vreme. */
void printCurrentTime() {
	time_t pIntTime = time(NULL);
	struct tm* currentLocalTime = localtime(&pIntTime);
	char timeString[11];
	if (currentLocalTime) {
		strftime(timeString, 10, "%H:%M:%S", currentLocalTime);
		puts(timeString);
	}
}
