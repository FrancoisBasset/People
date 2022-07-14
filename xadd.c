#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>
#include "xdef.h"
#include "launchx.h"
#include "people.h"
#include <stdio.h>

char *prenom;
char *nom;
char *style;
char add_updated = 1;

void xadd_init(void) {
	prenom = malloc(sizeof(char) * 100);
	strcpy(prenom, "");
	nom = malloc(sizeof(char) * 100);
	strcpy(nom, "");
	style = malloc(sizeof(char) * 100);
	strcpy(style, "");

	if (scr != NULL) {
		free(scr);
		scr = NULL;
	}
	scr = malloc(sizeof(char) * 10);
	strcpy(scr, "addscreen");

	XClearArea(display, window, 302, 0, max_width - 302, max_height, 0);

	XDrawString(display, window, gc_black_text, 900, 100, "Ajouter une personne", 20);

	XDrawString(display, window, gc_black_text, 600, 200, "Prenom : ", 9);
	XDrawRectangle(display, window, gc_black_text, 800, 165, 400, 50);

	XDrawString(display, window, gc_black_text, 600, 400, "Nom : ", 5);
	XDrawRectangle(display, window, gc_black_text, 800, 365, 400, 50);

	XDrawString(display, window, gc_black_text, 600, 600, "Style : ", 7);
	XDrawRectangle(display, window, gc_black_text, 800, 565, 400, 50);

	XFillRectangle(display, window, gc_button, 900, 700, 200, 100);
	XDrawString(display, window, gc_white_text, 970, 755, "Ajouter", 7);
}

int xadd_handle_motion(int x, int y) {
	if (x >= 800 && x <= 1200 && y >= 165 && y <= 215) {
		XDefineCursor(display, window, input_cursor);
		hover = malloc(sizeof(char) * 7);
		strcpy(hover, "prenom");
		return 1;
	} else if (x >= 800 && x <= 1200 && y >= 365 && y <= 415) {
		XDefineCursor(display, window, input_cursor);
		hover = malloc(sizeof(char) * 4);
		strcpy(hover, "nom");
		return 1;
	} else if (x >= 800 && x <= 1200 && y >= 565 && y <= 615) {
		XDefineCursor(display, window, input_cursor);
		hover = malloc(sizeof(char) * 6);
		strcpy(hover, "style");
		return 1;
	} else if (x >= 900 && x <= 1100 && y >= 700 && y <= 800) {
		XDefineCursor(display, window, cursor);
		return 1;
	} else {
		free(hover);
		hover = NULL;
	}

	return 0;
}

void xadd_handle_press(int x, int y) {
	add_updated = 1;

	if (hover != NULL) {
		if (strcmp(hover, "prenom") == 0) {
			focus = malloc(sizeof(char) * 7);
			strcpy(focus, "prenom");
		} else if (strcmp(hover, "nom") == 0) {
			focus = malloc(sizeof(char) * 4);
			strcpy(focus, "nom");
		} else if (strcmp(hover, "style") == 0) {
			focus = malloc(sizeof(char) * 6);
			strcpy(focus, "style");
		}
	} else {
		free(focus);
		focus = NULL;
	}

	if (x >= 900 && x <= 1100 && y >= 700 && y <= 800) {
		struct people new_people = { .firstname = prenom, .lastname = nom, .style = style };
		people_add(new_people);

		strcpy(prenom, "");
		strcpy(nom, "");
		strcpy(style, "");
	}
}

void xadd_handle_refresh(void) {
	if (!add_updated) {
		return;
	}

	add_updated = 0;

	XClearArea(display, window, 801, 166, 399, 49, 0);
	XClearArea(display, window, 801, 366, 399, 49, 0);
	XClearArea(display, window, 801, 566, 399, 49, 0);

	XDrawString(display, window, gc_black_text, 805, 205, prenom, strlen(prenom));
	XDrawString(display, window, gc_black_text, 805, 405, nom, strlen(nom));
	XDrawString(display, window, gc_black_text, 805, 605, style, strlen(style));

	if (focus != NULL) {
		if (strcmp(focus, "prenom") == 0) {
			int width = XTextWidth(XQueryFont(display, big_font), prenom, input_text_index);

			XDrawLine(display, window, gc_black_text, 805 + width, 175, 805 + width, 205);
			XDrawLine(display, window, gc_black_text, 806 + width, 175, 806 + width, 205);
		} else if (strcmp(focus, "nom") == 0) {
			int width = XTextWidth(XQueryFont(display, big_font), nom, input_text_index);

			XDrawLine(display, window, gc_black_text, 805 + width, 375, 805 + width, 405);
			XDrawLine(display, window, gc_black_text, 806 + width, 375, 806 + width, 405);
		} else if (strcmp(focus, "style") == 0) {
			int width = XTextWidth(XQueryFont(display, big_font), style, input_text_index);

			XDrawLine(display, window, gc_black_text, 805 + width, 575, 805 + width, 605);
			XDrawLine(display, window, gc_black_text, 806 + width, 575, 806 + width, 605);
		}
	}
}

void xadd_handle_key_press(XKeyEvent event) {
	KeySym keysym = XLookupKeysym(&event, 0);
	char *keytext = XKeysymToString(keysym);

	if ((event.state & ShiftMask) == ShiftMask) {
		if (strlen(keytext) == 1) {
			int keycode = keytext[0] - 32;

			keytext = malloc(sizeof(char) * 2);
			sprintf(keytext, "%c", keycode);
		}
	}

	add_updated = 1;

	if (focus != NULL) {
		if (strlen(keytext) == 1) {
			if (strcmp(focus, "prenom") == 0) {
				if (input_text_index == strlen(prenom)) {
					strcat(prenom, keytext);
				} else {
					char *tmp = calloc(strlen(prenom) + 2, sizeof(char));
					strncpy(tmp, prenom, input_text_index);
					tmp[strlen(tmp)] = '\0';
					strcat(tmp, keytext);
					strcat(tmp, prenom + input_text_index);

					strcpy(prenom, tmp);
					free(tmp);
				}
			} else if (strcmp(focus, "nom") == 0) {
				if (input_text_index == strlen(nom)) {
					strcat(nom, keytext);
				} else {
					char *tmp = calloc(strlen(nom) + 2, sizeof(char));
					strncpy(tmp, nom, input_text_index);
					tmp[strlen(tmp)] = '\0';
					strcat(tmp, keytext);
					strcat(tmp, nom + input_text_index);

					strcpy(nom, tmp);
					free(tmp);
				}
			} else if (strcmp(focus, "style") == 0) {
				if (input_text_index == strlen(style)) {
					strcat(style, keytext);
				} else {
					char *tmp = calloc(strlen(style) + 2, sizeof(char));
					strncpy(tmp, style, input_text_index);
					tmp[strlen(tmp)] = '\0';
					strcat(tmp, keytext);
					strcat(tmp, style + input_text_index);

					strcpy(style, tmp);
					free(tmp);
				}
			}

			input_text_index++;
		} else if (strcmp(keytext, "BackSpace") == 0) {
			if (strcmp(focus, "prenom") == 0) {
				prenom[strlen(prenom) - 1] = '\0';

				if (input_text_index > strlen(prenom)) {
					input_text_index = strlen(prenom);
				}
			} else if (strcmp(focus, "nom") == 0) {
				nom[strlen(nom) - 1] = '\0';

				if (input_text_index > strlen(nom)) {
					input_text_index = strlen(nom);
				}
			} else if (strcmp(focus, "style") == 0) {
				style[strlen(style) - 1] = '\0';

				if (input_text_index > strlen(style)) {
					input_text_index = strlen(style);
				}
			}
		} else if (strcmp(keytext, "Left") == 0) {
			if (input_text_index > 0) {
				input_text_index--;
			}
		} else if (strcmp(keytext, "Right") == 0) {
			if (strcmp(focus, "prenom") == 0) {
				if (input_text_index < strlen(prenom)) {
					input_text_index++;
				}
			} else if (strcmp(focus, "nom") == 0) {
				if (input_text_index < strlen(nom)) {
					input_text_index++;
				}
			} else if (strcmp(focus, "style") == 0) {
				if (input_text_index < strlen(style)) {
					input_text_index++;
				}
			}
		}
	}
}
