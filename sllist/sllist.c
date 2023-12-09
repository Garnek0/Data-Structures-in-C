#include "sllist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

sllist_t* sllist_create(){
    sllist_t* list = malloc(sizeof(sllist_t)); // Allocate the sllist
    memset(list, 0, sizeof(sllist_t)); // Zero out the sllist structure
    return list; // Return the sllist pointer
}

void sllist_destroy(sllist_t* list){
    sllist_node_t* node = list->head;
    sllist_node_t* nextNode;

    // Destroy each node recursively
    while(node != NULL){
        nextNode = node->next;
        free(node);
        node = nextNode;
    }
    // Finally, free the list itself
    free(list);
}

void sllist_insert_end(sllist_t* list, void* data){
    // Allocate the new node and set it's fields to the correct values
    sllist_node_t* node = malloc(sizeof(sllist_node_t));
    node->next = NULL;
    node->data = data;

    // If the list has no elements, then the first
    // One to be inserten will be both it's head and it's tail
    if(list->nodeCount == 0) list->head = list->tail = node;
    else {
        list->tail->next = node; // Set the former tail's next pointer
        list->tail = node; // Set the new tail
    }
    list->nodeCount++; // Increase the node count
}

void sllist_insert_start(sllist_t* list, void* data){
    // (Same as sllist_insert_end)
    sllist_node_t* node = malloc(sizeof(sllist_node_t));
    node->data = data;

    // (Same as sllist_insert_end)
    if(list->nodeCount == 0) list->head = list->tail = node;
    else {
        node->next = list->head; // Set the formet head as the new node's next
        list->head = node; // Set the new head
    }
    list->nodeCount++; // Increase the node count
}

void sllist_insert(sllist_t* list, void* data, size_t index){
    sllist_node_t* node = malloc(sizeof(sllist_node_t));
    node->data = data;

    // Index can't be greater than the node count.
    // Print an error and return
    if(index > list->nodeCount) {
        fprintf(stderr, "sllist: index exceeds linked list size!\n");
        return;
    }

    if(list->nodeCount == 0) list->head = list->tail = node; //...
    else { 
        size_t i = 0;
        sllist_node_t* prev = list->head;

        // If the index is the start or the end of the list + 1, then
        // Use these functions for that
        if(index == 0) {
            return sllist_insert_start(list, data);
        } else if(index == list->nodeCount){
            return sllist_insert_end(list, data);
        }
        
        // Insert the element
        sllist_foreach(list, current){
            if(i == index){
                prev->next = node; // prev's next is set to the new node 
                node->next = current; // the new node's next is set to the current node (the node
                                      // which's place has been taken by the new node)
                break; // Done
            }
            prev = current;
            i++;
        }
    }
    list->nodeCount++; //...

    return;
}

void sllist_remove(sllist_t* list, void* data){
    sllist_node_t* prev = list->head;

    sllist_foreach(list, current){
        if(current->data == data){
            if(list->nodeCount == 1){
                // The only element in the list is removed
                list->head = list->tail = NULL;
            } else if(current == list->head){
                // The head of the list is removed
                list->head = current->next;
            } else if(current == list->tail){
                // The tail of the list is removed
                list->tail = prev;
                prev->next = NULL;
            } else {
                // A node in the middle of the list is removed
                prev->next = current->next;
            }
            free(current); // Free the removed node
            list->nodeCount--; // Decrement the node count
            return;
        }
        prev = current; // save the previous node
    }
    // If the foreach loop terminates then the element to be removed wasn't found.
    // Print an error and return
    fprintf(stderr, "sllist: could not find the node to delete!\n");
    return;
}

void sllist_remove_by_index(sllist_t* list, size_t index){
    // If the index is greater than the greatest index (nodeCound-1) or there are no nodes,
    // Print an error and return
    if(list->nodeCount == 0 || index > list->nodeCount-1){
        fprintf(stderr, "sllist: index exceeds linked list size!\n");
        return;
    }

    // Find and remove the indexed node
    // FIXME: This executes the same loop 2 times (maybe make an internal __sllist_remove_node() or something)
    int i = 0;
    sllist_foreach(list, current){
        if(i == index) return sllist_remove(list, current->data);
        i++;
    }
}

void* sllist_search(sllist_t* list, size_t index){
    // (Same as sllist_remove_by_index)
    if(list->nodeCount == 0 || index > list->nodeCount-1){
        fprintf(stderr, "sllist: index exceeds linked list size!\n");
        return NULL;
    }

    // Find the indexed node
    int i = 0;
    sllist_foreach(list, current){
        if(i == index) return current->data;
        i++;
    }
    return NULL;
}