#include "dllist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

dllist_t* dllist_create(){
    dllist_t* list = malloc(sizeof(dllist_t)); // Allocate the dllist
    memset(list, 0, sizeof(dllist_t)); // Zero out the dllist structure
    return list; // Return the dllist pointer
}

void dllist_destroy(dllist_t* list){
    dllist_node_t* node = list->head;
    dllist_node_t* nextNode;

    // Destroy each node
    while(node != NULL){
        nextNode = node->next;
        free(node);
        node = nextNode;
    }
    // Finally, free the list itself
    free(list);
}

void dllist_insert_end(dllist_t* list, void* data){
    // Allocate the new node and set it's fields to the correct values
    dllist_node_t* node = malloc(sizeof(dllist_node_t));
    node->next = NULL;
	node->prev = list->tail;
    node->data = data;

    // If the list has no elements, then the first
    // One to be inserted will be both it's head and it's tail
    if(list->nodeCount == 0) list->head = list->tail = node;
    else {
        list->tail->next = node; // Set the former tail's next pointer
        list->tail = node; // Set the new tail
    }
    list->nodeCount++; // Increase the node count
}

void dllist_insert_start(dllist_t* list, void* data){
    // (Same as dllist_insert_end)
    dllist_node_t* node = malloc(sizeof(dllist_node_t));
    node->data = data;
	node->next = NULL;
	node->prev = NULL;

    // (Same as dllist_insert_end)
    if(list->nodeCount == 0) list->head = list->tail = node;
    else {
        node->next = list->head; // Set the formet head as the new node's next
        list->head = node; // Set the new head
    }
    list->nodeCount++; // Increase the node count
}

void dllist_insert(dllist_t* list, void* data, size_t index){
    dllist_node_t* node = malloc(sizeof(dllist_node_t));
    node->data = data;
	node->next = node->prev = NULL;

    // Index can't be greater than the node count.
    // Print an error and return
    if(index > list->nodeCount) {
        fprintf(stderr, "dllist: index exceeds linked list size!\n");
        return;
    }

    if(list->nodeCount == 0) list->head = list->tail = node; //...
    else { 
        size_t i = 0;
        dllist_node_t* prev = list->head;

        // If the index is the start or the end of the list + 1, then
        // Use these functions for that
        if(index == 0) {
            return dllist_insert_start(list, data);
        } else if(index == list->nodeCount){
            return dllist_insert_end(list, data);
        }
        
        // Insert the element
        dllist_foreach(list, current){
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

static void __dllist_remove_node(dllist_t* list, dllist_node_t* node){
	if(list->nodeCount == 1){
        // The only element in the list is removed
        list->head = list->tail = NULL;
	} else if(node == list->head){
        // The head of the list is removed
        list->head = node->next;
		if(node->next) node->next->prev = NULL;
    } else if(node == list->tail){
        // The tail of the list is removed
	    list->tail = node->prev;
    	node->prev->next = NULL;
    } else {
        // A node in the middle of the list is removed
        node->prev->next = node->next;
		node->next->prev = node->prev;
    }
    free(node); // Free the removed node
    list->nodeCount--; // Decrement the node count
    return;
}

void dllist_remove(dllist_t* list, void* data){
    dllist_foreach(list, current){
        if(current->data == data){
        	__dllist_remove_node(list, current);
		}
    }
    // If the foreach loop terminates then the element to be removed wasn't found.
    // Print an error and return
    fprintf(stderr, "dllist: could not find the node to delete!\n");
    return;
}

void dllist_remove_by_index(dllist_t* list, size_t index){
    // If the index is greater than the greatest index (nodeCound-1) or there are no nodes,
    // Print an error and return
    if(list->nodeCount == 0 || index > list->nodeCount-1){
        fprintf(stderr, "dllist: index exceeds linked list size!\n");
        return;
    }

    int i = 0;

	dllist_foreach(list, current){
        if(i == index) {
			__dllist_remove_node(list, current);
			break;
		}
		i++;
    }
}

void* dllist_search(dllist_t* list, size_t index){
    // (Same as dllist_remove_by_index)
    if(list->nodeCount == 0 || index > list->nodeCount-1){
        fprintf(stderr, "dllist: index exceeds linked list size!\n");
        return NULL;
    }

    // Find the indexed node
    int i = 0;
    dllist_foreach(list, current){
        if(i == index) return current->data;
        i++;
    }
    return NULL;
}
