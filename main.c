#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"
#include "draw.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	// stack stores the lines to print out
	stack_t *s = initstack();

	push(s, "Hello1");
	push(s, "Hello2");
	push(s, "Hello3");

	// print stack
	printstack(s);

	// free up stack
	freestack(s);

	printf("%s",argv[1]);
	//mode1(argv[1]);
	draw("./nixon.txt");
	return 0;
}
