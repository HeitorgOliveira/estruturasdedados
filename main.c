#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "item.h"
#include "rb.h"

int main(void){
    AVL *T = avl_criar();
    avl_inserir(T, item_criar(1, 1));
    avl_inserir(T, item_criar(2, 2));
    avl_inserir(T, item_criar(3, 3));
    avl_inserir(T, item_criar(4, 4));
    AVL *T2 = avl_criar();
    avl_inserir(T2, item_criar(5, 5));
    avl_inserir(T2, item_criar(6, 6));
    avl_inserir(T2, item_criar(7, 7));
    avl_inserir(T2, item_criar(8, 8));
    AVL *T3 = uniao(T, T2);
    avl_imprimir(T3);
}