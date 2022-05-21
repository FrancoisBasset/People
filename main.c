#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers/index.h"
#include "headers/file.h"
#include "headers/people.h"
#include "headers/menu.h"

int main(void) {
	menu_main();
	menu_free();
}