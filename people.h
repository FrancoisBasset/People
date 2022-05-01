#ifndef PEOPLE_H
#define PEOPLE_H
struct people {
	int id;
	char *firstname;
	char *lastname;
	char *style;
};

void people_print(struct people p);
struct people* people_get_all(void);
struct people people_get(int id);
void people_add(struct people p);
void people_delete(int id);
void people_free(struct people p);
#endif