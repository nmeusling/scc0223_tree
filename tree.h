//
// Created by nmeusling on 19/11/17.
//

#ifndef SCC0223_TREE_TREE_H
#define SCC0223_TREE_TREE_H

typedef char elem;

typedef struct block {
    elem info;
    struct block *left, *right;
}node;

typedef struct {
    struct block *root;
    int skipped;
} Tree;

void create(Tree*);
int isEmpty(Tree*);
node* search(node*,elem*);
node* busca_pai(node*,elem*);
void inserir_esq(Tree*,elem*,elem*,int*);
void inserir_dir(Tree*,elem*,elem*,int*);
void print_tree(node*);
int height(node*);
void finaliza(node*);
void remover(Tree*,elem*,int*);
void percurso_pre_ordem(node*);
void percurso_em_ordem(node*);
void percurso_pos_ordem(node*);
int espelho_similares(node*,node*);
int insert_width(Tree *T, elem *x, int);
int num_leaves(node * p);
int is_full(node *p);

#endif //SCC0223_TREE_TREE_H
