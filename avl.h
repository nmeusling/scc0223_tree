/*
 * Natalie Menato
 * Numero USP: 10295051
 * 26/11/2017
 * Submissao para SCC0223 Trabalho 2 - parte 2
 *
 */

#ifndef SCC0223_TREE_AVL_H
#define SCC0223_TREE_AVL_H

#include <stdlib.h>

typedef char elem;

//no da arvore avl
typedef struct block_avl {
    elem info;
    int fb;
    struct block_avl *left, *right;
} node_avl;

//arvore avl
typedef struct {
    node_avl *root;
} avl;


//função para criar/inicializar a AVL
void create_avl(avl*);

//função para finalizar a AVL; deve começar com p=raiz
void destroy_avl(node_avl**);

//imprime os elementos da árvore
void print_avl(node_avl**);

//chama as funcoes para inserir na arovor avl
int insert_avl(node_avl**,elem*);


#endif //SCC0223_TREE_AVL_H
