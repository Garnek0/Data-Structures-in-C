#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

queue_t* queue_create(){
    queue_t* queue = malloc(sizeof(queue_t)); // Allocate the queue struct
    queue->list = sllist_create(); // Create the list in which the queue items will be stored
    return queue; // Finally, return the address of the newly created queue
}

void queue_destroy(queue_t* queue){
    sllist_destroy(queue->list); // Destroy the list first
    free(queue);
}

void queue_enqueue(queue_t* queue, void* data){
    // Just insert the the item at the end of the linked list
    sllist_insert_end(queue->list, data);
}

void* queue_peek(queue_t* queue){
    // If the list has 0 nodes, then there are no items in the queue.
    // Print an error message and return
    if(queue->list->nodeCount == 0){
        fprintf(stderr, "queue: can\'t peek; no items queued!\n");
        return NULL;
    }
    void* data = sllist_search(queue->list, 0); // Get the first item from the list, 
                                                // This is the first item in the queue
    return data;
}

void* queue_dequeue(queue_t* queue){
    // If the list has 0 nodes, then there are no items in the queue.
    // Print an error message and return
    if(queue->list->nodeCount == 0){
        fprintf(stderr, "queue: can\'t dequeue; no items queued!\n");
        return NULL;
    }
    void* data = sllist_search(queue->list, 0); // (Same as queue_peek)
    sllist_remove_by_index(queue->list, 0); // Remove the node containing the just now retrieved item
    return data;
}