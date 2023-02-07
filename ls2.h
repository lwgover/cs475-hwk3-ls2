#ifndef LS2_H_INCLUDED
#define LS2_H_INCLUDED

#include "stack.h"

#define TRUE 1
#define FALSE 0
#define INDENT "    "

// TODO: Function declarations here for ls2
int mode1(char dir[]);
int mode2(char dir[], char file_name[]);
int mode2_recursive(stack_t* stack, char* dir, int numTabs);

#endif
