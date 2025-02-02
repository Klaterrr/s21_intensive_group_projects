#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

// TODO: Implement stack functions here

Stack* stack_init() {
    Stack* zero_stack = malloc(sizeof(Stack));
    zero_stack->top = -1;
    return zero_stack;
}

void stack_push(Stack* stack, Token* data) {
    if (stack->top < MAX_STACK_LEN) {
        stack->top++;
        stack->items[stack->top] = data;
    } else {
        printf("STACK OVERFLOW!\n");
    }
    // printf(": + %d\n", stack->top);
    // printf(": + : %s\n", stack->items[stack->top]->value);
    printf("+: ");
    print_stack(stack);
}

Token* stack_pop(Stack* stack) {
    // printf(": - %d\n", stack->top);
    // printf(": - : %s\n", stack->items[stack->top]->value);

    Token* data = NULL;
    // data->value = (char*)malloc(sizeof(char*));
    if (stack->top > -1) {
        data = stack->items[stack->top];
        stack->top--;
    } else {
        printf("EMPTY STACK!\n");
    }
    // printf("-: ");
    // print_stack(stack);
    return data;
}

void print_stack(Stack* stack) {
    printf("Stack: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%s ", stack->items[i]->value);
    }
    printf("\n");
}

int stack_is_empty(Stack* stack) { return stack->top == -1; }