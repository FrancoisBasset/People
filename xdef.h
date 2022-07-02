#ifndef XDEF_H
#define XDEF_H
void xdef_init(void);

extern Display* display;
extern Window window;

extern GC gc_button;
extern GC gc_white_text;
extern GC gc_black_text;

extern Cursor cursor;
extern Cursor input_cursor;

extern int max_height;

extern Font font;
extern Font big_font;
#endif
