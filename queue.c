/*
 * Natalie Menato
 * Numero USP: 10295051
 * 26/11/2017
 * Submissao para SCC0223 Trabalho 2 - parte 2
 *
 */

#include "queue.h"

//no para fila, cada elemento e um pointeiro
struct queue_block {
    void *info;
    struct queue_block *next;
};

//inicializa a fila
void create_queue(Queue *Q) {
    Q->first=NULL;
    Q->last=NULL;
}

//insere na fila, insere no fim
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

//removo o ultimo no da fila, retorna o valor removido
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

//remove todos os elementas da fila, liberando a memoria
void destroy_queue(Queue *Q){
    while(!is_empty(Q)){
        remove_queue(Q);
    }
}

//verifica se a fila esta vazia
int is_empty(Queue *Q) {
    if (Q->first==NULL)
        return(1);
    else return(0);
}

