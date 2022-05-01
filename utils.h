#ifndef UTILS_H
#define UTILS_H
char *utils_get_username(void);
char *utils_get_people_folder_name();
char *utils_get_index_file_name();
char *utils_get_people_file_name();
void utils_mkdir(char *folder_name);
int utils_file_exists(char *file_name);
#endif