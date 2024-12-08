#include <abb.h>
#include <item.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct no NO;
struct no{
    NO *esq;
    NO *dir;
    ITEM *item;
};
struct abb{
    NO *raiz;
    int profundidade;
};

NO *abb_criar_no(ITEM *item){
    if (item == NULL) return NULL;
    NO *no = (NO*) malloc(sizeof(NO));
    no->item = item;
    no->esq = no->dir = NULL;
    return no;
}

ABB *abb_criar(){
    ABB *abb = (ABB *) malloc(sizeof(ABB));
    if (abb == NULL) return NULL;
    abb->raiz = NULL;
    abb->profundidade = -1;
    return abb;
}

NO *abb_inserir_no(NO *raiz, NO *no){
    if (raiz == NULL){
        raiz = no;
    }
    else if (item_get_chave(raiz->item) > item_get_chave(no->item)){
        raiz->esq = abb_inserir_no(raiz->esq, no);
    }
    else{
        raiz->dir = abb_inserir_no(raiz->dir, no);
    }return raiz;
}

bool abb_inserir(ABB *T, ITEM *item){
    if (T == NULL) return NULL;
    NO *no;
    no = abb_criar_no(item);
    if (no != NULL){
        abb_inserir_no(T->raiz, no);
        return true;
    }
}

ITEM *abb_busca_no(NO *raiz, int chave){
    if (raiz == NULL) return NULL;
    if (item_get_chave(raiz->item) == chave){
        return raiz->item;
    }
    else if (item_get_chave(raiz->item) > chave){
        return abb_busca_no(raiz->esq, chave);
    } else{
        return abb_busca_no(raiz->dir, chave);
    }
}

ITEM *abb_busca(ABB *T, int chave){
    if (T == NULL) return NULL;
    return abb_busca_no(T->raiz, chave);
}

bool troca_max_esq(NO *troca, NO* raiz, NO*ant){
    if (troca->dir != NULL){
        troca_max_esq(troca->dir, raiz, troca);
    }
    if (raiz == ant){
        ant->esq = troca->esq;
    }else{
        ant->dir = troca->esq;
    }
    raiz->item = troca->item;
    free(troca);
    troca = NULL;
}

bool abb_remover_aux(NO **raiz, int chave){
    if (*raiz ==  NULL) return false;
    NO *p;
    if (item_get_chave((*raiz)->item) == chave){
        /*Tratar a remoção adequadamente*/

        // Caso em que pelo menos um dos filhos é NULL
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            p = *raiz;
            if (p->esq == NULL){
                *raiz = p->dir;
            }else if(p->dir == NULL){
                *raiz = p->esq;
            }
            item_excluir(p->item);
            free(p);
            p = NULL;
        }
        else{
            troca_max_esq((*raiz)->esq, (*raiz), (*raiz));
        }
        return true;
    }
    else if(item_get_chave((*raiz)->item) > chave){
        return abb_remover_aux(&(*raiz)->esq, chave);
    }
    else{
        return abb_remover_aux(&(*raiz)->dir, chave);
    }
}


bool abb_excluir_item(ABB **T, int chave){
    if (*T == NULL) return false;
    return abb_excluir_no(&(*T)->raiz, chave);
}