/*
 * Natalie Menato
 * Numero USP: 10295051
 * 26/11/2017
 * Submissao para SCC0223 Trabalho 2 - parte 2
 *
 */

#include "avl.h"
#include <stdio.h>


/*
 * Função para criar/inicializar a AVL
 */
void create_avl(avl *A) {
    A->root = NULL;
}

/*
 * Função para finalizar a AVL; deve começar com p=raiz
 */
void destroy_avl(node_avl **p) {
    if (*p != NULL) {
        destroy_avl(&(*p)->left);
        destroy_avl(&(*p)->right);
        free(*p);
    }
}

/*
 * Imprime os elementos da árvore
 */
void print_avl(node_avl **p) {
    if (*p != NULL) {
        printf("%c/%d(", (*p)->info, (*p)->fb);
        print_avl(&(*p)->left);
        printf(",");
        print_avl(&(*p)->right);
        printf(")");
    } else printf("null");
}

/*
 * Fazer rotacao esquerda-esquerda
 */
void EE(node_avl **r) {
    node_avl *pai = *r;
    node_avl *filho = pai->left;
    pai->left = filho->right;
    filho->right = pai;
    pai->fb = 0;
    filho->fb = 0;
    *r = filho;
}

/*
 * Fazer rotacao direita-direita
 */
void DD(node_avl **r) {
    node_avl *pai = *r;
    node_avl *filho = pai->right;
    pai->right = filho->left;
    filho->left = pai;
    pai->fb = 0;
    filho->fb = 0;
    *r = filho;
}

/*
 * Fazer rotacao esquerda-direita
 */
void ED(node_avl **r) {
    node_avl *pai = *r;
    node_avl *filho = pai->left;
    node_avl *neto = filho->right;
    pai->left = neto->right;
    filho->right = neto->left;
    neto->left = filho;
    neto->right = pai;
    switch (neto->fb) {
        case -1:
            pai->fb = 1;
            filho->fb = 0;
            break;
        case 0:
            pai->fb = 0;
            filho->fb = 0;
            break;
        case 1:
            pai->fb = 0;
            filho->fb = -1;
            break;
    }
    neto->fb = 0;
    *r = neto;
}

/*
 * Fazer rotacao direita-esquerda
 */
void DE(node_avl **r) {
    node_avl *pai = *r;
    node_avl *filho = pai->right;
    node_avl *neto = filho->left;
    filho->left = neto->right;
    pai->right = neto->left;
    neto->left = pai;
    neto->right = filho;
    switch (neto->fb) {
        case -1:
            pai->fb = 0;
            filho->fb = 1;
            break;
        case 0:
            pai->fb = 0;
            filho->fb = 0;
            break;
        case 1:
            pai->fb = -1;
            filho->fb = 0;
            break;
    }
    neto->fb = 0;
    *r = neto;
}

/*
 * Insere um novo elemento no avl, fazendo rotacao se necessario
 */
int insert_avl_aux(node_avl **p, elem *x, int *grew) {
    if (*p == NULL) {
        *p = (node_avl *) malloc(sizeof(node_avl));
        (*p)->info = *x;
        (*p)->fb = 0;
        (*p)->left = NULL;
        (*p)->right = NULL;
        *grew = 1;
        return 1;
    } else if (*x == (*p)->info)
        return 0;
    else if (*x < (*p)->info) {
        if (insert_avl_aux(&(*p)->left, x, grew)) {
            if (*grew) {
                switch ((*p)->fb) {
                    case -1:
                        if ((*p)->left->fb == -1)
                            EE(p);
                        else ED(p);
                        *grew = 0;
                        break;
                    case 0:
                        (*p)->fb = -1;
                        *grew = 1;
                        break;
                    case 1:
                        (*p)->fb = 0;
                        *grew = 0;
                        break;
                }
            }
            return 1;
        } else return 0;
    } else {
        if (insert_avl_aux(&(*p)->right, x, grew)) {
            if (*grew) {
                switch ((*p)->fb) {
                    case -1:
                        (*p)->fb = 0;
                        *grew = 0;
                        break;
                    case 0:
                        (*p)->fb = 1;
                        *grew = 1;
                        break;
                    case 1:
                        if ((*p)->right->fb == 1)
                            DD(p);
                        else DE(p);
                        *grew = 0;
                        break;
                }
            }
            return 1;
        } else return 0;
    }
}

/*
 * Chama as funcoes para inserir na arovor avl
 */
int insert_avl(node_avl **p, elem *x) {
    int cresceu;
    return insert_avl_aux(p, x, &cresceu);
}


/*
 * Função para computar a altura de uma árvore binária onde o node p é a raiz
 */
int height_avl(node_avl *p) {
    int h_left, h_right;

    if (p == NULL)
        return (0);
    else {
        h_left = 1 + height_avl(p->left);
        h_right = 1 + height_avl(p->right);
        if (h_left > h_right)
            return (h_left);
        else return (h_right);
    }
}

/*
 * Conta o numbero de nos folhas na arvore
 */
int num_leaves_avl(node_avl *p) {
    if (p->left == NULL && p->right == NULL)
        return 1;
    else if (p->left == NULL)
        return num_leaves_avl(p->right);
    else if (p->right == NULL)
        return num_leaves_avl(p->left);
    else
        return num_leaves_avl(p->left) + num_leaves_avl(p->right);

}

/*
 * Verifica se a arvore e cheia
 */
int is_full_avl(node_avl *p) {
    int h, i, max_leaves = 1;
    h = height_avl(p);
    for (i = 1; i < h; i++) {
        max_leaves = max_leaves * 2;
    }

    if (num_leaves_avl(p) == max_leaves)
        return 1;
    else
        return 0;
}

/*
 * Verifica se uma arvore e abb
 */
int is_abb_avl(node_avl *p) {
    int result;
    if (p == NULL)
        return 1;
    else if (p->left == NULL && p->right == NULL)
        return 1;
    else if (p->left == NULL)
        result = (p->right->info > p->info) && is_abb_avl(p->left) && is_abb_avl(p->right);
    else if (p->right == NULL)
        result = (p->left->info < p->info) && is_abb_avl(p->left) && is_abb_avl(p->right);
    else
        result = (p->left->info < p->info) && (p->right->info > p->info) && is_abb_avl(p->left) && is_abb_avl(p->right);

    return result;
}

/*
 * Verifica se altura das subarvores direita e esquerda de todas as subarvores
 */
int is_avl_aux_avl(node_avl *p) {
    int height_difference;
    if (p == NULL)
        return 1;

    height_difference = height_avl(p->right) - height_avl(p->left);
    if (height_difference < -1 || height_difference > 1)
        return 0;
    else
        return (is_avl_avl(p->left) && is_avl_avl(p->right));

}

/*
 * Verifica se uma arvore e avl
 */
int is_avl_avl(node_avl *p) {
    if (!is_abb_avl(p))
        return 0;
    else
        return is_avl_aux_avl(p);
}


/*
 * Verifica se os elementos da arvore estao ordenada com precurso pre-order
 */
int preorder_aux_avl(node_avl *p, elem *prev) {
    if (p == NULL)
        return 1;
    if (*prev > p->info)
        return 0;
    else {
        *prev = p->info;
        return preorder_aux_avl(p->left, prev) && preorder_aux_avl(p->right, prev);
    }
}

/*
 * Chama a funcao para verifcar se a arvore fica ordenado com precurso pre-order
 */
int preorder_avl(node_avl *p) {
    int result;
    elem *prev = (elem *) malloc(sizeof(elem));
    *prev = p->info;
    result = preorder_aux_avl(p, prev);
    free(prev);
    return result;
}

/*
 * Verifica se os elementos da arvore estao ordenada com precurso em ordem
 */
int inorder_aux_avl(node_avl *p, elem *prev) {

    if (p == NULL)
        return 1;
    //*prev = p->info;

    if (!inorder_aux_avl(p->left, prev))
        return 0;
    if (*prev > p->info)
        return 0;
    *prev = p->info;
    if (!inorder_aux_avl(p->right, prev))
        return 0;
    else
        return 1;
}

/*
 * Chama a funcao para verifcar se a arvore fica ordenado com precurso em ordem
 */
int inorder_avl(node_avl *p) {
    int result;
    elem prev = 0;
    result = inorder_aux_avl(p, &prev);
    return result;
}

/*
 * Verifica se os elementos da arvore estao ordenada com precurso pos-order
 */
int postorder_aux_avl(node_avl *p, elem *prev) {
    if (p == NULL)
        return 1;

    *prev = p->info;
    if (!postorder_aux_avl(p->left, prev))
        return 0;
    else if (!postorder_aux_avl(p->right, prev))
        return 0;
    else if (*prev > p->info)
        return 0;
    else
        return 1;
}

/*
 * Chama a funcao para verifcar se a arvore fica ordenado com precurso pos-order
 */
int postorder_avl(node_avl *p) {
    int result;
    elem prev = 0;
    result = postorder_aux_avl(p, &prev);
    return result;
}

