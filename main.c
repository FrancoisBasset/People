#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "index.h"
#include "file.h"
#include "people.h"

int main(void) {
	char *firstnames[6] = {"François", "Charles", "Louis", "Philippe", "Robert", "Henri"};
	char *lastnames[6] = {"Bonaparte", "Le Gros", "Le Bref", "Le Bon", "Le Chauve", "Capet"};
	char *styles[6] = {"Trance", "Trance Goa", "Psytrance", "Hardstyle", "Hardcore", "Terrorcore"};
	srand(time(NULL));
	for (int i = 0; i < 10000; i++) {
		struct people p = {};

		char *f = firstnames[rand() % 6];
		p.firstname = malloc(sizeof(char) * (strlen(f) + 1));
		strcpy(p.firstname, f);

		char *l = lastnames[rand() % 6];
		p.lastname = malloc(sizeof(char) * (strlen(l) + 1));
		strcpy(p.lastname, l);

		char *s = styles[rand() % 6];
		p.style = malloc(sizeof(char) * (strlen(s) + 1));
		strcpy(p.style, s);

		people_add(p);
	}

	struct people *peoples = people_get_all();
	int people_count = people_get_all_count();

	for (int i = 0; i < people_count; i++) {
		people_print(peoples[i]);
	}

	file_free();
	index_free();
	people_free();
}