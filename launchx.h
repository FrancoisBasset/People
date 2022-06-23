#ifndef LAUNCHX_H
#define LAUNCHX_H
#include <X11/Xlib.h>

void launchx(void);
void draw_buttons(void);
int handle_buttons_press(int x, int y);
void handle_motion(int x, int y);

void list_people(void);
void show_people(void);
void add_people(void);
void delete_people(void);
#endif
