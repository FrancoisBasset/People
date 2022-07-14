#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "launchx.h"
#include "xdef.h"
#include "xmenu.h"
#include "xadd.h"
#include "xlist.h"

char *scr;
char* hover = NULL;
char *focus = NULL;

int input_text_index = 0;

void launchx(void) {
	xdef_init();

	XMapWindow(display, window);
	XSelectInput(display, window, ExposureMask | ButtonPressMask | PointerMotionMask | KeyPressMask);
	XSetInputFocus(display, window, RevertToNone, CurrentTime);

	scr = malloc(sizeof(char) * 1);
	strcpy(scr, "");

	int quit = 0;
	xmenu_draw_buttons();
	XEvent event;

	while (1) {
		XNextEvent(display, &event);

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
			case KeyPress:
				xadd_handle_key_press(event.xkey);
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
	XSetInputFocus(display, PointerRoot, RevertToParent, CurrentTime);
	XCloseDisplay(display);
}

int handle_press(int x, int y) {
	if (strcmp(scr, "addscreen") == 0) {
		xadd_handle_press(x, y);
	}

	return xmenu_handle_press(x, y);
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

	if (strcmp(scr, "listscreen") == 0) {
		if (xlist_handle_motion(x, y)) {
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

void delete_people(void) {
}
