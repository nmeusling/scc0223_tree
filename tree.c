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


//insere um elemento em largura com um dado numero de nos anteriores vazios, retorna 0 se nao foi possivel inserir
int insert_width(Tree *T, elem *x, int preceding_blanks) {
    //conta quantos nos vazios ja tem sido inserido na arvore
    int skipped = 0; //nos vazios consecutivos
    int total_skipped = 0; //total vazio na arvore
    Queue Q;
    node *removed;
    create_queue(&Q);
    //cria o novo no
    node *p = (node *) malloc(sizeof(node));
    if (p == NULL)
        return 0;
    p->info = *x;
    p->left = NULL;
    p->right = NULL;
    //arvore e vazia
    if (T->root == NULL) {
        T->root = p;
        return 0;
    }
    //usa fila para adicionar os elementos em largura
    insert_queue(&Q, T->root);
    while (!is_empty(&Q)) {
        removed = remove_queue(&Q);
        //se tem um no nulo na fila
        if(removed == NULL){
            //numero de nos vazio na proxima nivel da arvore e 2
            total_skipped +=2;
            skipped += 2;
            //insere os dos nos nulos na fila
            insert_queue(&Q, NULL);
            insert_queue(&Q, NULL);
        }
        else {
            if (removed->left == NULL) {
                //se tem o numero correto de nos vazios antes do novo no, insere p
                if (preceding_blanks == skipped && T->skipped + preceding_blanks== total_skipped) {
                    removed->left = p;
                    T->skipped += preceding_blanks;
                    return 0;
                } else {
                    //deixa o no nulo, incrementa o numero de nos vazios
                    insert_queue(&Q, NULL);
                    skipped ++;
                    total_skipped ++;
                }
            } else if (removed->left != NULL) {
                //insere o no na fila
                skipped = 0;
                insert_queue(&Q, removed->left);
            }
            if (removed->right == NULL) {
                //se tem o numero correto de nos vazios antes do novo no, insere p
                if (preceding_blanks == skipped && T->skipped + preceding_blanks== total_skipped) {
                    removed->right = p;
                    T->skipped +=preceding_blanks;
                    return 0;
                } else {
                    //deixa o no nulo, incrementa o numero de nos vazios
                    insert_queue(&Q, NULL);
                    skipped ++;
                    total_skipped ++;
                }
            } else if (removed->right != NULL) {
                //insere o no na fila
                skipped = 0;
                insert_queue(&Q, removed->right);
            }
        }
    }
    //libera memoria da fila
    destroy_queue(&Q);
    return 1;
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

//libera toda a memória usada na árvore
void destroy_tree(node *p) {
    if (p != NULL) {
        destroy_tree(p->left);
        destroy_tree(p->right);
        free(p);
    }
}

//função para computar a altura de uma árvore binária onde o node p é a raiz
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

//conta o numbero de nos folhas na arvore
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

//verifica se a arvore e cheia
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

//verifica se uma arvore e abb
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

//verifica se uma arvore e avl
int is_avl(node *p){
    if(!is_abb(p))
        return 0;
    else
        return is_avl_aux(p);
}

//verifica se altura das subarvores direita e esquerda de todas as subarvores
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

//chama a funcao para verifcar se a arvore fica ordenado com precurso pre-order
int preorder(node * p){
    int result;
    elem * prev = (elem *)malloc(sizeof(elem));
    *prev = p->info;
    result = preorder_aux(p, prev);
    free (prev);
    return result;
}

//verifica se os elementos da arvore estao ordenada com precurso pre-order
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

//chama a funcao para verifcar se a arvore fica ordenado com precurso em ordem
int inorder(node * p){
    int result;
    elem prev = 0;
    result = inorder_aux(p, &prev);
    return result;
}

//verifica se os elementos da arvore estao ordenada com precurso em ordem
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

//chama a funcao para verifcar se a arvore fica ordenado com precurso pos-order
int postorder(node * p){
    int result ;
    elem prev = 0;
    result = postorder_aux(p, &prev);
    return result;
}

//verifica se os elementos da arvore estao ordenada com precurso pos-order
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