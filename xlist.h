#ifndef XLIST_H
#define XLIST_H
void xlist_init(void);
void xlist_handle_refresh(void);
int xlist_handle_motion(int x, int y);
void xlist_handle_press(int x, int y);
//void xlist_handle_key_press(XKeyEvent event);
#endif
