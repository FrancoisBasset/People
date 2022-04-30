#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "utils.h"

FILE *index_file = NULL;
int i = 0;

void index_init(void) {
	char *folder_name = utils_get_people_folder_name();
	char *index_file_name = utils_get_index_file_name();

	utils_mkdir(folder_name);

	if (utils_file_exists(index_file_name) == -1) {
		index_file = fopen(index_file_name, "w");
		i = 0;
	} else {
		index_file = fopen(index_file_name, "r");
		fseek(index_file, 0, SEEK_END);
		if (ftell(index_file) == 0) {
			i = 0;
		} else {
			rewind(index_file);
			fscanf(index_file, "%d", &i);
		}

		fclose(index_file);

		index_file = fopen(index_file_name, "r+");
	}

	free(folder_name);
	free(index_file_name);
}

int index_get(void) {
	return i;
}

void index_increment() {
	i++;

	rewind(index_file);

	fprintf(index_file, "%d", i);
}

void index_end(void) {
	fclose(index_file);
}