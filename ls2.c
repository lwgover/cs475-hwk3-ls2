#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"


// TODO: function definitions here for ls2

void mode1(char dir[]){
    struct stack_t *stack;
    stack = initstack();

    DIR* init = opendir(dir);
    struct dirent *entry;


    push(stack,init);

    char* name;

    while(stack->top != NULL){
      while ((entry = readdir(init)) != NULL){
        name = entry->d_name;
        if(name[0] == '.' && strlen(name) == 1){
          printf("ignored");
        }
        if(name[0] == '.' && name[1] == '.' && strlen(name) == 2){
          printf("ignored");
        }
      }
    }
    closedir(init); 
}
