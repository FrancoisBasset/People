#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>
#include "xdef.h"
#include "launchx.h"
#include "xlist.h"

void xlist_init(void) {
	if (scr != NULL) {
		free(scr);
		scr = NULL;
	}
	scr = malloc(sizeof(char) * 11);
	strcpy(scr, "listscreen");

	XClearArea(display, window, 302, 0, max_width - 302, max_height, 0);

	XDrawString(display, window, gc_black_text, 900, 100, "Liste des personnes", 19);

	XDrawString(display, window, gc_black_text, 900, 200, "ID :", 4);

	XDrawLine(display, window, gc_black_text, 980, 170, 1080, 170);
	XDrawLine(display, window, gc_black_text, 980, 210, 1080, 210);
	XDrawLine(display, window, gc_black_text, 975, 175, 975, 205);
	XDrawLine(display, window, gc_black_text, 1085, 175, 1085, 205);
	XDrawArc(display, window, gc_black_text, 975, 170, 10, 10, 90 * 64, 90 * 64);
	XDrawArc(display, window, gc_black_text, 1075, 170, 10, 10, 0 * 64, 90 * 64);

	XDrawArc(display, window, gc_black_text, 975, 200, 10, 10, 180 * 64, 90 * 64);
	XDrawArc(display, window, gc_black_text, 1075, 200, 10, 10, 270 * 64, 90 * 64);

	XDrawLine(display, window, gc_black_text, 1070, 170, 1070, 210);

	int start_pixel = 1073;
	int end_pixel = 1082;

	for (int i = 0; start_pixel < end_pixel; i++) {
		XDrawLine(display, window, gc_black_text, start_pixel, 186 + i, end_pixel, 186 + i);	

		if (i % 2 == 0) {
			start_pixel++;
			end_pixel--;
		}
	}
}

int xlist_handle_motion(int x, int y) {
	if (x >= 1071 && x <= 1079 && y >= 171 && y <= 209) {
		XDefineCursor(display, window, cursor);
		return 1;
	}

	return 0;
}
