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
void create_tree_avl(char * str, avl *a);

int main(){
    char input[CHAR_LIMIT +1];
    int full;
    Tree T;
    avl tree_avl;

    input_tree(input);

    create(&T);
    create_tree(input, &T);
    printf("\nArvore: \n");
    print_tree(T.root);
    printf("\nAltura da arvore: %d", height(T.root));
    printf("\nNumero de nós folhas: %d", num_leaves(T.root));
    printf("\n0 - Nao, 1 - Sim");
    printf("\nA arvore esta cheia?: %d", is_full(T.root));
    printf("\nA arvore e ABB?: %d", is_abb(T.root));
    printf("\nA arvore e AVL?: %d", is_avl(T.root));
    printf("\nOrdenada em Pre-order?: %d", preorder(T.root));
    printf("\nOrdenada em ordem?: %d", inorder(T.root));
    printf("\nOrdenada em Pos-order?: %d", postorder(T.root));


    create_avl(&tree_avl);
    create_tree_avl(input, &tree_avl);

    printf("\n----------------------------------------------");
    printf("\nArvore AVL: \n");
    print_avl(&tree_avl.root);
    printf("\nAltura da arvore: %d", height(tree_avl.root));
    printf("\nNumero de nós folhas: %d", num_leaves(tree_avl.root));
    printf("\n0 - Nao, 1 - Sim");
    printf("\nA arvore esta cheia?: %d", is_full(tree_avl.root));
    printf("\nA arvore e ABB?: %d", is_abb(tree_avl.root));
    printf("\nA arvore e AVL?: %d", is_avl(tree_avl.root));
    printf("\nOrdenada em Pre-order?: %d", preorder(tree_avl.root));
    printf("\nOrdenada em Ordem?: %d", inorder(tree_avl.root));
    printf("\nOrdenada em Pos-order?: %d", postorder(tree_avl.root));

}

//Pede para o usuario inserir o chars representando a arvore
void input_tree(char * input){
    int length;
    printf("Insere ate %d caraters: ", CHAR_LIMIT);
    fgets(input, CHAR_LIMIT+1, stdin);
    length = strlen(input);
    //se o enter foi considerado no string, tira e coloca null
    if(input[length-1] == 10){
        input[length-1] = 0;
    }
}

//Funcao para inserir os nos representados no input string
void create_tree(char * str, Tree *T){
    int i, length = strlen(str), spaces = 0;
    for(i=0; i<length;i++){
        //se o char e um espaco
        if(str[i] == 32){
            spaces ++;
        }
        else{
            //insere o elemento, especificando quantos nos vazios (spaces) devem ir antes do no desejado
            insert_width(T, &(str[i]),spaces);
            spaces = 0;
        }
    }


}

//Funcao para inserir os nos representados no input string
void create_tree_avl(char * str, avl *a){
    int i, length = strlen(str);
    for(i=0; i<length;i++){
        if(str[i] != 32){
            insert_avl(&a->root, &str[i]);
        }
    }
}