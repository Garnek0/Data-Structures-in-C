// Queue - queue
//
// Implementation using Singly Linked List (sllist)

#ifndef QUEUE_H
#define QUEUE_H

#include <types.h>
#include <sllist/sllist.h>

typedef struct _queue {
    sllist_t* list;
} queue_t;

queue_t* queue_create();
void queue_destroy(queue_t* queue);
void queue_enqueue(queue_t* queue, void* data);
void* queue_peek(queue_t* queue);
void* queue_dequeue(queue_t* queue);

#endif //QUEUE_H