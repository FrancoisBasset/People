#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "utils.h"

char *utils_get_username(void) {
	FILE *output = popen("whoami", "r");
	char *username = malloc(sizeof(char) * 50);

	fscanf(output, "%50s", username);

	fclose(output);

	return username;
}

char *utils_get_people_folder_name() {
	char *username = utils_get_username();

	int folder_name_length = 15 + strlen(username);

	char *folder_name = malloc(sizeof(char) * folder_name_length);

	strcpy(folder_name, "/home/");
	strcat(folder_name, username);
	strcat(folder_name, "/.people");

	free(username);

	return folder_name;
}

char *utils_get_index_file_name() {
	char *folder_name = utils_get_people_folder_name();

	int index_filename_length = strlen(folder_name) + 7;
	char *index_file_name = malloc(sizeof(char) * index_filename_length);

	strcpy(index_file_name, folder_name);
	strcat(index_file_name, "/index");

	free(folder_name);

	return index_file_name;
}

char *utils_get_people_file_name() {
	char *folder_name = utils_get_people_folder_name();

	int people_filename_length = strlen(folder_name) + 8;
	char *people_file_name = malloc(sizeof(char) * people_filename_length);

	strcpy(people_file_name, folder_name);
	strcat(people_file_name, "/people");

	free(folder_name);

	return people_file_name;
}

void utils_mkdir(char *folder_name) {
	struct stat st = {0};

	if (stat(folder_name, &st) == -1) {
		mkdir(folder_name, 0777);
	}
}

int utils_file_exists(char *file_name) {
	return access(file_name, F_OK);
}