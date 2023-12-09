// Stack - stack

#ifndef STACK_H
#define STACK_H

#include <types.h>

typedef struct _stack {
    size_t size;
    size_t top;
    long* stack;
} stack_t;

stack_t* stack_create(size_t size);
void stack_destroy(stack_t* stack);
void stack_push(stack_t* stack, long value);
long stack_peek(stack_t* stack);
long stack_pop(stack_t* stack);

#endif //STACK_H