#include <stdio.h>
#include <string.h>
#include "curses.h"

int main(int argc, char **argv) {
	if (argc == 2 && strcmp(argv[1], "-gui") == 0) {
		printf("GUI");
	} else {
		menu_main();
		menu_free();
	}
}
