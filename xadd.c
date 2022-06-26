#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>
#include "xdef.h"
#include "launchx.h"
#include <stdio.h>

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
	}

	return 0;
}

void xadd_handle_press(int x, int y) {
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
	}
}

void xadd_handle_refresh(void) {
	if (add_updated || (focus != NULL && blink_index == 0)) {
		add_updated = 0;
		blink_index = 0;

		XClearArea(display, window, 801, 166, 399, 49, 0);
		XClearArea(display, window, 801, 366, 399, 49, 0);
		XClearArea(display, window, 801, 566, 399, 49, 0);

		XDrawString(display, window, gc_black_text, 805, 205, prenom, strlen(prenom));
		XDrawString(display, window, gc_black_text, 805, 405, nom, strlen(nom));
		XDrawString(display, window, gc_black_text, 805, 605, style, strlen(style));
	}

	if (focus != NULL && blink_index == 50000) {
		if (strcmp(focus, "prenom") == 0) {
			XDrawLine(display, window, gc_black_text, 805, 175, 805, 205);
			XDrawLine(display, window, gc_black_text, 806, 175, 806, 205);
		} else if (strcmp(focus, "nom") == 0) {
			XDrawLine(display, window, gc_black_text, 805, 375, 805, 405);
			XDrawLine(display, window, gc_black_text, 806, 375, 806, 405);
		} else if (strcmp(focus, "style") == 0) {
			XDrawLine(display, window, gc_black_text, 805, 575, 805, 605);
			XDrawLine(display, window, gc_black_text, 806, 575, 806, 605);
		}
	}

	if (blink_index == 100000) {
		blink_index = 0;
	} else {
		blink_index++;
	}
}
