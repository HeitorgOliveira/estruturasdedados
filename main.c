#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "rb.h"

int main(void){
    /*AVL *T = avl_criar();
    avl_inserir(T, 1);
    avl_inserir(T, 2);
    avl_inserir(T, 3);
    avl_inserir(T, 4);
    AVL *T2 = avl_criar();
    avl_inserir(T2, 4);
    avl_inserir(T2, 5);
    avl_inserir(T2, 6);
    avl_inserir(T2, 7);
    avl_inserir(T2, 8);
    AVL *T3 = avl_uniao(T, T2);
    printf("--------- Arvore 3 ---------\n");
    avl_imprimir(T3);
    printf("----------------------------\n");
    printf("--------- Arvore 4 ---------\n");
    AVL *T4 = avl_interseccao(T, T2);
    avl_imprimir(T4);
    printf("----------------------------\n");*/
    
    RB *rb = rb_criar();
    rb_inserir(rb, 17);
    rb_inserir(rb, 56);
    rb_inserir(rb, 43);
    rb_inserir(rb, 15);
    rb_inserir(rb, 88);
    rb_inserir(rb, 45);
    rb_inserir(rb, 92);
    rb_inserir(rb, 41);
    rb_inserir(rb, 33);
    rb_inserir(rb, 3);
    rb_inserir(rb, 34);
    rb_imprimir(rb);
    rb_remover(rb, 88);
    rb_remover(rb, 45);
    rb_remover(rb, 92);
    rb_remover(rb, 41);
    rb_remover(rb, 15);
}