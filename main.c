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
	draw("./prettyPicture.txt"); 

	if (argv[1] == NULL){
		printf("./ls2Sol <path> [exact-match-pattern]\n");
		return 1;
	}
	if (argv[2] != NULL){
		mode2(argv[1],argv[2]);	
	}else{
		mode1(argv[1]);
	}
	return 0;
}
