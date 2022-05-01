#include "people.h"

#ifndef FILE_H
#define FILE_H
void file_init(void);
struct people* file_get_all_people(void);
struct people file_get_people(int id);
int file_get_all_people_count(void);
void file_add_people(struct people p);
void file_delete_people(int id);
void file_free(void);
#endif