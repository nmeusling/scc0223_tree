//
// Created by nmeusling on 23/11/17.
//

#include "avl.h"

#include <stdio.h>


//função para criar/inicializar a AVL
void create_avl(avl *A) {
    A->root=NULL;
}

//função para finalizar a AVL; deve começar com p=raiz
void destroy_avl(node_avl **p) {
    if (*p!=NULL) {
        destroy_avl(&(*p)->left);
        destroy_avl(&(*p)->right);
        free(*p);
    }
}

//imprime os elementos da árvore
void print_avl(node_avl **p) {
    if (*p!=NULL) {
        printf("%c/%d(",(*p)->info,(*p)->fb);
        print_avl(&(*p)->left);
        printf(",");
        print_avl(&(*p)->right);
        printf(")");
    }
    else printf("=");
}

//função de busca de um elemento na AVL; deve começar com p=raiz
int buscar(node_avl **p, int *x) {
    if (*p==NULL)
        return 0;
    else if (*x<(*p)->info)
        return(buscar(&(*p)->left,x));
    else if (*x>(*p)->info)
        return(buscar(&(*p)->right,x));
    else return 1;
}

//funções para inserção de um elemento na AVL
//a variável "cresceu" indica se a árvore cresceu após a inserção
void EE(node_avl **r) {
    node_avl *pai=*r;
    node_avl *filho=pai->left;
    pai->left=filho->right;
    filho->right=pai;
    pai->fb=0;
    filho->fb=0;
    *r=filho;
}

void DD(node_avl **r) {
    node_avl *pai=*r;
    node_avl *filho=pai->right;
    pai->right=filho->left;
    filho->left=pai;
    pai->fb=0;
    filho->fb=0;
    *r=filho;
}

void ED(node_avl **r) {
    node_avl *pai=*r;
    node_avl *filho=pai->left;
    node_avl *neto=filho->right;
    pai->left=neto->right;
    filho->right=neto->left;
    neto->left=filho;
    neto->right=pai;
    switch (neto->fb) {
        case -1:
            pai->fb=1;
            filho->fb=0;
            break;
        case 0:
            pai->fb=0;
            filho->fb=0;
            break;
        case 1:
            pai->fb=0;
            filho->fb=-1;
            break;
    }
    neto->fb=0;
    *r=neto;
}

void DE(node_avl **r) {
    node_avl *pai=*r;
    node_avl *filho=pai->right;
    node_avl *neto=filho->left;
    filho->left=neto->right;
    pai->right=neto->left;
    neto->left=pai;
    neto->right=filho;
    switch (neto->fb) {
        case -1:
            pai->fb=0;
            filho->fb=1;
            break;
        case 0:
            pai->fb=0;
            filho->fb=0;
            break;
        case 1:
            pai->fb=-1;
            filho->fb=0;
            break;
    }
    neto->fb=0;
    *r=neto;
}

int insert_avl_aux(node_avl **p, elem *x, int *grew) {
    if (*p==NULL) {
        *p=(node_avl*) malloc(sizeof(node_avl));
        (*p)->info=*x;
        (*p)->fb=0;
        (*p)->left=NULL;
        (*p)->right=NULL;
        *grew=1;
        return 1;
    }
    else if (*x==(*p)->info)
        return 0;
    else if (*x<(*p)->info) {
        if (insert_avl_aux(&(*p)->left,x,grew)) {
            if (*grew) {
                switch ((*p)->fb) {
                    case -1:
                        if ((*p)->left->fb==-1)
                            EE(p);
                        else ED(p);
                        *grew=0;
                        break;
                    case 0:
                        (*p)->fb=-1;
                        *grew=1;
                        break;
                    case 1:
                        (*p)->fb=0;
                        *grew=0;
                        break;
                }
            }
            return 1;
        }
        else return 0;
    }
    else {
        if (insert_avl_aux(&(*p)->right,x,grew)) {
            if (*grew) {
                switch ((*p)->fb) {
                    case -1:
                        (*p)->fb=0;
                        *grew=0;
                        break;
                    case 0:
                        (*p)->fb=1;
                        *grew=1;
                        break;
                    case 1:
                        if ((*p)->right->fb==1)
                            DD(p);
                        else DE(p);
                        *grew=0;
                        break;
                }
            }
            return 1;
        }
        else return 0;
    }
}

int insert_avl(node_avl **p, elem *x) {
    int cresceu;
    return insert_avl_aux(p, x, &cresceu);
}