#include <stdio.h>
#include "sllist/sllist.h"
#include "dllist/dllist.h"
#include "stack/stack.h"
#include "queue/queue.h"

int main(){
    stack_t* stack = stack_create();
    sllist_t* sllist = sllist_create();
	dllist_t* dllist = dllist_create();
    queue_t* queue = queue_create();

	// Test code goes here

    stack_destroy(stack);
    sllist_destroy(sllist);
	dllist_destroy(dllist);
    queue_destroy(queue);
}
