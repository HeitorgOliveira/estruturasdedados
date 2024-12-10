#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "ls.h" 

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
    
    LS *ls = ls_criar();
    ls_inserir(ls, 70);
    ls_inserir(ls, 90);
    ls_inserir(ls, 40);
    ls_inserir(ls, 90);
    ls_inserir(ls, 100);
    ls_inserir(ls, 10);
    ls_inserir(ls, 80);
    ls_inserir(ls, 80);
    ls_inserir(ls, 60);
    ls_inserir(ls, 50);
    ls_imprimir(ls);
    ls_inserir(ls, 110);
    ls_inserir(ls, 120);
    ls_imprimir(ls);
    ls_remover(ls, 110);
    ls_remover(ls, 1);
    ls_inserir(ls, 130);
    ls_imprimir(ls);

    
}