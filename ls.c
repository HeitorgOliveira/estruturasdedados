#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ls.h" 
#include "avl.h"

struct ls{
    int tamanho;
    int qtd_itens;
    int* vetor;
};

LS* ls_criar(){//criamos uma lista sequencial com um malloc de 1000 inteiros já que não foi especificado se a memória é crítica ou não o(1)
    int tam=1000;
    int* vetorNovo = malloc(sizeof(int)*tam);
    LS* lista_sequencial_nova = malloc(sizeof(LS));
    lista_sequencial_nova->vetor = vetorNovo;
    lista_sequencial_nova->tamanho = tam;
    lista_sequencial_nova->qtd_itens = 0;

    return lista_sequencial_nova;
}

void encontrar_posicao_pra_insercao(LS* ls, int valor, int** pos) {//busca binária para encontrar a posição de inserção
    int inicio = 0;
    int fim = ls->qtd_itens - 1;
    
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (ls->vetor[meio] == valor){  
            *pos = NULL;
            return;  // valor já esta na lista
        }
        else if (ls->vetor[meio] < valor)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }//cada iteração do while divide o vetor em 2 partes, entao o pior caso é quando o vetor achao o valor na
    // ultima iteração, que é log2(n) ja que a quantidade de iteracoes é o numero que se elevar o dois dá a quantidade de nós
    **pos = inicio;
}

bool ls_inserir(LS* ls, int valor){//O(n+log2(n))
    if(ls==NULL) return false;
    if (ls->qtd_itens == ls->tamanho) {
        ls->tamanho *= 2;
        ls->vetor = realloc(ls->vetor, sizeof(int) * ls->tamanho);//dobra o tamanho para insercao nova
    };

    int* posicao = malloc(sizeof(int));
    encontrar_posicao_pra_insercao(ls, valor, &posicao);//O(log2(n))

    if (posicao ==NULL) {//se ja existe
        free(posicao);
        return false;
    }

    for (int i = ls->qtd_itens; i > *posicao; i--){// while para mover os elementos para a direita, se posicao for
    // 0, o pior caso, ele vai ter que mover todos os elementos entao seria O(n)
        ls->vetor[i] = ls->vetor[i-1];
    }
    ls->vetor[*posicao] = valor;
    ls->qtd_itens++;
    free(posicao);
    return true;
}

void busca_binaria_por_index(LS* ls, int valor, int** pos){
    int inicio = 0;
    int fim = ls->qtd_itens - 1;
    while (inicio <= fim){
        int meio = (inicio + fim) / 2;
        if (ls->vetor[meio] == valor) {
            **pos = meio;
            return;
        }
        else if (ls->vetor[meio] < valor) inicio = meio + 1;
        else fim = meio - 1;
    }
    *pos = NULL;
}


bool ls_excluir(LS* ls, int valor){
    int* posicao = malloc(sizeof(int));
    busca_binaria_por_index(ls, valor, &posicao);

    if (posicao == NULL){
        free(posicao);
        return false;
    } 
    for (int i = *posicao; i < ls->qtd_itens - 1; i++){
        ls->vetor[i] = ls->vetor[i+1];
    }
    
    ls->qtd_itens--;
    free(posicao);
    return true;
}

bool ls_pertence(LS* ls, int chave){
    if(ls==NULL) return false;
    int* posicao = malloc(sizeof(int));
    busca_binaria_por_index(ls, chave, &posicao);
    if (posicao == NULL){
        free(posicao);
        return false;
    }
    free(posicao);
    return true;

}

void ls_imprimir(LS* ls){
    for (int i = 0; i < ls->qtd_itens; i++){
        printf("%d, ", ls->vetor[i]);
    }
}

bool ls_insere_em_avl(AVL* avl, LS* ls){
    
    if(avl==NULL) return false;
    for(int i=0; i<ls->qtd_itens; i++){
        avl_inserir(avl, ls->vetor[i]);
        
    }
}

bool ls_apagar(LS** ls){
    if(*ls==NULL) return false;
    free((*ls)->vetor);
    (*ls)->vetor=NULL;
    free(*ls);
    *ls=NULL;
    return true;
}

LS* ls_uniao(LS* A, LS* B){
    if(A==NULL || B==NULL) return NULL;
    LS* uniao = ls_criar();
    for(int i=0; i<A->qtd_itens; i++){
        ls_inserir(uniao, A->vetor[i]);
    }
    for(int i=0; i<B->qtd_itens; i++){
        ls_inserir(uniao, B->vetor[i]);
    }
    return uniao;
}

LS* ls_interseccao(LS* A, LS* B){
    if(A==NULL || B==NULL) return NULL;
    LS* interseccao = ls_criar();
    for(int i=0; i<A->qtd_itens; i++){
        if(ls_pertence(B, A->vetor[i])){
            ls_inserir(interseccao, A->vetor[i]);
        }
    }
    return interseccao;
}

