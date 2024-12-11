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
void verificar_se_tem_ls(CONJUNTO* s){
    if(s==NULL){
        return;
    }
    if(s->ls){
    }
}
bool conjunto_inserir (CONJUNTO *s, int elemento){
    if (s != NULL){
        return (s->avl != NULL ? avl_inserir(s->avl, elemento) : ls_inserir(s->ls, elemento));
    }
}

bool conjunto_remover(CONJUNTO *s, int elemento){
    if (s != NULL){
        return (s->avl != NULL ? avl_excluir(s->avl, elemento) : ls_excluir(s->ls, elemento));
    }
}

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

void conjunto_imprimir(CONJUNTO *s){
    if (s != NULL){
        s->avl != NULL ? avl_imprimir(s->avl) : ls_imprimir(s->ls);
    }
}

bool conjunto_pertence(CONJUNTO *A, int elemento){
    if (A != NULL){
        return (A->avl != NULL ? avl_pertence(A->avl, elemento) : ls_pertence(A->ls, elemento));
    }
}

void conjunto_uniao_aux(NO *raiz, LS *ls, AVL *T){
    if (raiz == NULL || T == NULL) return;
    avl_inserir(T, raiz->numero);
    conjunto_uniao_aux(raiz->esq, ls, T);
    conjunto_uniao_aux(raiz->dir, ls, T);
}

CONJUNTO *conjunto_uniao(CONJUNTO *A, CONJUNTO *B){
    if (A != NULL && B != NULL){
        
        if (A->avl != NULL && B->avl != NULL){
            CONJUNTO *conjunto = conjunto_criar('A');
            conjunto->avl = avl_uniao(A->avl, B->avl);
            return conjunto;
        }
        if (A->ls != NULL && B->ls != NULL){
            CONJUNTO *conjunto = conjunto_criar('L');
            conjunto->ls = ls_uniao(A->ls, B->ls);
            return conjunto;
        }
        else{
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

void conjunto_interseccao_aux(NO *raiz, LS *ls, AVL *T){
    if (T == NULL || raiz == NULL) return;
    if (ls_pertence(ls, raiz->numero)){
        avl_inserir(T, raiz->numero);
    }
    conjunto_interseccao_aux(raiz->esq, ls, T);
    conjunto_interseccao_aux(raiz->dir, ls, T);
}

CONJUNTO *conjunto_interseccao(CONJUNTO *A, CONJUNTO *B) {
    if (A == NULL || B == NULL) {
        return NULL;
    }

    CONJUNTO *conjunto = NULL;

    if (A->avl != NULL && B->avl != NULL) {
        conjunto = conjunto_criar('A');
        conjunto->avl = avl_interseccao(A->avl, B->avl);
    }
    else if (A->ls != NULL && B->ls != NULL) {
        conjunto = conjunto_criar('L');
        conjunto->ls = ls_interseccao(A->ls, B->ls);
    }
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