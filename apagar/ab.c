#include <ab.h>
#include <item.h>
#include <stdio.h>
#include <stdlib.h>
#define ESQUERDA 0
#define DIREITA 1

typedef struct no NO;

struct no{
    NO *esquerda;
    NO *direita;
    ITEM *item;
};

struct ab{
    NO *raiz;
    int profundidade;
};

NO *ab_cria_no(ITEM *item){
    NO *no = malloc(sizeof(NO));
    if (no == NULL) return NULL;
    no->item = item;
    no->direita = no->esquerda = NULL;
    return no;
}

AB *ab_criar(){
    AB *ab = malloc(sizeof (AB));
    if (ab == NULL) return NULL;

    ab->raiz = NULL;
    ab->profundidade = -1;
    return ab;
}

void ab_inserir_lado_no(NO *raiz, NO *no, int lado, int chave){
    if (raiz == NULL) return;
    if (item_get_chave(raiz->item) == chave){
        if (lado == ESQUERDA){
            raiz->esquerda = no;
        }else{
            raiz->direita = no;
        }
        return;
    }
    ab_inserir_lado_no(raiz->esquerda, no, lado, chave);
    ab_inserir_lado_no(raiz->direita, no, lado, chave);
}

bool ab_inserir_lado(AB *T, ITEM *item, int lado, int chave){
    if (T == NULL || item == NULL) return false;
    if (T->raiz == NULL)
    {
        NO *no = ab_cria_no(item);
        if (no == NULL) return false;
        T->raiz = no;
        return true;
    }else{
        NO *no = ab_cria_no(item);
        if (no == NULL) return false;
        ab_inserir_lado_no(T->raiz, no, lado, chave);
        return true;
    }
}

bool ab_apaga_no(AB *T, int chave){
    if (T == NULL) return false;
    apaga_rec(&(T->raiz), chave);
    return true;
}

void apaga_rec(NO **raiz, int chave){
    if (raiz == NULL) return;
    if (item_get_chave((*raiz)->item) == chave){
        item_apagar(&(*raiz)->item);
        free(*raiz);
        *raiz = NULL;
        return;
    }
    apaga_rec(&(*raiz)->esquerda, chave);
    apaga_rec(&(*raiz)->direita, chave);
    return;
}

void ab_excluir_nos(NO **raiz){
    if (*raiz == NULL) return;
    ab_excluir_nos(&(*raiz)->esquerda);
    ab_excluir_nos(&(*raiz)->direita);
    item_apagar(&(*raiz)->item);
    free(*raiz);
    *raiz = NULL;
    return;
}

bool ab_excluir(AB **T){
    if (T == NULL || *T == NULL) return false;
    ab_excluir_nos(&(*T)->raiz);
    free(*T);
    *T = NULL;
    return true;
}