#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ADS.h"
//-----------------
#include <time.h>
//------------------

int main(){


    comp=0;

    FILE *arq_arvore;
    FILE *arq_entrada;
    FILE *arq_saida_ABP;
    FILE *arq_saida_AVL;
    pNodoA *ABP;
    pNodoA *AVL;
//--------------------------
    clock_t Ticks[4];

    int altura_ABP;
    int altura_AVL;
//-------------------------
    char nomlex[40];         // NOME DO ARQUIVO LÉXICO
    char nomtxt[40];         // NOME DO ARQUIVO TEXTO
    char token_lex[30];      // TOKEN DO ARQUIVO LÉXICO
    char *palavra;		     // PALAVRA DO TEXTO QUE SERÁ COMPARADA NA ARVORE
    char linha[1000];        // LINHA A SER LIDA
    char linha_saida[1000];  // LINHA A SER IMPRESSA NO ARQUIVO DE SAÍDA

    int score;                // POLARIDADE DAS PALAVRAS NA ÁRVORE
    int score_ABP=0;          // POLARIDADE DAS SENTENCAS PARA  AVL E ABP
    int score_AVL=0;
    int ok;
    int comp_ABP=0;           // NUMERO DE COMPARAÇÕES FEITAS NA ABP
    int comp_AVL=0;           // NUMERO DE COMPARAÇÕES FEITAS NA AVL

    ABP=cria_arvore();
    AVL=cria_arvore();

    fflush(stdin);
    printf("Arquivo Lexico:");
    scanf("%s", nomlex);
    printf("Arquivo das Sentencas:");
    scanf("%s", nomtxt);

    if(!(arq_arvore=fopen(nomlex,"r"))||!(arq_entrada=fopen(nomtxt,"r"))||!(arq_saida_ABP=fopen("Saida_ABP.txt","w"))||!(arq_saida_AVL=fopen("Saida_AVL.txt","w"))){
        if(!(arq_arvore=fopen(nomlex,"r")))
            printf("Erro na Abertura do Arquivo Lexico!\n");
        if(!(arq_entrada=fopen(nomtxt,"r")))
            printf("Erro na Abertura do Arquivo de entrada!\n");
        if(!(arq_saida_ABP=fopen("Saida_ABP.txt","w")))
            printf("Erro na Criacao do Arquivo de saida da ABP!\n");
        if(!(arq_saida_AVL=fopen("Saida_AVL.txt","w")))
             printf("Erro na Criacao do Arquivo de saida da AVL!\n");
    }else{
       //----------------------------
       Ticks[0] = clock();
       //----------------------------
        while(!feof(arq_arvore)){

            fscanf(arq_arvore," %s %d",token_lex,&score);
            ABP=InsereABP(ABP,token_lex,score);

        }
        Ticks[1] = clock();

        rewind(arq_arvore);

        Ticks[2] = clock();
        while(!feof(arq_arvore)){

            fscanf(arq_arvore," %s %d",token_lex,&score);
            AVL=InsereAVL(AVL,token_lex,score,&ok);

        }
       Ticks[3] = clock();
       //---------------------------


        while(fgets(linha,1000,arq_entrada)){

            strcpy(linha_saida,linha);              //E feita uma copia da linha antes de chamar o strtok
            palavra=strtok(linha," ,.-:;!?");       //pois depois da execução do strtok ela perdera as pontuações(. , : ; ... ! ?)
                                                    //porem fazendo a copia antes e escrever essa copia no arquivo
            while(palavra!=NULL){                   // de saida esse problema nao ocorre

                consulta(AVL,palavra,&score_ABP);
                comp_AVL=comp_AVL+comp;              //salva o numero das comparacoes da avl
                comp=0;                              //A variavel global e zerada para ser usada na consulta da ABP


                consulta(ABP,palavra,&score_AVL);     //salva o numero das comparacoes da avl
                comp_ABP=comp_ABP+comp;               //A variavel global e zerada para ser usada na consulta da ABP
                comp=0;

                palavra=strtok( NULL," ,.-:;!?");
            }
            fprintf(arq_saida_ABP,"%d %s",score_ABP,linha_saida);    // a linha  que foi copiada em cima é
            score_ABP=0;                                         // escrita no arquivo com a sua polaridade
            fprintf(arq_saida_AVL,"%d %s",score_AVL,linha_saida);
            score_AVL=0;
        }
    }

    altura_ABP=altura(ABP);
    altura_AVL=altura(AVL);
    double TempoABP = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    double TempoAVL = (Ticks[3] - Ticks[2]) * 1000.0 / CLOCKS_PER_SEC;

    printf("\nAltura ABP:%d",altura_ABP);
    printf("\nAltura AVL:%d",altura_AVL);
    printf("\nTempo ABP:%g ms.",TempoABP);
    printf("\nTempo AVL:%g ms.",TempoAVL);
    printf("\nComparacoes AVL: %d\n",comp_AVL);
    printf("Comparacoes ABP: %d\n",comp_ABP);

    fclose(arq_arvore);
    fclose( arq_entrada);
    fclose(arq_saida_ABP);
    fclose(arq_saida_AVL);

    return 0;
}

