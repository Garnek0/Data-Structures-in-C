#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

stack_t* stack_create(){
    stack_t* stack = malloc(sizeof(stack_t)); // Allocate the stack struct

    stack->list = sllist_create(); // Create the list for the stack elements
    stack->top = 0; // Set the top of the stack to 0
    return stack; // Return the address of the new stack
}

void stack_destroy(stack_t* stack){
    sllist_destroy(stack->list); // Destroy the list first
    free(stack);
}

void stack_push(stack_t* stack, void* data){
    sllist_insert_end(stack->list, data); // Insert the item into the stack's list
    stack->top++; // Increase the top pointer
}

void* stack_peek(stack_t* stack){
    // If the stack top pointer is 0, then there are no items on the stack.
    // Print an error and return.
    if(stack->top == 0){
        fprintf(stderr, "stack: can\'t peek; top is 0!\n");
        return 0;
    }
    void* data = sllist_search(stack->list, stack->top-1); // Get the last element from the list (top-1)
    return data;
}

void* stack_pop(stack_t* stack){
    // If the stack top pointer is 0, then there are no items on the stack.
    // Print an error and return.
    if(stack->top <= 0){
        fprintf(stderr, "stack: can\'t push; top is 0!\n");
        return 0;
    }
    void* data = sllist_search(stack->list, stack->top-1); // (Same as stack_peek)
    stack->top--; // Decrement the top and remove the last value of the stack
    sllist_remove_by_index(stack->list, stack->top);
    return data;
}