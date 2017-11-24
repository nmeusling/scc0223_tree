/*
 * Natalie Menato
 * Numero USP: 10295051
 * 26/11/2017
 * Submissao para SCC0223 Trabalho 2 - parte 2
 *
 */

#include "tree.h"
#include "queue.h"


//inicializa a árvore, fazendo a raiz igual a NULL
void create(Tree *T) {
    T->root = NULL;
    T->skipped = 0;
}

//verifica se a árvore está vazia
int IsEmpty(Tree *T) {
    if (T->root == NULL)
        return 1;
    else return 0;
}

//busca x na árvore, devendo iniciar com p=raiz ou outro ponto da árvore
node *busca(node *p, elem *x) {
    node *aux;

    if (p == NULL)
        return (NULL);
    else if (p->info == *x)
        return (p);
    else {
        aux = busca(p->left, x);
        if (aux == NULL)
            aux = busca(p->right, x);
        return (aux);
    }
}

//busca pai de x na árvore, devendo iniciar com p=raiz ou outro ponto da árvore
node *busca_pai(node *p, elem *x) {
    node *aux;

    if (p == NULL)
        return (NULL);
    else if ((p->left != NULL) && (p->left->info == *x))
        return (p);
    else if ((p->right != NULL) && (p->right->info == *x))
        return (p);
    else {
        aux = busca_pai(p->left, x);
        if (aux == NULL)
            aux = busca_pai(p->right, x);
        return (aux);
    }
}

int insert_width(Tree *T, elem *x, int preceding_blanks) {
    int skipped = 0;
    int total_skipped = 0;
    Queue Q;
    node *removed;
    create_queue(&Q);
    node *p = (node *) malloc(sizeof(node));
    if (p == NULL)
        return 0;
    p->info = *x;
    p->left = NULL;
    p->right = NULL;
    //tree is empty
    if (T->root == NULL) {
        T->root = p;
        return 0;
    }
    insert_queue(&Q, T->root);
    while (!is_empty(&Q)) {
        removed = remove_queue(&Q);
        if(removed == NULL){
            total_skipped +=2;
            skipped += 2;
            insert_queue(&Q, NULL);
            insert_queue(&Q, NULL);
        }
        else {
            if (removed->left == NULL) {
                if (preceding_blanks == skipped && T->skipped + preceding_blanks== total_skipped) {
                    removed->left = p;
                    T->skipped += preceding_blanks;
                    return 0;
                } else {
                    insert_queue(&Q, NULL);
                    skipped ++;
                    total_skipped ++;
                }
            } else if (removed->left != NULL) {
                skipped = 0;
                insert_queue(&Q, removed->left);
            }
            if (removed->right == NULL) {
                if (preceding_blanks == skipped && T->skipped + preceding_blanks== total_skipped) {
                    removed->right = p;
                    T->skipped +=preceding_blanks;
                    return 0;
                } else {
                    insert_queue(&Q, NULL);
                    skipped ++;
                    total_skipped ++;
                }
            } else if (removed->right != NULL) {
                skipped = 0;
                insert_queue(&Q, removed->right);
            }
        }
    }

    destroy_queue(&Q);
}

//se possível, insere x à esquerda de pai na árvore
//se pai=-1, insere na raiz
void inserir_esq(Tree *T, elem *x, elem *pai, int *erro) {
    node *aux, *p;

    if (*pai != -1) {
        aux = busca(T->root, pai);
        if ((aux != NULL) && (aux->left == NULL)) {
            p = (node *) malloc(sizeof(node));
            p->info = *x;
            p->left = NULL;
            p->right = NULL;
            aux->left = p;
            *erro = 0;
        } else *erro = 1;
    } else if (T->root == NULL) {
        p = (node *) malloc(sizeof(node));
        p->info = *x;
        p->left = NULL;
        p->right = NULL;
        T->root = p;
        *erro = 0;
    } else *erro = 1;
}

//se possível, insere x à direita de pai na árvore
//se pai=-1, insere na raiz
void inserir_dir(Tree *T, elem *x, elem *father, int *erro) {
    node *aux, *p;

    if (*father != -1) {
        aux = busca(T->root, father);
        if ((aux != NULL) && (aux->left == NULL)) {
            p = (node *) malloc(sizeof(node));
            p->info = *x;
            p->left = NULL;
            p->right = NULL;
            aux->right = p;
            *erro = 0;
        } else *erro = 1;
    } else if (T->root == NULL) {
        p = (node *) malloc(sizeof(node));
        p->info = *x;
        p->left = NULL;
        p->right = NULL;
        T->root = p;
        *erro = 0;
    } else *erro = 1;
}

//imprime os elementos da árvore
void print_tree(node *p) {
    if (p != NULL) {
        printf("%c(", p->info);
        print_tree(p->left);
        printf(",");
        print_tree(p->right);
        printf(")");
    } else printf("null");
}

//função para computar a altura de uma árvore binária; devo começar com p
//apontando para a raiz
int height(node *p) {
    int h_left, h_right;

    if (p == NULL)
        return (0);
    else {
        h_left  = 1 + height(p->left);
        h_right = 1 + height(p->right);
        if (h_left > h_right)
            return (h_left);
        else return (h_right);
    }
}

//libera toda a memória usada na árvore
void finaliza(node *p) {
    if (p != NULL) {
        finaliza(p->left);
        finaliza(p->right);
        free(p);
    }
}

//função que remove um elemento da árvore, caso ele esteja nela
void remover(Tree *T, elem *x, int *erro) {
    node *filho, *pai;
    int eh_filho_esq;

    //localizando o nó e o pai dele
    if ((T->root != NULL) && (T->root->info == *x)) {
        pai = NULL;
        filho = T->root;
    } else {
        pai = busca_pai(T->root, x);
        if (pai != NULL) {
            if ((pai->left != NULL) && (pai->left->info == *x)) {
                filho = pai->left;
                eh_filho_esq = 1;
            } else {
                filho = pai->right;
                eh_filho_esq = 0;
            }
        } else filho = NULL;
    }

    if (filho == NULL)
        *erro = 1;
    else {
        //primeiro caso: o nó não tem filhos
        if ((filho->left == NULL) && (filho->right == NULL)) {
            if (pai != NULL) {
                if (eh_filho_esq)
                    pai->left = NULL;
                else pai->right = NULL;
            } else T->root = NULL;
            free(filho);
            *erro = 0;
        }
            //segundo caso: o nó tem um ou dois filhos
        else {
            if (filho->left != NULL) {
                filho->info = filho->left->info;
                filho->left->info = *x;
            } else {
                filho->info = filho->right->info;
                filho->right->info = *x;
            }
            remover(T, x, erro);
        }
    }
}

//função de percurso de pre-ordem na árvore = busca em profundidade
void percurso_pre_ordem(node *p) {
    if (p != NULL) {
        printf("%d\n", p->info);
        percurso_pre_ordem(p->left);
        percurso_pre_ordem(p->right);
    }
}

//função de percurso de em-ordem na árvore
void percurso_em_ordem(node *p) {
    if (p != NULL) {
        percurso_em_ordem(p->left);
        printf("%d\n", p->info);
        percurso_em_ordem(p->right);
    }
}

//função de percurso de pos-ordem na árvore
void percurso_pos_ordem(node *p) {
    if (p != NULL) {
        percurso_pos_ordem(p->left);
        percurso_pos_ordem(p->right);
        printf("%d\n", p->info);
    }
}

//função que verifica se duas árvores são espelho-similares
int espelho_similares(node *p1, node *p2) {
    if ((p1 == NULL) && (p2 == NULL))
        return (1);
    else if ((p1 == NULL) || (p2 == NULL))
        return (0);
    else if ((espelho_similares(p1->left, p2->right)) && (espelho_similares(p1->right, p2->left)))
        return (1);
    else return (0);
}


int num_leaves(node * p){
    if(p->left == NULL && p->right == NULL)
        return 1;
    else if(p->left == NULL)
        return num_leaves(p->right);
    else if(p->right == NULL)
        return num_leaves(p->left);
    else
        return num_leaves(p->left) + num_leaves(p->right);

}

int is_full(node * p){
    int h, i, max_leaves = 1;
    h = height(p);
    for(i = 1; i< h; i++){
        max_leaves = max_leaves*2;
    }

    if(num_leaves(p) == max_leaves)
        return 1;
    else
        return 0;
}

int is_abb(node *p){
    int result;
    if(p == NULL)
        return 1;
    else if(p->left == NULL && p->right == NULL)
        return 1;
    else if(p->left == NULL)
        result = (p->right->info > p->info) && is_abb(p->left) && is_abb(p->right);
    else if(p->right == NULL)
        result = (p->left->info < p->info) && is_abb(p->left) && is_abb(p->right);
    else
        result = (p->left->info < p->info) && (p->right->info > p->info) && is_abb(p->left) && is_abb(p->right);

    return result;
}

int is_avl(node *p){
    return (is_abb(p) && is_avl_aux(p));
}

int is_avl_aux(node *p){
    int height_difference;
    if(p == NULL)
        return 1;

    height_difference = height(p->right) - height(p->left);
    if(height_difference < -1 || height_difference > 1)
        return 0;
    else
        return (is_avl(p->left) && is_avl(p->right));

}

int preorder(node * p){
    int result;
    elem * prev = (elem *)malloc(sizeof(elem));
    *prev = p->info;
    result = preorder_aux(p, prev);
    free (prev);
    return result;
}

int preorder_aux (node * p, elem * prev){
    if(p == NULL)
        return 1;
    if(*prev > p->info)
        return 0;
    else {
        *prev = p->info;
        return preorder_aux(p->left, prev) && preorder_aux(p->right, prev);
    }
}

int inorder(node * p){
    int result;
    elem prev;
    //elem * prev = (elem *)malloc(sizeof(elem));
    prev = 0;
    result = inorder_aux(p, &prev);
    //free (prev);
    return result;
}
//todo more tests
int inorder_aux (node * p, elem * prev){

    if(p == NULL)
        return 1;
    //*prev = p->info;

    if(!inorder_aux(p->left, prev))
        return 0;
    if(*prev > p->info)
        return 0;
    *prev = p->info;
    if(!inorder_aux(p->right, prev))
        return 0;
    else
        return 1;
}

int postorder(node * p){
    int result;
    elem * prev = (elem *)malloc(sizeof(elem));
    *prev = p->info;
    result = postorder_aux(p, prev);
    free (prev);
    return result;
}
//todo more tests
int postorder_aux (node * p, elem * prev){
    if(p == NULL)
        return 1;

    *prev = p->info;
    if (!postorder_aux(p->left, prev))
        return 0;
    else if(!postorder_aux(p->right, prev))
        return 0;
    else if(*prev > p->info)
        return 0;
    else
        return 1;
}