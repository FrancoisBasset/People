#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "utils.h"
#include "people.h"

FILE *people_file = NULL;
struct people *peoples = NULL;
int people_count = 0;
int people_max_count = 0;

void file_init(void) {
	char *folder_name = utils_get_people_folder_name();
	char *people_file_name = utils_get_people_file_name();

	utils_mkdir(folder_name);

	if (utils_file_exists(people_file_name) == -1) {
		people_file = fopen(people_file_name, "w");
		fclose(people_file);
	}

	people_file = fopen(people_file_name, "r+");

	free(folder_name);
	free(people_file_name);
}

struct people* file_get_all_people(void) {
	if (peoples != NULL) {
		return peoples;
	}

	rewind(people_file);

	int count = 0;
	while (!feof(people_file)) {
		if (fgetc(people_file) == '\n') {
			count++;
		}
	}

	people_max_count = count * 2;
	peoples = malloc(sizeof(struct people) * people_max_count);

	int id = 0;
	char *firstname = malloc(sizeof(char) * 50);
	char *lastname = malloc(sizeof(char) * 50);
	char *style = malloc(sizeof(char) * 50);

	rewind(people_file);
	while (fscanf(people_file, "%d:::%50[^:::]:::%50[^:::]:::%50s\n", &id, firstname, lastname, style) != EOF) {
		struct people p = {};
		p.id = id;
		p.firstname = malloc(sizeof(char) * (strlen(firstname) + 1));
		strcpy(p.firstname , firstname);

		p.lastname = malloc(sizeof(char) * (strlen(lastname) + 1));
		strcpy(p.lastname , lastname);

		p.style = malloc(sizeof(char) * (strlen(style) + 1));
		strcpy(p.style , style);

		peoples[people_count] = p;

		people_count++;
	}

	free(firstname);
	free(lastname);
	free(style);

	return peoples;
}

struct people file_get_people(int id) {
	for (int i = 0; i < people_count; i++) {
		if (peoples[i].id == id) {
			return peoples[i];
		}
	}

	return (struct people) {};
}

int file_get_all_people_count(void) {
	return people_count;
}

void file_add_people(struct people p) {
	fseek(people_file, 0, SEEK_END);
	index_increment();
	fprintf(people_file, "%d:::%s:::%s:::%s\n", index_get(), p.firstname, p.lastname, p.style);
}

void file_delete_people(int id) {
	int item_removed = 0;
	int j = -1;
	for (int i = 0; i < people_count; i++) {
		if (peoples[i].id == id) {
			free(peoples[i].firstname);
			free(peoples[i].lastname);
			free(peoples[i].style);

			j = i + 1;

			item_removed = 1;
		}

		if (j != -1) {
			peoples[i] = peoples[j];

			j++;
		}
	}

	if (item_removed) {
		people_count--;

		fclose(people_file);
		char *people_file_name = utils_get_people_file_name();
		people_file = fopen(people_file_name, "w");

		for (int i = 0; i < people_count; i++) {
			fprintf(people_file, "%d:::%s:::%s:::%s\n", peoples[i].id, peoples[i].firstname, peoples[i].lastname, peoples[i].style);
		}

		free(people_file_name);
	}
}

void file_free(void) {
	fclose(people_file);
}