#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "launchx.h"
#include "xdef.h"
#include "xmenu.h"
#include "xadd.h"

char *scr;
char* hover = NULL;
char *focus = NULL;
char *prenom;
char *nom;
char *style;

char add_updated = 1;
int blink_index = -1;

void launchx(void) {
	xdef_init();

	XMapWindow(display, window);
	XSelectInput(display, window, ExposureMask | ButtonPressMask | PointerMotionMask);

	scr = malloc(sizeof(char) * 1);
	strcpy(scr, "");

	prenom = malloc(sizeof(char) * 100);
	strcpy(prenom, "Francois");
	nom = malloc(sizeof(char) * 100);
	strcpy(nom, "Basset");
	style = malloc(sizeof(char) * 100);
	strcpy(style, "Trance");

	int quit = 0;
	xmenu_draw_buttons();
	XEvent event;

	int blink_index = 0;

	while (1) {
		if (XPending(display)) {
			XNextEvent(display, &event);
		}

		switch (event.type) {
			case Expose:
				xmenu_draw_buttons();
				break;
			case ButtonPress:
				quit = handle_press(event.xbutton.x, event.xbutton.y);
				break;
			case MotionNotify:
				handle_motion(event.xmotion.x, event.xmotion.y);
				break;
		}

		if (quit) {
			break;
		}

		if (strcmp(scr, "addscreen") == 0) {
			xadd_handle_refresh();
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

int handle_press(int x, int y) {
	if (strcmp(scr, "addscreen") == 0) {
		xadd_handle_press(x, y);
	}

	return xmenu_handle_press(x, y);

	//int pixel = XTextWidth(font, prenom, strlen(prenom));
	//XDrawString(display, window, gc_black_text, 805 + pixel, 200, prenom, strlen(prenom));
}

void handle_motion(int x, int y) {
	if (hover != NULL) {
		free(hover);
		hover = NULL;
	}

	if (strcmp(scr, "addscreen") == 0) {
		if (xadd_handle_motion(x, y)) {
			return;
		}
	}

	if (xmenu_handle_motion(x, y)) {
		return;
	}
}

void list_people(void) {
}

void show_people(void) {
}

void add_people(void) {
	if (scr != NULL) {
		free(scr);
		scr = NULL;
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
