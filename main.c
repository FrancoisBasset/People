#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "index.h"
#include "file.h"
#include "people.h"
#include "menu.h"

int main(void) {
	menu_main();
	menu_free();
}