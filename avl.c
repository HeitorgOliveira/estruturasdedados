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

ITEM *avl_buscar_aux(NO *raiz, int chave){
    if (raiz == NULL) return NULL;
    if (item_get_chave(raiz->item) == chave) return raiz->item;
    if (item_get_chave(raiz->item) > chave) return avl_buscar_aux(raiz->esq, chave);
    return avl_buscar_aux(raiz->dir, chave);
}

ITEM *avl_buscar(AVL *T, int chave){
    if (T == NULL || T->raiz == NULL) return NULL;
    return avl_busca_aux(T->raiz, chave);
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
    raiz->item = troca->item;
    item_excluir(troca->item);
    free(troca);
    troca = NULL;
    return;
}

bool avl_excluir_aux(NO **raiz, int chave){
    if (*raiz == NULL) return false;
    if (item_get_chave((*raiz)->item) > chave){
        return avl_excluir_aux(&(*raiz)->esq, chave);
    }
    else if(item_get_chave((*raiz)->dir) < chave){
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
    item_excluir(&(*raiz)->item);
    free(*raiz);
    *raiz = NULL;
    return true;
}

bool avl_apagar(AVL **T){
    if (*T == NULL) return false;
    return avl_apagar_aux(&(*T)->raiz);
}

void avl_imprimir_aux(NO *raiz){
    if (raiz == NULL) return;
    avl_imprimir_aux(raiz->esq);
    printf("Raiz: %d\n", item_get_chave(raiz->item));
    avl_imprimir_aux(raiz->dir);
}

void avl_imprimir(AVL *T){
    if (T == NULL || T->raiz == NULL) return;
    avl_imprimir_aux(T->raiz);
}

bool pertence(AVL *T, int chave){
    
}