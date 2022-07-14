#include <X11/Xlib.h>
#include "launchx.h"
#include "xdef.h"
#include "xlist.h"
#include "xadd.h"

void xmenu_draw_buttons(void) {
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

int xmenu_handle_motion(int x, int y) {
	if (x >= 50 && x <= 250 && y >= 50 && y <= 150) {
		XDefineCursor(display, window, cursor);
		return 1;
	} else if (x >= 50 && x <= 250 && y >= 200 && y <= 300) {
		XDefineCursor(display, window, cursor);
		return 1;
	} else if (x >= 50 && x <= 250 && y >= 350 && y <= 450) {
		XDefineCursor(display, window, cursor);
		return 1;
	} else if (x >= 50 && x <= 250 && y >= 500 && y <= 600) {
		XDefineCursor(display, window, cursor);
		return 1;
	} else if (x >= 50 && x <= 250 && y >= 650 && y <= 750) {
		XDefineCursor(display, window, cursor);
		return 1;
	}

	XUndefineCursor(display, window);
	return 0;
}

int xmenu_handle_press(int x, int y) {
	if (x >= 50 && x <= 250 && y >= 50 && y <= 150) {
		xlist_init();
	} else if (x >= 50 && x <= 250 && y >= 200 && y <= 300) {
		show_people();
	} else if (x >= 50 && x <= 250 && y >= 350 && y <= 450) {
		xadd_init();
	} else if (x >= 50 && x <= 250 && y >= 500 && y <= 600) {
		delete_people();
	} else if (x >= 50 && x <= 250 && y >= 650 && y <= 750) {
		return 1;
	}

	return 0;
}
