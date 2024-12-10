#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ls.h" 

struct ls{
    int tamanho;
    int qtd_itens;
    int* vetor;
};

LS* ls_criar(int tam){
    int* vetorNovo = malloc(sizeof(int)*tam);
    vetorNovo[0]=0;
    vetorNovo[1]=1;
    vetorNovo[2]=2;
    vetorNovo[3]=3;
    vetorNovo[4]=4;
    vetorNovo[5]=6;
    vetorNovo[6]=7;
    vetorNovo[7]=8;
    vetorNovo[8]=9;
    vetorNovo[9]=10;

    LS* lista_sequencial_nova = malloc(sizeof(LS));
    lista_sequencial_nova->vetor = vetorNovo;
    lista_sequencial_nova->tamanho = tam;
    lista_sequencial_nova->qtd_itens = 10;
}
int encontrar_posicao(LS* ls, int valor){
    int inicio = 0;
    int fim = ls->qtd_itens - 1;
    
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (ls->vetor[meio] == valor) return 0;
        if (ls->vetor[meio] < valor) 
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return inicio;
}