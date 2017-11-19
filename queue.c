//
// Created by nmeusling on 19/11/17.
//

#include "queue.h"


struct queue_block {
    void *info;
    struct queue_block *next;
};


void create_queue(Queue *Q) {
    Q->first=NULL;
    Q->last=NULL;
}


int insert_queue(Queue *Q, void *x) {
    queue_node *p;

    p=(queue_node*) malloc(sizeof(queue_node));
    if (p==NULL)
        return 0;
    else {
        p->info=x;
        p->next=NULL;
        if (Q->first==NULL)
            Q->first=p;
        else Q->last->next=p;
        Q->last=p;
        return 1;
    }
}


void * remove_queue(Queue *Q) {
    queue_node *p;
    void * x;
    if (is_empty(Q))
        return NULL;
    else {
        x=Q->first->info;
        p=Q->first;
        Q->first=Q->first->next;
        if (Q->first==NULL) //para o caso de haver só 1 elemento na fila
            Q->last=NULL;
        free(p);
        return x;
    }
}

void destroy_queue(Queue *Q){
    while(!is_empty(Q)){
        remove_queue(Q);
    }
}

int is_empty(Queue *Q) {
    if (Q->first==NULL)
        return(1);
    else return(0);
}

