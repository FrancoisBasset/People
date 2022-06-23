#include <X11/Xlib.h>
#include <stdio.h>

int main(void) {
	Display *display = XOpenDisplay(0);

	int c;
    char **fonts = XListFonts(display, "*bold-r-*", 400, &c);
    for (int i = 0; i < c; i++) {
         printf(fonts[i]);
         printf("\n");
    }
}
