#include "dz5.h"

/* Priprema datoteku za obradu (cita n redova jer ne sadrze podatke o pesmama, ovde, za ASX format preskacemo prva 2 reda). */
void initFile(FILE *stream, int n) {
	//fscanf(stream, "%*[^\n]\n");	// radi samo ako je 1 red teksta i jedan prazan
	char ignore[1024];
	for (int i = 0; i < n; i++)
		fgets(ignore, sizeof(ignore), stream);
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