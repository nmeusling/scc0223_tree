//
// Created by nmeusling on 19/11/17.
//

#ifndef SCC0223_TREE_QUEUE_H
#define SCC0223_TREE_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct queue_block queue_node;
//typedef void* queue_elem;


typedef struct {
    queue_node *first, *last;
} Queue;

void create_queue(Queue*);
int insert_queue(Queue*,void *);
void * remove_queue(Queue*);
int is_empty(Queue*);
void destroy_queue(Queue *Q);

#endif //SCC0223_TREE_QUEUE_H
