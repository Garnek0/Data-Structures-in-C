// Singly Linked List - sllist

#ifndef SLLIST_H
#define SLLIST_H

#define sllist_foreach(list, i) for(struct _sllist_node* i = list->head; i != NULL; i = i->next)

#include <types.h>

typedef struct _sllist {
    size_t nodeCount;
    struct _sllist_node* head;
    struct _sllist_node* tail;
} sllist_t;

typedef struct _sllist_node {
    void* data;
    struct _sllist_node* next;
} sllist_node_t;

sllist_t* sllist_create();
void sllist_destroy(sllist_t* list);
void sllist_insert();
void sllist_insert_end(sllist_t* list, void* data);
void sllist_insert_start(sllist_t* list, void* data);
void sllist_insert(sllist_t* list, void* data, size_t index);
void sllist_remove(sllist_t* list, void* data);
void sllist_remove_by_index(sllist_t* list, size_t index);

#endif //SLLIST_H