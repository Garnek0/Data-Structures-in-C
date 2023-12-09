#include <stdio.h>
#include "sllist/sllist.h"
#include "stack/stack.h"

int main(){
    stack_t* stack = stack_create(1);
    sllist_t* sllist = sllist_create();

    stack_destroy(stack);
    sllist_destroy(sllist);
}