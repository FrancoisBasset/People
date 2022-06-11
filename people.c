#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "people.h"
#include "file.h"
#include "index.h"

struct people *peoples = NULL;
int people_count = -1;
int people_max_count = -1;

void people_init(void) {
	char **lines = file_get_all_lines();
	int lines_count = file_get_all_lines_count();

	people_count = lines_count;
	people_max_count = lines_count * 2 > 10 ? lines_count * 2 : 10;
	peoples = malloc(sizeof(struct people) * people_max_count);

	int id = 0;
	char *firstname = malloc(sizeof(char) * 50);
	char *lastname = malloc(sizeof(char) * 50);
	char *style = malloc(sizeof(char) * 50);

	for (int i = 0; i < lines_count; i++) {
		sscanf(lines[i], "%d:::%50[^:::]:::%50[^:::]:::%50s\n", &id, firstname, lastname, style);
		free(lines[i]);

		struct people p = {};
		p.id = id;

		p.firstname = malloc(sizeof(char) * (strlen(firstname) + 1));
		strcpy(p.firstname , firstname);

		p.lastname = malloc(sizeof(char) * (strlen(lastname) + 1));
		strcpy(p.lastname , lastname);

		p.style = malloc(sizeof(char) * (strlen(style) + 1));
		strcpy(p.style , style);

		peoples[i] = p;
	}

	free(lines);

	free(firstname);
	free(lastname);
	free(style);
}

struct people* people_get_all(void) {
	if (peoples == NULL) {
		people_init();
	}

	return peoples;
}

int people_get_all_count(void) {
	if (peoples == NULL) {
		people_init();
	}

	return people_count;
}

struct people people_get(int id) {
	if (peoples == NULL) {
		people_init();
	}

	for (int i = 0; i < people_count; i++) {
		if (peoples[i].id == id) {
			return peoples[i];
		}
	}

	return (struct people) {};
}

void people_add(struct people p) {
	if (peoples == NULL) {
		people_init();
	}

	if (people_count == people_max_count) {
		people_max_count *= 2;

		struct people *new_peoples = malloc(sizeof(struct people) * people_max_count);

		for (int i = 0; i < people_count; i++) {
			new_peoples[i] = peoples[i];
		}

		free(peoples);

		peoples = new_peoples;
	}

	p.id = index_get() + 1;

	peoples[people_count] = p;
	people_count++;

	file_write_people(p);
}

void people_delete(int id) {
	if (peoples == NULL) {
		people_init();
	}

	int item_removed = 0;
	int j = 0;
	for (int i = 0; i < people_count; i++) {
		if (peoples[i].id == id) {
			free(peoples[i].firstname);
			free(peoples[i].lastname);
			free(peoples[i].style);

			j = i + 1;
			item_removed = 1;
		}

		if (item_removed == 1) {
			peoples[i] = peoples[j];
			j++;
		}
	}

	if (item_removed == 1) {
		people_count--;

		file_write_peoples(peoples, people_count);
	}
}

void people_free(void) {
	for (int i = 0; i < people_count; i++) {
		free(peoples[i].firstname);
		free(peoples[i].lastname);
		free(peoples[i].style);
	}

	free(peoples);
}
