#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"

char* file_name;


//%%%%%%%%%%%%%%%%%%%%%  Helper Methods  %%%%%%%%%%%%%%%%%%%%%%%%%%%

int mode1_recursive(char* dir, int numTabs){

    DIR* init = opendir(dir); // current directory
    struct dirent *entry; // entry

    struct stat buf; //file stats 
    char* name; // current file name

    chdir(dir); // navigate into the current directory

    while ((entry = readdir(init)) != NULL){
      name = entry->d_name;
      if(!strcmp(name, "..") || !strcmp(name, ".")){ // don't go into parent directory or self
        //printf("%s is invalid\n",name);
        continue;
      }
      if(lstat(name, &buf) == -1){
          printf("Error, %s\n", entry->d_name);
          return 1;
      }
      for(int i = 0; i < numTabs; i++) printf(INDENT); // do all the indenting
      printf("%s",name);
      if (S_ISDIR(buf.st_mode)) {
        printf("/ (directory)\n"); // go to new line
        mode1_recursive(name,numTabs+1); //recurse
      }else{
        printf(" (%ld bytes)\n",buf.st_size);
      }
    }
    closedir(init); //close directory
    chdir(".."); //nav back to parent directory
    return 0; //success
}

void betterStrCat(char s1[], char s2[],char* output){
  strcat(output,s1);
  strcat(output,s2);
}

void fileString(char name[], char tabs[], struct stat buf,char* output){
  snprintf(output,strlen(name) + strlen(tabs) + 20, "%s%s (%ld bytes)",tabs,name,buf.st_size);
}

int stuff_in_the_while_loop(stack_t* stack,char name[],char tabs[], struct stat buf){
  int numTabs = strlen(tabs) / 4;
  char* line;
  if(!strcmp(name, "..") || !strcmp(name, ".")){ // don't go into parent directory or self
    return FALSE;
  }
  if(lstat(name, &buf) == -1){
      printf("Error, %s\n", name);
      return FALSE;
  }
  if (S_ISDIR(buf.st_mode)) {
    if(mode2_recursive(stack,name,numTabs+1) == TRUE){ //only push to stack if true
      line = (char*) calloc(4,strlen(name) + strlen("/ (directory)") + strlen(tabs) + 1);
      betterStrCat(tabs,name,line);
      strcat(line, "/ (directory)");
      push(stack,line); //add directory to the stack
      return TRUE;
    }
  }else if(S_ISREG(buf.st_mode)) {
    if(strcmp(name,file_name)==0){
      char numBytesSize[100];
      sprintf(numBytesSize, "%ld", buf.st_size);

      line = (char*) calloc(4,strlen(tabs) + strlen(name) + strlen(" (") + strlen(numBytesSize) + strlen(" bytes)") + 1);
      fileString(name,tabs,buf,line);
      push(stack,line); //add file to the stack
      return TRUE;
    }
  }
  return FALSE;
}

int mode2_recursive(stack_t* stack, char* dir, int numTabs){
    DIR* init = opendir(dir);
    struct dirent *entry;

    struct stat buf;
    char* name;

    chdir(dir); // navigate into the current directory

    char tabs[numTabs * strlen(INDENT)];
    tabs[0] = ""[0];
    for(int i = 0; i < numTabs; i++)strcat(tabs,INDENT); // get the right numTabs for the variables

    int seenFileType = FALSE;

    while ((entry = readdir(init)) != NULL){
      name = entry->d_name;
      if(stuff_in_the_while_loop(stack,name,tabs,buf)==TRUE){
        seenFileType = TRUE;
      }
    }
    closedir(init); //close directory
    chdir(".."); //nav back to parent directory
    return seenFileType; //success
}
// %%%%%%%%%%%% visible functions %%%%%%%%%%%%%%%%%%%%%%%%%

int mode1(char dir[]){return mode1_recursive(dir,0);}

int mode2(char dir[], char fileName[]){
  struct stack_t *stack;
  stack = initstack();

  file_name = fileName;
  
  mode2_recursive(stack,dir,0);
  printstack(stack);
  return 0;
}