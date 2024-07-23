// Doubly Linked List - dllist

#ifndef DLLIST_H
#define DLLIST_H

#define dllist_foreach(list, i) for(struct _dllist_node* i = list->head; i != NULL; i = i->next)

#include <types.h>

typedef struct _dllist {
    size_t nodeCount;
    struct _dllist_node* head;
    struct _dllist_node* tail;
} dllist_t;

typedef struct _dllist_node {
    void* data;
    struct _dllist_node* next;
	struct _dllist_node* prev;
} dllist_node_t;

dllist_t* dllist_create();
void dllist_destroy(dllist_t* list);
void dllist_insert();
void dllist_insert_end(dllist_t* list, void* data);
void dllist_insert_start(dllist_t* list, void* data);
void dllist_insert(dllist_t* list, void* data, size_t index);
void dllist_remove(dllist_t* list, void* data);
void dllist_remove_by_index(dllist_t* list, size_t index);
void* dllist_search(dllist_t* list, size_t index);

#endif //DLLIST_H
