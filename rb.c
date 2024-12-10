#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rb.h"

typedef struct no NO;
typedef struct no{
    NO* esquerda;
    NO*direita;
    bool vermelho;
    int chave;
};

struct rb{
    NO* raiz;
};

RB* rb_criar(){
    RB* rb = malloc(sizeof(RB));
    if (rb == NULL) return NULL;
    rb->raiz = NULL;
    return rb;
}
NO* rotacao_esquerda(NO* raiz) {
    NO* aux = raiz->direita;
    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;
    aux->vermelho = raiz->vermelho;
    raiz->vermelho = true;
    return aux;
}

NO* rotacao_direita(NO* raiz) {
    NO* aux = raiz->esquerda;
    raiz->esquerda = aux->direita;
    aux->direita = raiz;
    aux->vermelho = raiz->vermelho;
    raiz->vermelho = true;
    return aux;
}

NO* no_balancear(NO* raiz) {
    if (raiz->direita != NULL && raiz->direita->vermelho) {
        raiz = rotacao_esquerda(raiz);
    }
    if (raiz->esquerda != NULL && raiz->esquerda->vermelho && raiz->esquerda->esquerda != NULL && raiz->esquerda->esquerda->vermelho) {
        raiz = rotacao_direita(raiz);
    }
    if (raiz->esquerda != NULL && raiz->esquerda->vermelho && raiz->direita != NULL && raiz->direita->vermelho) {//inverte as cores
        raiz->vermelho = true;
        raiz->esquerda->vermelho = false;
        raiz->direita->vermelho = false;
    }
    return raiz;
}

NO* rb_inserir_balance(NO** raiz, int chave){
    if (*raiz == NULL) {
        NO* novo = malloc(sizeof(NO));
        if (novo == NULL) return NULL;
        novo->chave = chave;
        novo->esquerda = novo->direita = NULL;
        novo->vermelho = true;
        *raiz = novo;
        return novo;
    }
    if ((*raiz)->chave == chave) return *raiz;
    if (chave < (*raiz)->chave) {
        NO* inserido = rb_inserir_balance(&(*raiz)->esquerda, chave);
        if (inserido == NULL) return NULL;
    } else {
        NO* inserido = rb_inserir_balance(&(*raiz)->direita, chave);
        if (inserido == NULL) return NULL;
    }
    //apos a insercao, se for inserido, o no é rebalanceado
    *raiz = no_balancear(*raiz);
    return *raiz;
}

bool rb_inserir(RB *rb, int chave){
    if (rb == NULL) return false;
    NO* inserido = rb_inserir_aux(&(rb->raiz), chave);

}

rb_remover_aux(NO** raiz, int chave){
    if (*raiz == NULL) return NULL;
    if ((*raiz)->chave == chave) {
        if ((*raiz)->esquerda == NULL && (*raiz)->direita == NULL) {
            free(*raiz);
            *raiz = NULL;
            return *raiz;
        }
        if ((*raiz)->esquerda == NULL) {
            NO* aux = *raiz;
            *raiz = (*raiz)->direita;
            free(aux);
            return *raiz;
        }
        if ((*raiz)->direita == NULL) {
            NO* aux = *raiz;
            *raiz = (*raiz)->esquerda;
            free(aux);
            return *raiz;
        }
        NO* troca = (*raiz)->esquerda;
        while (troca->direita != NULL) {
            troca = troca->direita;
        }
        (*raiz)->chave = troca->chave;
        rb_remover_aux(&(*raiz)->esquerda, troca->chave);
        return *raiz;
    }
    if ((*raiz)->chave > chave) {
        return rb_remover_aux(&(*raiz)->esquerda, chave);
    }
    return rb_remover_aux(&(*raiz)->direita, chave);
}

bool rb_remover(RB *rb, int chave){
    if (rb == NULL) return false;
    NO* removido = rb_remover_aux(&(rb->raiz), chave);
    if (removido == NULL) return false;
    return true;
}