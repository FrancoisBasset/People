#include "people.h"

#ifndef FILE_H
#define FILE_H
struct people* file_get_all_people(void);
struct people file_get_people(int id);
void file_add_people(struct people p);
void file_delete_people(int id);
#endif