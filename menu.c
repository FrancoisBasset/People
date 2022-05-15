#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "menu.h"
#include "people.h"
#include "index.h"
#include "file.h"

#define GREEN COLOR_PAIR(1)
#define RED COLOR_PAIR(2)
#define BLUE COLOR_PAIR(3)

void menu_main(void) {
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_BLUE, COLOR_BLUE);

	int index = 0;
	char *items[5] = { "Lister les personnes         ", "Voir le detail d'une personne", "Ajouter une personne         ", "Supprimer une personne       ", "Quitter                      " };

	attron(BLUE);
	mvprintw(0, 0, "                                 ");
	mvprintw(1, 0, "  ");
	mvprintw(1, 31, "  ");
	mvprintw(2, 0, "  ");
	mvprintw(2, 31, "  ");
	mvprintw(3, 0, "  ");
	mvprintw(3, 31, "  ");
	mvprintw(4, 0, "  ");
	mvprintw(4, 31, "  ");
	mvprintw(5, 0, "  ");
	mvprintw(5, 31, "  ");
	mvprintw(6, 0, "                                 ");
	attroff(BLUE);

	attron(GREEN);
	mvprintw(1, 2, "%s", items[0]);
	attroff(GREEN);
	mvprintw(2, 2, "%s", items[1]);
	mvprintw(3, 2, "%s", items[2]);
	mvprintw(4, 2, "%s", items[3]);
	mvprintw(5, 2, "%s", items[4]);

	move(index, 0);

	int c;
	while (c = getch()) {
		switch(c) {
			case KEY_DOWN:
				if (index < 4) {
					mvprintw(index + 1, 2, items[index]);
					index++;
					attron(GREEN);
					mvprintw(index + 1, 2, "%s", items[index]);
					attroff(GREEN);
					move(index + 1, 0);
				}
				break;
			case KEY_UP:
				if (index > 0) {
					mvprintw(index + 1, 2, items[index]);
					index--;
					attron(GREEN);
					mvprintw(index + 1, 2, "%s", items[index]);
					attroff(GREEN);
					move(index + 1, 0);
				}
				break;
			case '\n':
				move(8, 0);
				clrtobot();
				attron(RED);
				mvprintw(index + 1, 2, "%s", items[index]);
				attroff(RED);
				keypad(stdscr, FALSE);
				echo();

				switch (index) {
					case 0:
						menu_list();
						break;
					case 1:
						menu_show();
						break;
					case 2:
						menu_add();
						break;
					case 3:
						menu_delete();
						break;
					case 4:
						endwin();
						return;
						break;
				}

				noecho();
				keypad(stdscr, TRUE);
				attron(GREEN);
				mvprintw(index + 1, 2, "%s", items[index]);
				attroff(GREEN);

				break;
		}
	}
}

static void menu_list(void) {
	struct people *peoples = people_get_all();
	int people_count = people_get_all_count();

	if (people_count == 0) {
		mvprintw(8, 0, "Il n'y a pas de personnes !");
	}

	for (int i = 0; i < people_count; i++) {
		mvprintw(8 + i, 0, "%d, %s %s, %s\n", peoples[i].id, peoples[i].firstname, peoples[i].lastname, peoples[i].style);
	}
}

static void menu_show(void) {
	mvprintw(8, 0, "ID ? ");
	int id;
	scanw("%d", &id);

	struct people p = people_get(id);
	if (p.id != 0) {
		mvprintw(10, 0, "ID : %d", p.id);
		mvprintw(11, 0, "Firstname : %s", p.firstname);
		mvprintw(12, 0, "Lastname : %s", p.lastname);
		mvprintw(13, 0, "Style : %s", p.style);
	} else {
		mvprintw(10, 0, "Cette personne n'existe pas !");
	}
}

static void menu_add(void) {
	struct people p = {0};

	mvprintw(8, 0, "Prénom ? ");
	p.firstname = malloc(sizeof(char) * 50);
	scanw("%49s", p.firstname);

	mvprintw(9, 0, "Nom ? ");
	p.lastname = malloc(sizeof(char) * 50);
	scanw("%49s", p.lastname);

	mvprintw(10, 0, "Style ? ");
	p.style = malloc(sizeof(char) * 50);
	scanw("%49s", p.style);

	people_add(p);

	mvprintw(11, 0, "Personne ajoutée !");
}

static void menu_delete(void) {
	mvprintw(8, 0, "ID ? ");

	int id;
	scanw("%d", &id);

	struct people p = people_get(id);

	if (p.id != 0) {
		people_delete(id);
		mvprintw(8, 0, "Personne %d supprimé !", id);
	} else {
		mvprintw(8, 0, "Cette personne n'existe pas !");
	}
}

void menu_free(void) {
	endwin();

	file_free();
	index_free();
	people_free();
}