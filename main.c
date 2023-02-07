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

	if (argv[1] == NULL){
		printf("./ls2Sol <path> [exact-match-pattern]\n");
		return 1;
	}

	printf("works: %s",argv[1]);
	mode1(argv[1]);
	//draw("./nixon.txt");
	return 0;
}
