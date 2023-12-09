#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

stack_t* stack_create(size_t size){
    if(size == 0) size = 1;
    stack_t* stack = malloc(sizeof(stack_t));

    stack->stack = calloc(size, sizeof(long));
    stack->size = size;
    stack->top = 0;
    return stack;
}

void stack_destroy(stack_t* stack){
    free(stack->stack);
    free(stack);
}

void stack_push(stack_t* stack, long value){
    if(stack->top >= stack->size){
        printf("stack: can\'t push; overflow!\n");
        return;
    }
    stack->stack[stack->top] = value;
    stack->top++;
}

long stack_peek(stack_t* stack){
    if(stack->top <= 0){
        printf("stack: can\'t peek; top is 0!\n");
        return 0;
    }
    long value = stack->stack[stack->top-1];
    return value;
}

long stack_pop(stack_t* stack){
    if(stack->top <= 0){
        printf("stack: can\'t push; top is 0!\n");
        return 0;
    }
    long value = stack_peek(stack);
    stack->top--;
    return value;
}