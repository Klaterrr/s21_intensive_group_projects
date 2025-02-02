#ifndef STACK_H
#define STACK_H

#include "lib.h"
#define MAX_STACK_LEN 100

typedef struct stack_struct {
    Token* items[MAX_STACK_LEN];
    int top;
} Stack;

Stack* stack_init();
void stack_push(Stack* stack, Token* data);
Token* stack_pop(Stack* stack);
void print_stack(Stack* stack);
int stack_is_empty(Stack* stack);

#endif
