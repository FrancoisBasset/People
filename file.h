#include "people.h"

#ifndef FILE_H
#define FILE_H
void file_init(void);

char** file_get_all_lines(void);
int file_get_all_lines_count(void);

void file_write_people(struct people p);
void file_write_peoples(struct people *peoples, int people_count);

void file_free(void);
#endif