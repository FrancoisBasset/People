#ifndef XADD_H
#define XADD_H
void xadd_init(void);
int xadd_handle_motion(int x, int y);
void xadd_handle_press(int x, int y);
void xadd_handle_refresh(void);
void xadd_handle_key_press(XKeyEvent event);
#endif
