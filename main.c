#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "index.h"
#include "file.h"
#include "people.h"

void main_free() {

}

int main(void) {
	index_init();
	file_init();

	char *styles[5] = {"Trance", "Psytrance", "Hardstyle", "Hardcore", "Terrorcore"};
	srand(time(NULL));

	struct people p1 = { .firstname = "François", .lastname = "Basset", .style = styles[rand() % 5] };

	file_add_people(p1);

	printf("Ajout %s:::%s:::%s\n", p1.firstname, p1.lastname, p1.style);

	struct people *peoples = file_get_all_people();

	file_delete_people(11);
	file_delete_people(13);
	file_delete_people(15);

	int people_count = file_get_all_people_count();
	printf("Nombre d'éléments : %d\n", people_count);

	for (int i = 0; i < people_count; i++) {
		printf("%d:::%s:::%s:::%s\n", peoples[i].id, peoples[i].firstname, peoples[i].lastname, peoples[i].style);
	}

	for (int i = 0; i < people_count; i++) {
		free(peoples[i].firstname);
		free(peoples[i].lastname);
		free(peoples[i].style);
	}

	free(peoples);

	file_free();
	index_free();
}