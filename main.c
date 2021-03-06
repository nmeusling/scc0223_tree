/*
 * Natalie Menato
 * Numero USP: 10295051
 * 26/11/2017
 * Submissao para SCC0223 Trabalho 2 - parte 2
 *
 */
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "avl.h"


void input_tree(char *);

void create_tree(char *, Tree *T);

void create_tree_avl(char *str, avl *a);

void print_result(int resultado);

int main() {
    char input[CHAR_LIMIT + 1];
    int resultado;
    Tree T;
    avl tree_avl;

    input_tree(input);

    create(&T);
    create_tree(input, &T);
    printf("\nArvore: \n");
    print_tree(T.root);
    printf("\nAltura da arvore: %d", height(T.root));
    printf("\nNumero de nos folhas: %d", num_leaves(T.root));

    printf("\nA arvore esta cheia?: ");
    print_result(is_full(T.root));

    printf("\nA arvore e ABB?: ");
    print_result(is_abb(T.root));

    printf("\nA arvore e AVL?: ");
    print_result(is_avl(T.root));

    printf("\nOrdenada em Pre-order?: ");
    print_result(preorder(T.root));

    printf("\nOrdenada em ordem?: ");
    print_result(inorder(T.root));

    printf("\nOrdenada em Pos-order?: ");
    print_result(postorder(T.root));


    create_avl(&tree_avl);
    create_tree_avl(input, &tree_avl);

    printf("\n----------------------------------------------");
    printf("\nArvore AVL: \n");
    print_avl(&tree_avl.root);
    printf("\nAltura da arvore: %d", height_avl(tree_avl.root));
    printf("\nNumero de nos folhas: %d", num_leaves_avl(tree_avl.root));

    printf("\nA arvore esta cheia?: ");
    print_result(is_full_avl(tree_avl.root));

    printf("\nA arvore e ABB?: ");
    print_result(is_abb_avl(tree_avl.root));

    printf("\nA arvore e AVL?: ");
    print_result(is_avl_avl(tree_avl.root));

    printf("\nOrdenada em Pre-order?: ");
    print_result(preorder_avl(tree_avl.root));

    printf("\nOrdenada em Ordem?: ");
    print_result(inorder_avl(tree_avl.root));

    printf("\nOrdenada em Pos-order?: ");
    print_result(postorder_avl(tree_avl.root));
    printf("\n");

}

/*
 * Pede para o usuario inserir o chars representando a arvore
 */
void input_tree(char *input) {
    int length;
    printf("Insere ate %d caraters: ", CHAR_LIMIT);
    fgets(input, CHAR_LIMIT + 1, stdin);
    length = (int) strlen(input);
    //se o enter foi considerado no string, tira e coloca null
    if (input[length - 1] == 10) {
        input[length - 1] = 0;
    }
}

/*
 * Funcao para inserir os nos representados no input string
 */
void create_tree(char *str, Tree *T) {
    int i, length = (int) strlen(str), spaces = 0;
    for (i = 0; i < length; i++) {
        //se o char e um espaco
        if (str[i] == 32) {
            spaces++;
        } else {
            //insere o elemento, especificando quantos nos vazios (spaces) devem ir antes do no desejado
            insert_width(T, &(str[i]), spaces);
            spaces = 0;
        }
    }


}

/*
 * Funcao para inserir os nos representados no input string
 */
void create_tree_avl(char *str, avl *a) {
    int i, length = (int) strlen(str);
    for (i = 0; i < length; i++) {
        if (str[i] != 32) {
            insert_avl(&a->root, &str[i]);
        }
    }
}

void print_result(int resultado) {
    if (resultado)
        printf("Sim");
    else
        printf("Não");
}