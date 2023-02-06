#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

/**
 * Creates and returns a pointer to a new stack
 * @return pointer to a stack_t
 */
stack_t *initstack() {
  stack_t *newStack = (stack_t*) malloc(sizeof(stack_t));
  newStack->top = NULL;
  newStack->size = 0;
  return newStack;
}

/**
 * Pops and frees top element.
 * @param s pointer to a stack_t
 * @return a pointer to the top, or NULL if stack was empty
 */
void* pop(stack_t* s) {
  if (s->size > 0) {
    stacknode_t *top = s->top;
    void* oldData = top->data;  // save the current top for return
    s->top = s->top->next;
    s->size--;
    free(top);  // free up memory
    return oldData;
  }
  return NULL;
}

/**
 * Pushes an element onto the stack
 * @param s pointer to a stack_t
 * @param item pointer to an element to push onto the stack
 */
void push(stack_t* s, void* item) {
  stacknode_t *newNode = (stacknode_t*) malloc(sizeof(stacknode_t));
  newNode->data = item;
  newNode->next = s->top;
  s->top = newNode;
  s->size++;
}

/**
 * Frees up the stack
 * @param s pointer to a stack_t
 */
void freestack(stack_t* s) {
  while (s->size) {
    pop(s);
  }
  free(s);
}

/**
 * Prints out the contents of the stack from top to bottom.
 * @param s pointer to a stack_t
 */
void printstack(stack_t* s) {
  stacknode_t *current = s->top;
  while (current != NULL) {
    printf("%s\n", (char*) current->data);
    current = current->next;
  }
}