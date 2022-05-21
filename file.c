#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/index.h"
#include "headers/utils.h"
#include "headers/people.h"

FILE *people_file = NULL;
int lines_count = 0;

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

char **file_get_all_lines(void) {
	if (people_file == NULL) {
		file_init();
	}

	rewind(people_file);

	while (!feof(people_file)) {
		if (fgetc(people_file) == '\n') {
			lines_count++;
		}
	}

	char **lines = malloc(sizeof(char*) * lines_count);
	char *line = malloc(sizeof(char) * 100);

	rewind(people_file);

	int i = 0;
	while (fscanf(people_file, "%100[^\n]\n", line) != EOF) {
		lines[i] = malloc(sizeof(char) * (strlen(line) + 10));
		strcpy(lines[i], line);

		i++;
	}

	free(line);

	return lines;
}

int file_get_all_lines_count(void) {
	if (people_file == NULL) {
		file_init();
	}

	return lines_count;
}

void file_write_people(struct people p) {
	if (people_file == NULL) {
		file_init();
	}

	fseek(people_file, 0, SEEK_END);
	index_increment();
	fprintf(people_file, "%d:::%s:::%s:::%s\n", index_get(), p.firstname, p.lastname, p.style);
}

void file_write_peoples(struct people *peoples, int people_count) {
	if (people_file == NULL) {
		file_init();
	}

	lines_count = people_count;

	fclose(people_file);
	char *people_file_name = utils_get_people_file_name();
	people_file = fopen(people_file_name, "w");

	for (int i = 0; i < people_count; i++) {
		fprintf(people_file, "%d:::%s:::%s:::%s\n", peoples[i].id, peoples[i].firstname, peoples[i].lastname, peoples[i].style);
	}

	free(people_file_name);
}

void file_free(void) {
	if (people_file != NULL) {
		fclose(people_file);
	}
}