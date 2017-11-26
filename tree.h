/*
 * Natalie Menato
 * Numero USP: 10295051
 * 26/11/2017
 * Submissao para SCC0223 Trabalho 2 - parte 2
 *
 */


typedef char elem;
#define CHAR_LIMIT 100

//no da arvore
typedef struct block {
    elem info;
    struct block *left, *right;
} node;

//arvore
typedef struct {
    struct block *root;
    int skipped;
} Tree;

//inicializa a árvore, fazendo a raiz igual a NULL
void create(Tree *);

//verifica se a árvore está vazia
int isEmpty(Tree *);

//insere um elemento em largura com um dado numero de nos anteriores vazios, retorna 0 se nao foi possivel inserir
int insert_width(Tree *T, elem *x, int);

//imprime os elementos da árvore
void print_tree(node *);

//função para computar a altura de uma árvore binária onde o node p é a raiz
int height(node *);

//libera toda a memória usada na árvore
void destroy_tree(node *);

//conta o numbero de nos folhas na arvore
int num_leaves(node *p);

//verifica se a arvore e cheia
int is_full(node *p);

//verifica se uma arvore e abb
int is_abb(node *p);

//verifica se uma arvore e avl
int is_avl(node *p);

//verifica se altura das subarvores direita e esquerda de todas as subarvores
int is_avl_aux(node *p);

//chama a funcao para verifcar se a arvore fica ordenado com precurso pre-order
int preorder(node *p);

//verifica se os elementos da arvore estao ordenada com precurso pre-order
int preorder_aux(node *p, elem *prev);

//chama a funcao para verifcar se a arvore fica ordenado com precurso em ordem
int inorder(node *p);

//verifica se os elementos da arvore estao ordenada com precurso em ordem
int inorder_aux(node *p, elem *prev);

//chama a funcao para verifcar se a arvore fica ordenado com precurso pos-order
int postorder(node *p);

//verifica se os elementos da arvore estao ordenada com precurso pos-order
int postorder_aux(node *p, elem *prev);

