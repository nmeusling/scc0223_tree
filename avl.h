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
void create_avl(avl *);

//função para finalizar a AVL; deve começar com p=raiz
void destroy_avl(node_avl **);

//imprime os elementos da árvore
void print_avl(node_avl **);

//chama as funcoes para inserir na arovor avl
int insert_avl(node_avl **, elem *);

//função para computar a altura de uma árvore binária onde o node p é a raiz
int height_avl(node_avl *p);

//conta o numbero de nos folhas na arvore
int num_leaves_avl(node_avl *p);

//verifica se a arvore e cheia
int is_full_avl(node_avl *p);

//verifica se uma arvore e abb
int is_abb_avl(node_avl *p);

//verifica se uma arvore e avl
int is_avl_avl(node_avl *p);

//chama a funcao para verifcar se a arvore fica ordenado com precurso pre-order
int preorder_avl(node_avl *p);

//chama a funcao para verifcar se a arvore fica ordenado com precurso em ordem
int inorder_avl(node_avl *p);

//chama a funcao para verifcar se a arvore fica ordenado com precurso pos-order
int postorder_avl(node_avl *p);

#endif //SCC0223_TREE_AVL_H
