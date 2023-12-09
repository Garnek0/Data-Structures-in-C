#include "sllist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

sllist_t* sllist_create(){
    sllist_t* list = malloc(sizeof(sllist_t));
    memset(list, 0, sizeof(sllist_t));
    return list;
}

void sllist_destroy(sllist_t* list){
    sllist_node_t* node = list->head;
    sllist_node_t* nextNode;
    while(node != NULL){
        nextNode = node->next;
        free(node);
        node = nextNode;
    }
    free(list);
}

void sllist_insert_end(sllist_t* list, void* data){
    sllist_node_t* node = malloc(sizeof(sllist_node_t));
    node->next = NULL;
    node->data = data;

    if(list->nodeCount == 0) list->head = list->tail = node;
    else { 
        list->tail->next = node;
        list->tail = node;
    }
    list->nodeCount++;
}

void sllist_insert_start(sllist_t* list, void* data){
    sllist_node_t* node = malloc(sizeof(sllist_node_t));
    node->data = data;

    if(list->nodeCount == 0) list->head = list->tail = node;
    else {
        node->next = list->head;
        list->head = node;
    }
    list->nodeCount++;
}

void sllist_insert(sllist_t* list, void* data, size_t index){
    sllist_node_t* node = malloc(sizeof(sllist_node_t));
    node->data = data;

    if(index > list->nodeCount) {
        printf("sllist: index exceeds linked list size!\n");
        return;
    }

    if(list->nodeCount == 0) list->head = list->tail = node;
    else { 
        size_t i = 0;
        sllist_node_t* prev = list->head;

        if(index == 0) {
            return sllist_insert_start(list, data);
        } else if(index == list->nodeCount){
            return sllist_insert_end(list, data);
        }
        
        sllist_foreach(list, current){
            if(i == index){
                prev->next = node;
                node->next = current;
                break;
            }
            prev = current;
            i++;
        }
    }
    list->nodeCount++;

    return;
}

void sllist_remove(sllist_t* list, void* data){
    sllist_node_t* prev = list->head;

    sllist_foreach(list, current){
        if(current->data == data){
            if(list->nodeCount == 1){
                list->head = list->tail = NULL;
            } else if(current == list->head){
                list->head = current->next;
            } else if(current == list->tail){
                list->tail = prev;
                prev->next = NULL;
            } else {
                prev->next = current->next;
            }
            free(current);
            list->nodeCount--;
            return;
        }
        prev = current;
    }
    printf("sllist: could not find the node to delete!\n");
    return;
}

void sllist_remove_by_index(sllist_t* list, size_t index){
    if(list->nodeCount == 0 || index > list->nodeCount-1){
        printf("sllist: index exceeds linked list size!\n");
        return;
    }

    int i = 0;
    sllist_foreach(list, current){
        if(i == index) return sllist_remove(list, current->data);
        i++;
    }
}