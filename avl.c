#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct avl AVL;
typedef struct no NO;

struct no{
    NO *esq;
    NO *dir;
    int FB;
    int numero;
};

struct avl{
    NO *raiz;
};

NO *avl_cria_no(int numero){
    NO *no = (NO*) malloc(sizeof(NO));
    if (no == NULL) return NULL;
    no->numero = numero;
    no->esq = no->dir = NULL;
    no->FB = 0;
    return no;
}

int altura(NO *raiz){
    if (raiz == NULL) return 0;
    int esquerda = altura(raiz->esq);
    int direita = altura(raiz->dir);
    return 1 + (direita > esquerda ? direita : esquerda);
}

bool balanceada(NO *raiz){
    if (raiz == NULL) return true;
    int esquerda = altura(raiz->esq);
    int direita = altura(raiz->dir);
    if (abs(esquerda - direita) > 1){
        return false;
    }else return (balanceada(raiz->esq) && balanceada(raiz->dir));
}

NO *avl_rotaciona_esquerda(NO *no){
    NO *aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    no->FB = aux->FB = 0;
    return aux;
}

NO *avl_rotaciona_direita(NO *no){
    NO *aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;

    no->FB = aux->FB = 0;
    return aux;
}

NO *avl_rotaciona_dupla_esquerda(NO *no){
    no->dir = avl_rotaciona_direita(no->dir);
    return avl_rotaciona_esquerda(no);
}

NO *avl_rotaciona_dupla_direita(NO *no){
    no->esq = avl_rotaciona_esquerda(no->esq);
    return avl_rotaciona_direita(no);
}

NO *avl_inserir_aux(NO *raiz, NO *no){
    if (raiz == NULL){
        raiz = no;
    }
    else if (raiz->numero > no->numero){
        raiz->esq = avl_inserir_aux(raiz->esq, no);
    }else{
        raiz->dir = avl_inserir_aux(raiz->dir, no);
    }

    raiz->FB = altura(raiz->esq) - altura(raiz->dir);
    if (raiz->FB == 2){
        if (raiz->esq->FB >= 0) raiz = avl_rotaciona_direita(raiz);
        else raiz = avl_rotaciona_dupla_direita(raiz);
    }
    if (raiz->FB == -2){
        if (raiz->dir->FB <= 0) raiz = avl_rotaciona_esquerda(raiz);
        else raiz = avl_rotaciona_dupla_esquerda(raiz);
    }
    return raiz;

}

bool avl_inserir(AVL *T, int numero){
    if (T == NULL) return false;
    NO *p = avl_cria_no(numero);
    if (p == NULL) return false;
    avl_inserir_aux(T->raiz, p);
    return true;
}

int *avl_buscar_aux(NO *raiz, int chave){
    if (raiz == NULL) return NULL;
    if (raiz->numero == chave) return raiz->numero;
    if (raiz->numero > chave) return avl_buscar_aux(raiz->esq, chave);
    return avl_buscar_aux(raiz->dir, chave);
}

int *avl_buscar(AVL *T, int chave){
    if (T == NULL || T->raiz == NULL) return NULL;
    return avl_buscar_aux(T->raiz, chave);
}

void troca_max_esq(NO *troca, NO *raiz, NO *ant){
    if (troca->dir != NULL){
        troca_max_esq(troca->dir, raiz, troca);
    }
    else if (raiz == ant){
        ant->esq = troca->esq;
    }else{
        ant->dir = troca->esq;
    }
    raiz->numero = troca->numero;
    free(troca);
    troca = NULL;
    return;
}

bool avl_excluir_aux(NO **raiz, int chave){
    if (*raiz == NULL) return false;
    if ((*raiz)->numero > chave){
        return avl_excluir_aux(&(*raiz)->esq, chave);
    }
    else if((*raiz)->numero < chave){
        return avl_excluir_aux(&(*raiz)->dir, chave);
    }
    else{
        NO *p = *raiz;
        if(p->esq == NULL || p->dir == NULL){
            if (p->esq == NULL){
                *raiz = p->dir;
            }else{
                *raiz = p->esq;
            }
            free(p);
            p = NULL;
        }
        else{
            troca_max_esq((*raiz)->esq, *raiz, *raiz);
        }
        return true;
    }
}

bool avl_excluir(AVL *T, int chave){
    if (T == NULL || T->raiz == NULL) return false;
    NO *p = T->raiz;
    return avl_excluir_aux(&p, chave);
}

bool avl_apagar_aux(NO **raiz){
    if (*raiz == NULL) return false;
    avl_apagar_aux(&(*raiz)->esq);
    avl_apagar_aux(&(*raiz)->dir);
    free(*raiz);
    *raiz = NULL;
    return true;
}

bool avl_apagar(AVL **T){
    if (*T == NULL) return false;
    avl_apagar_aux(&(*T)->raiz);
    free(*T);
    *T = NULL;
    return true;
}

void avl_imprimir_aux(NO *raiz){
    if (raiz == NULL) return;
    avl_imprimir_aux(raiz->esq);
    printf("Raiz: %d\n", raiz->numero);
    avl_imprimir_aux(raiz->dir);
}

void avl_imprimir(AVL *T){
    if (T == NULL || T->raiz == NULL) return;
    avl_imprimir_aux(T->raiz);
}

bool pertence(AVL *T, int chave){
    return (avl_buscar(T, chave) != NULL);
}

void uniao_aux(AVL *T, NO *raiz){
    if (raiz == NULL) return;
    uniao_aux(T, raiz->esq);
    avl_inserir(T, raiz->numero);
    uniao_aux(T, raiz->dir);
}

AVL *uniao(AVL *T1, AVL *T2){
    AVL *T = avl_criar();
    if (T1 == NULL || T2 == NULL) return T;
    uniao_aux(T, T1->raiz);
    uniao_aux(T, T2->raiz);    
    return T;
}