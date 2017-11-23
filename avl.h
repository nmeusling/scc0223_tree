//
// Created by nmeusling on 23/11/17.
//

#ifndef SCC0223_TREE_AVL_H
#define SCC0223_TREE_AVL_H

#include <stdlib.h>
//declaração do nó da árvore
typedef char elem;

typedef struct block_avl {
    elem info;
    int fb;
    struct block_avl *left, *right;
} node_avl;

typedef struct {
    node_avl *root;
} avl;


//protótipos das funções
void create_avl(avl*);
void destroy_avl(node_avl**);
void print_avl(node_avl**);
int insert_avl(node_avl**,elem*);
int search_avl(node_avl**,elem*);

#endif //SCC0223_TREE_AVL_H