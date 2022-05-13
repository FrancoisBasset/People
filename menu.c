#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <menu.h>
#include "menu.h"
#include "people.h"
#include "index.h"
#include "file.h"

static MENU *menu;
static ITEM **actions;

void menu_main(void) {
	initscr();
	keypad(stdscr, TRUE);

	actions = malloc(sizeof(ITEM*) * 6);
	actions[0] = new_item("Lister les personnes", "");
	actions[1] = new_item("Voir le detail d'une personne", "");
	actions[2] = new_item("Ajouter une personne", "");
	actions[3] = new_item("Supprimer une personne", "");
	actions[4] = new_item("Quitter", "");

	menu = new_menu((ITEM**) actions);

	post_menu(menu);
	refresh();

	ITEM *current;
	int c;
	while(c = getch()) {
		switch(c) {
			case KEY_DOWN:
		        menu_driver(menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				break;
			case '\n':
				current = current_item(menu);
				int current_index = item_index(current);

				switch (current_index) {
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
				break;
		}
	}
}

static void menu_list(void) {
	move(6, 0);
	clrtobot();

	struct people *peoples = people_get_all();
	int people_count = people_get_all_count();

	if (people_count == 0) {
		mvprintw(6, 0, "Il n'y a pas de personnes !");
	}

	for (int i = 0; i < people_count; i++) {
		mvprintw(6 + i, 0, "%d, %s %s, %s\n", peoples[i].id, peoples[i].firstname, peoples[i].lastname, peoples[i].style);
	}
}

static void menu_show(void) {
	move(6, 0);
	clrtobot();

	mvprintw(6, 0, "ID ? ");
	int id;
	scanw("%d", &id);

	struct people p = people_get(id);
	if (p.id != 0) {
		mvprintw(8, 0, "ID : %d", p.id);
		mvprintw(9, 0, "Firstname : %s", p.firstname);
		mvprintw(10, 0, "Lastname : %s", p.lastname);
		mvprintw(11, 0, "Style : %s", p.style);
	} else {
		mvprintw(6, 0, "Cette personne n'existe pas !");
	}
}

static void menu_add(void) {
	move(6, 0);
	clrtobot();

	struct people p = {0};

	mvprintw(6, 0, "Prénom ? ");
	p.firstname = malloc(sizeof(char) * 50);
	scanw("%49s", p.firstname);

	mvprintw(7, 0, "Nom ? ");
	p.lastname = malloc(sizeof(char) * 50);
	scanw("%49s", p.lastname);

	mvprintw(8, 0, "Style ? ");
	p.style = malloc(sizeof(char) * 50);
	scanw("%49s", p.style);

	people_add(p);

	mvprintw(9, 0, "Personne ajoutée !");
}

static void menu_delete(void) {
	move(6, 0);
	clrtobot();

	mvprintw(6, 0, "ID ? ");

	int id;
	scanw("%d", &id);

	struct people p = people_get(id);

	if (p.id != 0) {
		people_delete(id);
		mvprintw(7, 0, "Personne %d supprimé !", id);
	} else {
		mvprintw(7, 0, "Cette personne n'existe pas !");
	}
}

void menu_free(void) {
	free_item(actions[0]);
	free_item(actions[1]);
	free_item(actions[2]);
	free_item(actions[3]);
	free_item(actions[4]);
	free_menu(menu);

	endwin();

	file_free();
	index_free();
	people_free();
}