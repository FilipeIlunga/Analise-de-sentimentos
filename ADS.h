
//Definicao de estruturas
struct pNodoA{
    char palavra[30];
    int score;
    int FB;
    struct pNodoA *esq;
    struct pNodoA *dir;
};typedef struct pNodoA pNodoA;

int comp;
//Inicializa arvore
pNodoA *cria_arvore();
pNodoA *consulta(pNodoA *a,char palavra[],int *score);

//Rotacoes AVL, recebem uma AVL e retornam uma AVL com as devidas rotacoes feitas
pNodoA *rotacao_direita(pNodoA *p);
pNodoA *rotacao_esquerda(pNodoA *p);
pNodoA *rotacao_dupla_direita (pNodoA* p);
pNodoA *rotacao_dupla_esquerda (pNodoA *p);

//Casos de desbalanceamento na insercao, recebem uma AVL e uma flag
pNodoA *Caso1 (pNodoA *a,int *ok);
pNodoA *Caso2 (pNodoA *a,int *ok);

//Funcoes de insercao
//Recebe uma arvore, a palavra a ser inserida ,o seu escore e uma flag que indica se a arvore esta balanceada, retorna a mesma arvore com a palavra e o seuu escore
pNodoA *InsereAVL(pNodoA *a,char palavra[],int score,int *ok);
//Recebe uma arvore, a palavra a ser inserida, retorna a mesma arvore com a palavra e o seuu escore
pNodoA *InsereABP(pNodoA *a,char palavra[],int score);

//-------------------------------------
int maior(int a, int b);
int altura(pNodoA *pRaiz);
//-------------------------------------
