#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ADS.h"

//Função que cria a arvore
pNodoA *cria_arvore(){
    return NULL;
}
// Funcao  de busca na arvore
pNodoA *consulta(pNodoA *a,char *palavra,int *score){
    while(a!=NULL){
        comp++;
        palavra[0]=tolower(palavra[0]);
        if(strcmp(palavra,a->palavra)==0){
            comp++;
            *score=*score+a->score;

            return a;
        }else{
            comp++;
            if(strcmp(palavra,a->palavra)<0)
                a=a->esq;
            else
                a=a->dir;
        }
    }
    return NULL;
}
//Rotação simples a direita para avl
pNodoA *rotacao_direita(pNodoA *p){
    pNodoA *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}
//Rotação simples a esquerda para avl
pNodoA *rotacao_esquerda(pNodoA *p){
    pNodoA *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}
//Rotação dupla a direita para avl
pNodoA *rotacao_dupla_direita (pNodoA* p){
    pNodoA *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1)
        p->FB = -1;
    else
        p->FB = 0;
    if (v->FB == -1)
        u->FB = 1;
    else
        u->FB = 0;
    p = v;
    return p;
}
//Rotação dupla a esquerda para avl
pNodoA *rotacao_dupla_esquerda (pNodoA *p){
    pNodoA *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1)
        p->FB = 1;
    else
        p->FB = 0;
    if (y->FB == 1)
        z->FB = -1;
    else
        z->FB = 0;
    p = y;
    return p;
}
// Casos: Funcoes que equilibrarao a avl para determinados casos
pNodoA *Caso1 (pNodoA *a, int *ok){
    pNodoA *z;
    z = a->esq;
    if (z->FB == 1)
        a = rotacao_direita(a);
    else
        a = rotacao_dupla_direita(a);
    a->FB = 0;
    *ok = 0;
return a;
}
pNodoA *Caso2 (pNodoA *a, int *ok){
    pNodoA *z;
    z = a->dir;
    if (z->FB == -1)
        a = rotacao_esquerda(a);
    else
        a = rotacao_dupla_esquerda(a);
    a->FB = 0;
    *ok = 0;
    return a;
}
// Funcao de Insercao para as  arveres ABP e AVL
pNodoA* InsereAVL (pNodoA *a,char palavra[],int score, int *ok){
    if (a == NULL){
        a = (pNodoA*) malloc(sizeof(pNodoA));
        strcpy(a->palavra,palavra);
        a->score=score;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (strcmp(palavra,a->palavra)<0){
        a->esq = InsereAVL(a->esq,palavra,score,ok);
        if (*ok){
            switch (a->FB){
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                a=Caso1(a,ok);
                break;
            }
        }
    }else{
        a->dir = InsereAVL(a->dir,palavra,score,ok);
        if (*ok){
            switch (a->FB){
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = Caso2(a,ok);
                break;
            }
        }
    }

    return a;
}
pNodoA *InsereABP(pNodoA *a,char palavra[],int score){
    if (a == NULL){
        a = (pNodoA*) malloc(sizeof(pNodoA));
        a->score=score;
        strcpy(a->palavra,palavra);
        a->esq = NULL;
        a->dir = NULL;
     }
     else if (strcmp(palavra,a->palavra)<0)
        a->esq = InsereABP(a->esq,palavra,score);
     else
        a->dir = InsereABP(a->dir,palavra,score);

  return a;
}

// --------------------------------------------------

int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

int altura(pNodoA *pRaiz){
   if((pRaiz == NULL) || (pRaiz->esq == NULL && pRaiz->dir == NULL))
       return 0;
   else
       return 1 + maior(altura(pRaiz->esq), altura(pRaiz->dir));
}

//----------------------------------------------------
