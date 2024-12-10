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
    LS* lista_sequencial_nova = malloc(sizeof(LS));
    lista_sequencial_nova->vetor = vetorNovo;
    lista_sequencial_nova->tamanho = tam;
    lista_sequencial_nova->qtd_itens = 0;
    return lista_sequencial_nova;
}

int encontrar_posicao_pra_insercao(LS* ls, int valor) {
    int inicio = 0;
    int fim = ls->qtd_itens - 1;
    
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (ls->vetor[meio] == valor) 
            return -1;  // valor já existe
        else if (ls->vetor[meio] < valor)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return inicio;
}

bool ls_inserir(LS* ls, int valor){
    if(ls==NULL) return false;
    if (ls->qtd_itens == ls->tamanho) return false;

    int posicao = encontrar_posicao_pra_insercao(ls, valor);

    if (posicao == -1) return false;//ja tem

    for (int i = ls->qtd_itens; i > posicao; i--){
        ls->vetor[i] = ls->vetor[i-1];
    }
    ls->vetor[posicao] = valor;
    ls->qtd_itens++;
    return true;
}



int busca_binaria_por_index(LS* ls, int valor){
    int inicio = 0;
    int fim = ls->qtd_itens - 1;
    while (inicio <= fim){
        int meio = (inicio + fim) / 2;
        if (ls->vetor[meio] == valor) return meio;
        else if (ls->vetor[meio] < valor) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}


bool ls_remover(LS* ls, int valor){
    int posicao = busca_binaria_por_index(ls, valor);
    if (posicao == -1) return false;
    for (int i = posicao; i < ls->qtd_itens - 1; i++){
        ls->vetor[i] = ls->vetor[i+1];
    }
    ls->qtd_itens--;
    return true;
}

void ls_imprimir(LS* ls){
    for (int i = 0; i < ls->qtd_itens; i++){
        printf("%d ", ls->vetor[i]);
    }
    printf("\n");
}