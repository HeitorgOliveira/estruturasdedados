#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rb.h"

typedef struct no NO;
struct no{
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
    NO* inserido = rb_inserir_balance(&(rb->raiz), chave);
    if (inserido == NULL) return false;
    rb->raiz->vermelho = false; //ter certeza que a raiz é preta
    return true;
}

void rb_remover_fixup(NO** raiz, NO* pai, NO* no) {
    while (no != *raiz && (no == NULL || !no->vermelho)) {
        if (no == pai->esquerda) {
            NO* w = pai->direita;
            if (w->vermelho) {
                w->vermelho = false;
                pai->vermelho = true;
                pai = rotacao_esquerda(pai);
                w = pai->direita;
            }
            if ((w->esquerda == NULL || !w->esquerda->vermelho) && (w->direita == NULL || !w->direita->vermelho)) {
                w->vermelho = true;
                no = pai;
                pai = NULL; // Update parent
            } else {
                if (w->direita == NULL || !w->direita->vermelho) {
                    if (w->esquerda != NULL) w->esquerda->vermelho = false;
                    w->vermelho = true;
                    w = rotacao_direita(w);
                    w = pai->direita;
                }
                w->vermelho = pai->vermelho;
                pai->vermelho = false;
                if (w->direita != NULL) w->direita->vermelho = false;
                pai = rotacao_esquerda(pai);
                no = *raiz;
            }
        } else {
            NO* w = pai->esquerda;
            if (w->vermelho) {
                w->vermelho = false;
                pai->vermelho = true;
                pai = rotacao_direita(pai);
                w = pai->esquerda;
            }
            if ((w->direita == NULL || !w->direita->vermelho) && (w->esquerda == NULL || !w->esquerda->vermelho)) {
                w->vermelho = true;
                no = pai;
                pai = NULL; // Update parent
            } else {
                if (w->esquerda == NULL || !w->esquerda->vermelho) {
                    if (w->direita != NULL) w->direita->vermelho = false;
                    w->vermelho = true;
                    w = rotacao_esquerda(w);
                    w = pai->esquerda;
                }
                w->vermelho = pai->vermelho;
                pai->vermelho = false;
                if (w->esquerda != NULL) w->esquerda->vermelho = false;
                pai = rotacao_direita(pai);
                no = *raiz;
            }
        }
    }
    if (no != NULL) no->vermelho = false;
}
NO* rb_remover_aux(NO** raiz, int chave, NO* pai) {
    if (*raiz == NULL) return NULL;
    NO* removido = NULL;
    if ((*raiz)->chave == chave) {
        if ((*raiz)->esquerda == NULL && (*raiz)->direita == NULL) {
            removido = *raiz;
            *raiz = NULL;
        } else if ((*raiz)->esquerda == NULL) {
            removido = *raiz;
            *raiz = (*raiz)->direita;
        } else if ((*raiz)->direita == NULL) {
            removido = *raiz;
            *raiz = (*raiz)->esquerda;
        } else {
            NO* troca = (*raiz)->esquerda;
            while (troca->direita != NULL) {
                troca = troca->direita;
            }
            (*raiz)->chave = troca->chave;
            removido = rb_remover_aux(&(*raiz)->esquerda, troca->chave, *raiz);
        }
    } else if ((*raiz)->chave > chave) {
        removido = rb_remover_aux(&(*raiz)->esquerda, chave, *raiz);
    } else {
        removido = rb_remover_aux(&(*raiz)->direita, chave, *raiz);
    }
    if (removido != NULL && !removido->vermelho) {
        rb_remover_fixup(raiz, pai, *raiz);
    }
    return removido;
}

bool rb_remover(RB *rb, int chave){
    if (rb == NULL) return false;
    NO* removido = rb_remover_aux(&(rb->raiz), chave, NULL);
    if (removido == NULL) return false;
    free(removido);
    if (rb->raiz != NULL) rb->raiz->vermelho = false; // Ensure the root is always black
    return true;
}

void rb_imprimir_aux(NO* raiz){
    if (raiz == NULL) return;
    rb_imprimir_aux(raiz->esquerda);
    printf("%d ", raiz->chave);
    rb_imprimir_aux(raiz->direita);
}
void rb_imprimir(RB *rb){
    if (rb == NULL) return;
    printf("Conjunto: ");
    rb_imprimir_aux(rb->raiz);
}