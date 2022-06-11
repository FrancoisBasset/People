#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "curses.h"
#include "people.h"
#include "index.h"
#include "file.h"

#define GREEN COLOR_PAIR(1)
#define RED COLOR_PAIR(2)
#define BLUE COLOR_PAIR(3)

int max_v = 0;
int max_h = 0;
int begin_h = 0;
int begin_v = 0;

void menu_main(void) {
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_GREEN);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_BLUE, COLOR_BLUE);

	getmaxyx(stdscr, max_v, max_h);
	begin_h = (max_h - 33) / 2;
	begin_v = (max_v - 8) / 2;

	int index = 0;
	char *items[5] = { "Lister les personnes         ", "Voir le detail d'une personne", "Ajouter une personne         ", "Supprimer une personne       ", "Quitter                      " };

	attron(BLUE);
	mvprintw(begin_v, begin_h, "                                 ");
	mvprintw(begin_v + 1, begin_h, "  ");
	mvprintw(begin_v + 1, begin_h + 31, "  ");
	mvprintw(begin_v + 2, begin_h, "  ");
	mvprintw(begin_v + 2, begin_h + 31, "  ");
	mvprintw(begin_v + 3, begin_h, "  ");
	mvprintw(begin_v + 3, begin_h + 31, "  ");
	mvprintw(begin_v + 4, begin_h, "  ");
	mvprintw(begin_v + 4, begin_h + 31, "  ");
	mvprintw(begin_v + 5, begin_h, "  ");
	mvprintw(begin_v + 5, begin_h + 31, "  ");
	mvprintw(begin_v + 6, begin_h, "                                 ");
	attroff(BLUE);

	attron(GREEN);
	mvprintw(begin_v + 1, begin_h + 2, "%s", items[0]);
	attroff(GREEN);
	mvprintw(begin_v + 2, begin_h + 2, "%s", items[1]);
	mvprintw(begin_v + 3, begin_h + 2, "%s", items[2]);
	mvprintw(begin_v + 4, begin_h + 2, "%s", items[3]);
	mvprintw(begin_v + 5, begin_h + 2, "%s", items[4]);

	move(begin_v + index, begin_h);

	int c;
	while (c = getch()) {
		switch(c) {
			case KEY_DOWN:
				if (index < 4) {
					mvprintw(begin_v + index + 1, begin_h + 2, items[index]);
					index++;
					attron(GREEN);
					mvprintw(begin_v + index + 1, begin_h + 2, "%s", items[index]);
					attroff(GREEN);
					move(begin_v + index + 1, begin_h);
				}
				break;
			case KEY_UP:
				if (index > 0) {
					mvprintw(begin_v + index + 1, begin_h + 2, items[index]);
					index--;
					attron(GREEN);
					mvprintw(begin_v + index + 1, begin_h + 2, "%s", items[index]);
					attroff(GREEN);
					move(begin_v + index + 1, begin_h);
				}
				break;
			case '\n':
				move(begin_v + 7, begin_h);
				clrtobot();
				attron(RED);
				mvprintw(begin_v + index + 1, begin_h + 2, "%s", items[index]);
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
				mvprintw(begin_v + index + 1, begin_h + 2, "%s", items[index]);
				attroff(GREEN);

				break;
		}
	}
}

static void menu_list(void) {
	struct people *peoples = people_get_all();
	int people_count = people_get_all_count();

	if (people_count == 0) {
		mvprintw(begin_v + 8, begin_h, "Il n'y a pas de personnes !");
	} else {
		int max_length = 0;
		for (int i = 0; i < people_count; i++) {
			char *s = malloc(sizeof(char) * 200);
			sprintf(s, "%d, %s %s, %s", peoples[i].id, peoples[i].firstname, peoples[i].lastname, peoples[i].style);

			if (max_length < strlen(s)) {
				max_length = strlen(s);
			}
		}

		int h = (max_h - max_length) / 2;
		int v = (max_v - (begin_v + 8)) / 2;
		v--;

		if (people_count > v) {
			max_length++;
		}

		attron(BLUE);
		for (int i = -2; i <= max_length; i++) {
			mvprintw(begin_v + 8, h + i, "  ");
			mvprintw(begin_v + 8 + v + 1, h + i, "  ");
		}
		for (int i = 0; i <= v; i++) {
			mvprintw(begin_v + 8 + i, h - 2, "  ");
			mvprintw(begin_v + 8 + i, h + max_length, "  ");
		}
		attroff(BLUE);

		int index = 0;
		int scroll_index = 0;
		int c = 0;
		set_escdelay(0);
		keypad(stdscr, TRUE);
		noecho();

		char *blank = calloc(max_length + 1, sizeof(char));
		memset(blank, ' ', sizeof(char) * max_length);

		do {
			switch (c) {
				case KEY_DOWN:
					if (index < people_count && index + v < people_count) {
						index++;
					}
					break;
				case KEY_UP:
					if (index > 0) {
						index--;
					}
					break;
			}

			for (int i = 0; i < v; i++) {
				if (index + i < people_count) {
					mvprintw(begin_v + 9 + i, h, blank);
					mvprintw(begin_v + 9 + i, h, "%d, %s %s, %s", peoples[index + i].id, peoples[index + i].firstname, peoples[index + i].lastname, peoples[index + i].style);
				}
			}

			int last = people_count - v;

			if (index == 0) scroll_index = 0;
			else if (index == last) scroll_index = v - 1;
			else {
				scroll_index = (index / v) + 1;
				double d = (double) index / (double) v;
				if (d > 1 / (double) v) {
					scroll_index++;
				}
				if (scroll_index >= v - 1) scroll_index = v - 2;
			}

			attron(GREEN);
			if (last > 0) {
				mvprintw(begin_v + 9 + scroll_index, h + max_length - 1, " ");
			}
			attroff(GREEN);
		} while ((c = getch()) != 27);
	}
}

static void menu_show(void) {
	mvprintw(begin_v + 8, begin_h, "ID ? ");

	keypad(stdscr, TRUE);
	set_escdelay(0);
	char c;

	char *id = calloc(10, sizeof(char));
	do {
		noecho();
		c = getch();
		echo();
		if (c >= 48 && c<= 57) {
			printw("%c", c);
			char s[2] = { c, '\0' };
			strcat(id, s);
		} else if (c == 27) {
			free(id);
			return;
		}
	} while (c != '\n');

	struct people p = people_get(atoi(id));
	if (p.id != 0) {
		mvprintw(begin_v + 10, begin_h, "ID : %d", p.id);
		mvprintw(begin_v + 11, begin_h, "Firstname : %s", p.firstname);
		mvprintw(begin_v + 12, begin_h, "Lastname : %s", p.lastname);
		mvprintw(begin_v + 13, begin_h, "Style : %s", p.style);
	} else {
		mvprintw(begin_v + 10, begin_h, "Cette personne n'existe pas !");
	}
}

static void menu_add(void) {
	struct people p = {0};

	keypad(stdscr, TRUE);
	set_escdelay(0);
	char c;

	mvprintw(begin_v + 8, begin_h, "Prénom ? ");
	p.firstname = calloc(50, sizeof(char));
	do {
		noecho();
		c = getch();
		echo();
		if ((c >= 65 && c<= 90) || (c >= 97 && c <= 122) || c == 45) {
			printw("%c", c);
			char s[2] = { c, '\0' };
			strcat(p.firstname, s);
		} else if (c == 27) {
			free(p.firstname);
			return;
		}
	} while (c != '\n');

	mvprintw(begin_v + 9, begin_h, "Nom ? ");
	p.lastname = calloc(50, sizeof(char));
	do {
		noecho();
		c = getch();
		echo();
		if ((c >= 65 && c<= 90) || (c >= 97 && c <= 122) || c == 45) {
			printw("%c", c);
			char s[2] = { c, '\0' };
			strcat(p.lastname, s);
		} else if (c == 27) {
			free(p.firstname);
			free(p.lastname);
			return;
		}
	} while (c != '\n');

	mvprintw(begin_v + 10, begin_h, "Style ? ");
	p.style = calloc(50, sizeof(char));
	do {
		noecho();
		c = getch();
		echo();
		if ((c >= 65 && c<= 90) || (c >= 97 && c <= 122) || c == 45) {
			printw("%c", c);
			char s[2] = { c, '\0' };
			strcat(p.style, s);
		} else if (c == 27) {
			free(p.firstname);
			free(p.lastname);
			free(p.style);
			return;
		}
	} while (c != '\n');

	people_add(p);

	mvprintw(begin_v + 11, begin_h, "Personne ajoutée !");
}

static void menu_delete(void) {
	mvprintw(begin_v + 8, begin_h, "ID ? ");

	keypad(stdscr, TRUE);
	set_escdelay(0);
	char c;

	char *id = calloc(10, sizeof(char));
	do {
		noecho();
		c = getch();
		echo();
		if (c >= 48 && c<= 57) {
			printw("%c", c);
			char s[2] = { c, '\0' };
			strcat(id, s);
		} else if (c == 27) {
			free(id);
			return;
		}
	} while (c != '\n');

	struct people p = people_get(atoi(id));

	if (p.id != 0) {
		people_delete(atoi(id));
		mvprintw(begin_v + 8, begin_h, "Personne %d supprimé !", atoi(id));
	} else {
		mvprintw(begin_v + 8, begin_h, "Cette personne n'existe pas !");
	}
}

void menu_free(void) {
	endwin();

	file_free();
	index_free();
	people_free();
}
