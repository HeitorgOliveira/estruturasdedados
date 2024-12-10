#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "ls.h" 
#include "conjunto.h"

int main(void){
    CONJUNTO* CT1 = conjunto_criar('A');
    conjunto_inserir(CT1, 1);
    conjunto_inserir(CT1, 2);
    conjunto_inserir(CT1, 4);
    conjunto_inserir(CT1, 5);
    CONJUNTO* CT2 = conjunto_criar('L');
    conjunto_inserir(CT2, 4);
    conjunto_inserir(CT2, 5);
    conjunto_inserir(CT2, 6);
    conjunto_inserir(CT2, 7);
    conjunto_inserir(CT2, 8);
    
    

    printf("T1\n");
    CONJUNTO* interseccao_t1_t2 = conjunto_interseccao(CT1, CT2);
    conjunto_imprimir(interseccao_t1_t2);
    
    LS *ls = ls_criar();
    ls_inserir(ls, 70);
    ls_inserir(ls, 90);
    ls_inserir(ls, 40);
    ls_inserir(ls, 90);
    ls_inserir(ls, 100);
    ls_inserir(ls, 10);
    
    ls_imprimir(ls);



}