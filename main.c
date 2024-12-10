#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "ls.h" 
#include "conjunto.h"

int main(void){
    AVL *T = avl_criar();
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

    CONJUNTO* uniao_t1_t2 = conjunto_uniao(T, T2);
    conjunto_imprimir(uniao_t1_t2);
    
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
    ls_excluir(ls, 110);
    ls_excluir(ls, 1);
    ls_inserir(ls, 130);
    ls_imprimir(ls);



}