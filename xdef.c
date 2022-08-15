#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include "xdef.h"
#include <stdio.h>

Display *display;
Screen *screen;
Window root_window;
Window window;
Visual *visual;

unsigned long black_pixel;
unsigned long white_pixel;
unsigned long green_pixel;

int screen_number;
int max_width;
int max_height;

GC gc_button;
GC gc_white_text;
GC gc_black_text;
GC gc_normal_black_text;

char *font_name = "-misc-fixed-bold-r-normal--18-120-100-100-c-90-iso8859-13";
char *big_font_name = "-adobe-helvetica-bold-r-normal--34-240-100-100-p-182-iso10646-1";

Cursor cursor;
Cursor input_cursor;

Font font;
Font big_font;

void xdef_init(void) {
	display = XOpenDisplay(0);
	screen = XDefaultScreenOfDisplay(display);
	root_window = XDefaultRootWindow(display);
	screen_number = XDefaultScreen(display);
	black_pixel = XBlackPixel(display, screen_number);
	white_pixel = XWhitePixel(display, screen_number);
	max_width = XWidthOfScreen(screen);
	max_height = XHeightOfScreen(screen);
	visual = XDefaultVisualOfScreen(screen);

	cursor = XCreateFontCursor(display, XC_hand1);

	XSetWindowAttributes xswa;
	xswa.override_redirect = True;
	window = XCreateWindow(display, root_window, 0, 0, max_width, max_height, 0, 24, InputOutput, visual, CWOverrideRedirect, &xswa);
	XSetWindowBackground(display, window, white_pixel);

	Colormap colormap = XCreateColormap(display, root_window, visual, AllocNone);

	XColor green;
	green.green = 55535;
	green.blue = 20000;
	XAllocColor(display, colormap, &green);
	green_pixel = green.pixel;

	XGCValues gcv_button;
	gcv_button.foreground = green_pixel;
	gc_button = XCreateGC(display, window, GCForeground, &gcv_button);

	font = XLoadFont(display, font_name);
	big_font = XLoadFont(display, big_font_name);

	XGCValues gcv_white_text;
    gcv_white_text.foreground = white_pixel;
	gcv_white_text.font = font;
    gc_white_text = XCreateGC(display, window, GCForeground | GCFont, &gcv_white_text);

	XGCValues gcv_black_text;
    gcv_black_text.foreground = black_pixel;
	gcv_black_text.font = big_font;
    gc_black_text = XCreateGC(display, window, GCForeground | GCFont, &gcv_black_text);
	
	XGCValues gcv_normal_black_text;
    gcv_normal_black_text.foreground = black_pixel;
	gcv_normal_black_text.font = font;
    gc_normal_black_text = XCreateGC(display, window, GCForeground | GCFont, &gcv_normal_black_text);

	input_cursor = XCreateFontCursor(display, XC_xterm);
}
