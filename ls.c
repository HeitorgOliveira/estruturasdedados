#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ls.h" 

typedef struct ls{
    int tamanho;
    int qtd_itens;
    int* vetor;
}LS;

LS* ls_criar(int tam){
    int* vetorNovo = malloc(sizeof(int)*tam);
    LS* lista_sequencial_nova = malloc(sizeof(LS));
    lista_sequencial_nova->vetor = vetorNovo;
    lista_sequencial_nova->tamanho = tam;
    lista_sequencial_nova->qtd_itens = 0;
}

int ls_index_do_menor_maior(int* vetor, int comeco, int fim,int num){
    if(comeco==fim){
        return -1;
    }
    int meio = (comeco+fim)/2;
    if(vetor[meio]==num){
        return meio;
    }
    if(vetor[meio]>num){
        return ls_index_do_menor_maior(vetor,comeco,meio,num);
    }
    return ls_index_do_menor_maior(vetor,meio+1,fim,num);
}

bool ls_inserir(LS* ls, int num){
    if(ls==NULL){
        printf("Lista sequencial não alocada\n");
        return false;
    }
    if(ls->qtd_itens==0){
        return false;
    }
    if (ls->qtd_itens == ls->tamanho){
        ls->tamanho++;
        ls->vetor = realloc(ls->vetor, sizeof(int)*(ls->tamanho));//como a gente aumentou o tamanho, ele faz o realloc pra por mais um espaço
    }
    int index_do_menor_maior  = ls_index_do_menor_maior(ls->vetor,0,ls->qtd_itens, num);
    return true;
}