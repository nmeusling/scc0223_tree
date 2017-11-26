/*
 * Natalie Menato
 * Numero USP: 10295051
 * 26/11/2017
 * Submissao para SCC0223 Trabalho 2 - parte 2
 *
 */


#include <stdio.h>
#include <stdlib.h>

//no da fila
typedef struct queue_block queue_node;

//fila
typedef struct {
    queue_node *first, *last;
} Queue;

//cria e incicializa a fila
void create_queue(Queue *);

//inserir um elemento no fim da fila
int insert_queue(Queue *, void *);

//remove o primeiro elemento da fila
void *remove_queue(Queue *);

//verifica se a fila esta vazia
int is_empty(Queue *);

//exclui todos os elementos da fila, liberando a memoria
void destroy_queue(Queue *Q);

