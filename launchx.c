#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "launchx.h"
#include "xdef.h"

char *scr;

void launchx(void) {
	xdef_init();

	XMapWindow(display, window);
	XSelectInput(display, window, ExposureMask | ButtonPressMask | PointerMotionMask);

	scr = malloc(sizeof(char) * 1);
	strcpy(scr, "");

	int quit = 0;
	draw_buttons();
	XEvent event;
	while (1) {
		XNextEvent(display, &event);

		switch (event.type) {
			case Expose:
				draw_buttons();
				break;
			case ButtonPress:
				quit = handle_buttons_press(event.xbutton.x, event.xbutton.y);
				break;
			case MotionNotify:
				handle_motion(event.xmotion.x, event.xmotion.y);
				break;
		}

		if (quit) {
			break;
		}
	}

	free(scr);
	XFreeGC(display, gc_button);
	XFreeGC(display, gc_white_text);
	XFreeGC(display, gc_black_text);
	XFreeCursor(display, cursor);
	XFreeCursor(display, input_cursor);
	XCloseDisplay(display);
}

void draw_buttons(void) {
	XFillRectangle(display, window, gc_button, 50, 50, 200, 100);
	XFillRectangle(display, window, gc_button, 50, 200, 200, 100);
	XFillRectangle(display, window, gc_button, 50, 350, 200, 100);
	XFillRectangle(display, window, gc_button, 50, 500, 200, 100);
	XFillRectangle(display, window, gc_button, 50, 650, 200, 100);

	XDrawString(display, window, gc_white_text, 60, 105, "Lister les personnes", 20);
	XDrawString(display, window, gc_white_text, 75, 255, "Voir une personne", 17);
	XDrawString(display, window, gc_white_text, 60, 405, "Ajouter une personne", 20);
	XDrawString(display, window, gc_white_text, 50, 555, "Supprimer une personne", 22);
	XDrawString(display, window, gc_white_text, 120, 705, "Quitter", 7);

	XDrawLine(display, window, gc_black_text, 300, 0, 300, max_height);
	XDrawLine(display, window, gc_black_text, 301, 0, 301, max_height);
}

int handle_buttons_press(int x, int y) {
	if (x >= 50 && x <= 250 && y >= 50 && y <= 150) {
		list_people();
	} else if (x >= 50 && x <= 250 && y >= 200 && y <= 300) {
		show_people();
	} else if (x >= 50 && x <= 250 && y >= 350 && y <= 450) {
		add_people();
	} else if (x >= 50 && x <= 250 && y >= 500 && y <= 600) {
		delete_people();
	} else if (x >= 50 && x <= 250 && y >= 650 && y <= 750) {
		return 1;
	}

	return 0;
}

void handle_motion(int x, int y) {
	if (strcmp(scr, "addscreen") == 0) {
		if (x >= 800 && x <= 1200 && y >= 165 && y <= 215) {
			XDefineCursor(display, window, input_cursor);
		} else if (x >= 800 && x <= 1200 && y >= 365 && y <= 415) {
			XDefineCursor(display, window, input_cursor);
		} else if (x >= 800 && x <= 1200 && y >= 565 && y <= 615) {
			XDefineCursor(display, window, input_cursor);
		} else {
			XDefineCursor(display, window, cursor);
		}
	}
}

void list_people(void) {
}

void show_people(void) {
}

void add_people(void) {
	if (scr != NULL) {
		free(scr);
	}
	scr = malloc(sizeof(char) * 10);
	strcpy(scr, "addscreen");
	XDrawString(display, window, gc_black_text, 1000, 100, "Ajouter une personne", 20);

	XDrawString(display, window, gc_black_text, 600, 200, "Prenom : ", 9);
	XDrawRectangle(display, window, gc_black_text, 800, 165, 400, 50);

	XDrawString(display, window, gc_black_text, 600, 400, "Nom : ", 5);
	XDrawRectangle(display, window, gc_black_text, 800, 365, 400, 50);
	
	XDrawString(display, window, gc_black_text, 600, 600, "Style : ", 7);
	XDrawRectangle(display, window, gc_black_text, 800, 565, 400, 50);

	XFillRectangle(display, window, gc_button, 900, 700, 200, 100);
	XDrawString(display, window, gc_white_text, 970, 755, "Ajouter", 7);
}

void delete_people(void) {
}
