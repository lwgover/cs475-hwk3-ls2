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

//puts together s1 and s2 and stores the result in output
void betterStrCat(char s1[], char s2[],char* output){
  strcat(output,s1);
  strcat(output,s2);
}

//makes the file string
void fileString(char name[], char tabs[], struct stat buf,char* output){
  snprintf(output,strlen(name) + strlen(tabs) + 20, "%s%s (%ld bytes)",tabs,name,buf.st_size);
}

int stuff_in_the_while_loop(stack_t* stack,char name[],char tabs[], struct stat buf){
  int numTabs = strlen(tabs) / 4;
  char* line;
  if(!strcmp(name, "..") || !strcmp(name, ".")){ // don't go into parent directory or self
    return FALSE;
  }
  if(lstat(name, &buf) == -1){ // checks if stat is working
      printf("Error, %s\n", name);
      return FALSE;
  }
  if (S_ISDIR(buf.st_mode)) {
    if(mode2_recursive(stack,name,numTabs+1) == TRUE){ //only push to stack if true
      line = (char*) calloc(4,strlen(name) + strlen("/ (directory)") + strlen(tabs) + 1);
      betterStrCat(tabs,name,line); // puts together tabs and name and stores it in line
      strcat(line, "/ (directory)");
      push(stack,line); //add directory to the stack
      return TRUE;
    }
  }else if(S_ISREG(buf.st_mode)) { // for regular files
    if(strcmp(name,file_name)==0){ // see if it's named the name of file_name
      char numBytesSize[100];
      sprintf(numBytesSize, "%ld", buf.st_size); // put the bytes string into an array and see how long it is

      line = (char*) calloc(4,strlen(tabs) + strlen(name) + strlen(" (") + strlen(numBytesSize) + strlen(" bytes)") + 1); //allocate mem 
      fileString(name,tabs,buf,line); // make the string
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

    while ((entry = readdir(init)) != NULL){ // get an entry
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
  stack = initstack(); // init the stack

  file_name = fileName; //set global file_name
  
  mode2_recursive(stack,dir,0); // make the stack
  printstack(stack); // print the stack
  return 0;
}