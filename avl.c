#include <avl.h>
#include <item.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct avl AVL;
typedef struct no NO;

struct no{
    NO *esq;
    NO *dir;
    int FB;
    ITEM *item;
};

struct avl{
    NO *raiz;
};

NO *avl_cria_no(ITEM *item){
    NO *no = (NO*) malloc(sizeof(NO));
    if (no == NULL) return NULL;
    no->item = no->esq = no->dir = NULL;
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
    if (raiz = NULL){
        raiz = no;
    }
    else if (item_get_chave(raiz->item) > item_get_chave(no->item)){
        raiz->esq = avl_inserir_aux(raiz->esq, no);
    }else{
        raiz->dir = avl_inserir_aux(raiz->dir, no);
    }

    raiz->FB = altura(raiz->esq) - altura(raiz->dir);
    if (raiz->FB == 2){
        if (raiz->esq->FB >= 0) raiz = rotaciona_direita(raiz);
        else raiz = rotaciona_dupla_direita(raiz);
    }
    if (raiz->FB == -2){
        if (raiz->dir->FB <= 0) raiz = rotaciona_esquerda(raiz);
        else raiz = rotaciona_dupla_esquerda(raiz);
    }
    return raiz;

}

bool avl_inserir(AVL *T, ITEM *item){
    if (T == NULL) return false;
    NO *p = avl_cria_no(item);
    if (p == NULL) return false;
    avl_inserir_aux(T->raiz, p);
    return true;
}

