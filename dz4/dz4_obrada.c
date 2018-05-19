#include "dz4.h"

void swap(Person *a, Person *b) {
	Person p = *a;
	*a = *b;
	*b = p;
}

/* Sortira listu glasaca po mestu stanovanja, pa po leksikografskom pretku. */
void sort(List lst) {
	Elem *i, *j;
	for (i = lst.first; i; i = i->next)
		for (j = i->next; j; j = j->next) {
			int x = strcmp(i->person->city, j->person->city);
			if (x > 0) {
				swap(i->person, j->person);
			}
			else if (x == 0) {
				x = strcmp(i->person->surname, j->person->surname);
				if (x > 0) {
					swap(i->person, j->person);
				}
				else if (x == 0) {
					x = strcmp(i->person->name, j->person->name);
					if (x > 0) {
						swap(i->person, j->person);
					}
				}
			}
		}
}

/* Oslobadjanje prostora jednog glasaca. */
void deletePerson(Person *p) {
	free(p->name);
	free(p->surname);
	free(p->id);
	free(p->city);
	free(p->voting);
	free(p);
}

/* Brisanje liste. */
void deleteList(List *plst) {
	Elem *curr = plst->first, *old;
	while (curr) {
		old = curr;
		curr = curr->next;
		deletePerson(old->person);
		free(old);
	}
	plst->first = plst->last = NULL;
}

/* Izbacuje iz liste osobu sa zadatim JMBGom. */
void removePerson(List *plst, char *id) {
	Elem *curr = plst->first, *prev = NULL, *old;
	while (curr) {
		if (strcmp(curr->person->id, id)) {
			prev = curr;
			curr = curr->next;
		}
		else {
			old = curr;
			curr = curr->next;
			if (!prev)
				plst->first = curr;
			else
				prev->next = curr;
			if (!curr)
				plst->last = prev;
			deletePerson(old->person);
			free(old);
		}
	}
}

/* Rasporedjuje glasace po birackim mestima.
Pretpostavlja se da je lista uredjena po mestu stanovanja. */
void assignVoters(List lst) {
	int n, i, x, len;
	char *s;
	printf("Unesite kapacitet birackog mesta: ");
	scanf("%d", &n);

	Elem *curr = lst.first, *prev = NULL;
	i = 0;
	x = 1;
	while (curr) {
		if (i == n) {	// ispunjen je kapacitet jednog birackog mesta
			x++;
			i = 0;
		}
		if (prev && strcmp(prev->person->city, curr->person->city)) {
			x = 1;
			i = 0;
		}
		
		len = snprintf(NULL, 0, "%s %d", curr->person->city, x);
		s = malloc((len + 1) * sizeof(*s));
		snprintf(s, len + 1, "%s %d", curr->person->city, x);

		curr->person->voting = s;
		i++;
		prev = curr;
		curr = curr->next;
	}
}
