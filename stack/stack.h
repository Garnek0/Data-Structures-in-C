// Stack - stack
//
// Implementation using Singly Linked List (sllist)

#ifndef STACK_H
#define STACK_H

#include <types.h>
#include <sllist/sllist.h>

typedef struct _stack {
    size_t top;
    sllist_t* list;
} stack_t;

stack_t* stack_create();
void stack_destroy(stack_t* stack);
void stack_push(stack_t* stack, void* value);
void* stack_peek(stack_t* stack);
void* stack_pop(stack_t* stack);

#endif //STACK_H