//
// Created by nmeusling on 18/11/17.
//
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
    input_tree(input);
    Tree T;
    create(&T);
    create_tree(input, &T);
    printf("\nArvore: \n");
    print_tree(T.root);
    printf("\nAltura da arvore: %d", height(T.root));
    printf("\nNumero de nós folhas: %d", num_leaves(T.root));
    printf("\nA arvore esta cheia?: %d", is_full(T.root));
    printf("\nA arvore e ABB?: %d", is_abb(T.root));
    printf("\nA arvore e AVL?: %d", is_avl(T.root));
    printf("\nPreorderd?: %d", preorder(T.root));
    printf("\nEmorderd?: %d", inorder(T.root));
    printf("\nPostorderd?: %d", postorder(T.root));

    avl tree_avl;
    create_avl(&tree_avl);
    create_tree_avl(input, &tree_avl);
    printf("\n----------------------------------------------");
    printf("\n\nArvore AVL: \n");
    print_avl(&tree_avl.root);
    printf("\nAltura da arvore: %d", height(tree_avl.root));
    printf("\nNumero de nós folhas: %d", num_leaves(tree_avl.root));
    printf("\nA arvore esta cheia?: %d", is_full(tree_avl.root));
    printf("\nA arvore e ABB?: %d", is_abb(tree_avl.root));
    printf("\nA arvore e AVL?: %d", is_avl(tree_avl.root));
    printf("\nPreorderd?: %d", preorder(tree_avl.root));
    printf("\nEmorderd?: %d", inorder(tree_avl.root));
    printf("\nPostorderd?: %d", postorder(tree_avl.root));


    //is_ordered(T.root, 0);
    //preorder(T.root, input, 0);
    //print_array(input);



    //ignore NL
}

void input_tree(char * input){
    int length;
    printf("Insere ate %d caraters: ", CHAR_LIMIT);
    fgets(input, CHAR_LIMIT+1, stdin);
    length = strlen(input);
    //if enter was included in string
    if(input[length-1] == 10){
        input[length-1] = 0;
    }
}

void create_tree(char * str, Tree *T){
    int i, length = strlen(str), spaces = 0;
    for(i=0; i<length;i++){
        if(str[i] == 32){
            spaces ++;
        }
        else{
            insert_width(T, &(str[i]),spaces);
            spaces = 0;
        }
    }


}

void create_tree_avl(char * str, avl *a){
    int i, length = strlen(str);
    for(i=0; i<length;i++){
        if(str[i] != 32){
            insert_avl(&a->root, &str[i]);
        }
    }
}