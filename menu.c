#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "people.h"
#include "index.h"
#include "file.h"

static char green[11] = "\033[0;32m";
static char yellow[11] = "\033[0;33m";
static char red[11] = "\033[0;31m";
static char blue[11] = "\033[0;34m";
static char end[8] = "\033[0m";

void menu_main(void) {
	char input;
	system("clear");

	do {
		printf("%s1%s %sLister les personnes%s\n", green, end, yellow, end);
		printf("%s2%s %sVoir le détail d'une personne%s\n", green, end, yellow, end);
		printf("%s3%s %sAjouter une personne%s\n", green, end, yellow, end);
		printf("%s4%s %sSupprimer une personne%s\n", green, end, yellow, end);
		printf("%sq%s %sQuitter%s\n", green, end, yellow, end);

		printf("%s", blue);
		input = 0;
		scanf(" %c", &input);
		printf("%s", end);

		switch (input) {
			case '1':
				menu_list();
				break;
			case '2':
				menu_show();
				break;
			case '3':
				menu_add();
				break;
			case '4':
				menu_delete();
				break;
			case 'q':
				break;
			default:
				printf("\033[0;31mCe n'est pas un choix correct !\033[0m\n\n");
				break;
		}

		if (input == 'q') {
			system("clear");
			break;
		}

		scanf("%1c[^\n]", &input);
		system("clear");
	} while (input != 'q');
}

static void menu_list(void) {
	struct people *peoples = people_get_all();
	int people_count = people_get_all_count();

	printf("\n");

	if (people_count == 0) {
		printf("\033[0;31mIl n'y a pas de personnes !\033[0m\n");
	}

	for (int i = 0; i < people_count; i++) {
		people_print(peoples[i]);
	}

	printf("\n");
}

static void menu_show(void) {
	printf("\n%sID ? ", blue);
	int id;
	scanf("%d", &id);
	printf("%s\n", end);

	struct people p = people_get(id);
	if (p.id != 0) {
		people_print_full(p);
	} else {
		printf("%sCette personne n'existe pas !%s\n", red, end);
	}

	printf("\n");
}

static void menu_add(void) {
	struct people p = {0};

	printf("\n%s", blue);

	printf("Prénom ? ");
	p.firstname = malloc(sizeof(char) * 50);
	scanf("%49s", p.firstname);

	printf("Nom ? ");
	p.lastname = malloc(sizeof(char) * 50);
	scanf("%49s", p.lastname);

	printf("Style ? ");
	p.style = malloc(sizeof(char) * 50);
	scanf("%49s", p.style);

	people_add(p);

	printf("%s✓%s\n\n", green, end);
}

static void menu_delete(void) {
	printf("\n%sID ? ", blue);

	int id;
	scanf("%d", &id);

	people_delete(id);

	printf("%s%s✓%s\n\n", end, green, end);
}

void menu_free(void) {
	file_free();
	index_free();
	people_free();
}