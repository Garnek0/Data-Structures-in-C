#include <stdio.h>
#include "sllist/sllist.h"
#include "stack/stack.h"
#include "queue/queue.h"

int main(){
    stack_t* stack = stack_create();
    sllist_t* sllist = sllist_create();
    queue_t* queue = queue_create();

    stack_destroy(stack);
    sllist_destroy(sllist);
    queue_destroy(queue);
}