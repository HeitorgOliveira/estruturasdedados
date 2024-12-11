#include "avl.h"
#include "ls.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct avl AVL;
typedef struct ls LS;
typedef struct no NO;
typedef struct conjunto CONJUNTO;

struct no{
    NO *esq;
    NO *dir;
    int FB;
    int numero;
};

struct avl{
    NO *raiz;
};

struct conjunto{
    AVL *avl;
    LS *ls;
};

// A função conjunto criar cria um conjunto de acordo com a seleção do usuário
// se a especificação for L criamos uma lista na estrutura conjunto e deixamos o ponteiro para
// sua árvore como NULL, para evitar o mau uso
// Fazemos o mesmo com árvores se inserirem T
CONJUNTO *conjunto_criar(unsigned char tipo){
    CONJUNTO *conjunto = (CONJUNTO *) malloc(sizeof(CONJUNTO)); 
    if (conjunto == NULL) return NULL;

    if (tipo == 'L'){
        conjunto->ls = ls_criar();
        conjunto->avl = NULL;
        return conjunto;
    }
    else if (tipo == 'A'){
        conjunto->avl = avl_criar();
        conjunto->ls = NULL;
        return conjunto;
    }
    else {return NULL;}
}

// Função auxiliar para verificar se há lista
void verificar_se_tem_ls(CONJUNTO* s){
    if(s==NULL){
        return;
    }
    if(s->ls){
    }
}

// Inserimos conforme as funções implementadas nas estruturas de dados contidas no conjunto
// novamente, as funções chamadas dependem do tipo de dado presente no conjunto
bool conjunto_inserir (CONJUNTO *s, int elemento){
    if (s != NULL){
        return (s->avl != NULL ? avl_inserir(s->avl, elemento) : ls_inserir(s->ls, elemento));
    }
}

// Chamamos as funções de remoçao da estrura de dado presente no conjunto
bool conjunto_remover(CONJUNTO *s, int elemento){
    if (s != NULL){
        return (s->avl != NULL ? avl_excluir(s->avl, elemento) : ls_excluir(s->ls, elemento));
    }
}

// Chamamos a função de apagar do conjunto de acordo com a estrutura de dados presente nele
void conjunto_apagar(CONJUNTO **s){
    if (*s != NULL){
        if ((*s)->avl != NULL){
            avl_apagar(&(*s)->avl);
        }else{
            ls_apagar(&(*s)->ls);
        }
        free(*s);
        *s = NULL;
    }
  }

// Chamamos a função de exibição de acordo com a estrutra de dados presente no conjunto
void conjunto_imprimir(CONJUNTO *s){
    if (s != NULL){
        s->avl != NULL ? avl_imprimir(s->avl) : ls_imprimir(s->ls);
    }
}

// Chama a função de pertencimento de acordo com a estrutura de dados presente no conjunto
bool conjunto_pertence(CONJUNTO *A, int elemento){
    if (A != NULL){
        return (A->avl != NULL ? avl_pertence(A->avl, elemento) : ls_pertence(A->ls, elemento));
    }
}

// Função auxliar para realizar a uniao no conjunto. Basicamente fazemos um percurso em pre-order para inserir
// os dados em uma árvore, assim juntando conteúdos em uma árvore só
void conjunto_uniao_aux(NO *raiz, LS *ls, AVL *T){
    if (raiz == NULL || T == NULL) return;
    avl_inserir(T, raiz->numero);
    conjunto_uniao_aux(raiz->esq, ls, T);
    conjunto_uniao_aux(raiz->dir, ls, T);
}

// Função principal conjunto uniao
// No caso de intersecção entre arvores, retornamos uma árvore
// No caso de intersecção entre lista, retornamos uma lista
// Em caso de ambiguidade (arvore e lista) optamos por retornar uma arvore
CONJUNTO *conjunto_uniao(CONJUNTO *A, CONJUNTO *B){
    if (A != NULL && B != NULL){
        
        // Caso as duas sejam árvores, simplesmente chamamos a função para unir as duas árvores
        if (A->avl != NULL && B->avl != NULL){
            CONJUNTO *conjunto = conjunto_criar('A');
            conjunto->avl = avl_uniao(A->avl, B->avl);
            return conjunto;
        }
        // Caso as duas sejam listas, chamamos as funções responsaveis por unir duas listas
        if (A->ls != NULL && B->ls != NULL){
            CONJUNTO *conjunto = conjunto_criar('L');
            conjunto->ls = ls_uniao(A->ls, B->ls);
            return conjunto;
        }
        // Caso as duas sejam estrutras diferentes juntamos os dois conjuntos criando uma AVL e inserindo todos os números na avl
        // para isso usamos a função de união na árvore vazia com a árvore alvo e chamamos a função de união com uma lista e uma árvore, presente no arquivo ls.h
        else
        {
            CONJUNTO *conjunto = conjunto_criar('A');   
            if (A->avl != NULL){
                
                conjunto->avl = avl_uniao(conjunto->avl, A->avl);
                
                ls_insere_em_avl(conjunto->avl, B->ls);
            }else{
                conjunto->avl = avl_uniao(conjunto->avl, B->avl);
                ls_insere_em_avl(conjunto->avl, A->ls);

            }
            
            return conjunto;
        }
    }
    return NULL;
}

// Função auxiliar para a operação de intersecção.
// Basicamente realizamos um percurso em pre-order verificando se o elemento da arvore está presente na lista
// com o uso da função de buscar um item na lista. Caso o item esteja presente, inserimos ele na árvore alvo.
void conjunto_interseccao_aux(NO *raiz, LS *ls, AVL *T){
    if (T == NULL || raiz == NULL) return;
    if (ls_pertence(ls, raiz->numero)){
        avl_inserir(T, raiz->numero);
        printf("Inserindo %d\n", raiz->numero);
    }
    conjunto_interseccao_aux(raiz->esq, ls, T);
    conjunto_interseccao_aux(raiz->dir, ls, T);
}

// Função principal de intersecção 
// No caso de intersecção entre arvores, retornamos uma árvore
// No caso de intersecção entre lista, retornamos uma lista
// Em caso de ambiguidade (arvore e lista) optamos por retornar uma arvore
CONJUNTO *conjunto_interseccao(CONJUNTO *A, CONJUNTO *B) {
    if (A == NULL || B == NULL) {
        printf("nulos\n");
        return NULL;
    }

    CONJUNTO *conjunto = NULL;

    // Se ambos os conjuntos forem AVLs, simplesmente chamamos a função de intersecção entre AVLs
    if (A->avl != NULL && B->avl != NULL) {
        printf("os dois sao avl\n");
        conjunto = conjunto_criar('A');
        conjunto->avl = avl_interseccao(A->avl, B->avl);
    }

    // Se ambos forem listas, chamamos a função de intersecção entre listas
    else if (A->ls != NULL && B->ls != NULL) {
        conjunto = conjunto_criar('L');
        conjunto->ls = ls_interseccao(A->ls, B->ls);
    }

    // Caso tenham tipos diferentes chamamos a função auxiliar.
    // O caso de intersecção é mais simples, pois devemos simplesmente verificar se o numero está presente em ambas
    // estruras de dados, então percorremos a arvore inteira verificando se seus numeros estão na lista, usando a função de busca
    // da lista. se o numero estiver nós o inserimos na árvore
    else if ((A->avl != NULL && B->ls != NULL) || 
             (A->ls != NULL && B->avl != NULL)) {
        conjunto = conjunto_criar('A');
        AVL *T = avl_criar();
        
        if (A->avl != NULL) {
            conjunto_interseccao_aux(A->avl->raiz, B->ls, T);
        } else {
            conjunto_interseccao_aux(B->avl->raiz, A->ls, T);
        }
        conjunto->avl = T;
    }else{
    }
    return conjunto;
}