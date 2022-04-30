#include <stdio.h>
#include <stdlib.h>
#include "index.h"

int main(void) {
	index_init();

	index_increment();

	printf("%d\n", index_get());

	index_end();
}