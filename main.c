#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "ls.h" 
#include "conjunto.h"

int main(void){
    CONJUNTO* CT1 = conjunto_criar('L');
    conjunto_inserir(CT1, 1);
    conjunto_inserir(CT1, 2);
    conjunto_inserir(CT1, 4);
    conjunto_inserir(CT1, 5);
    CONJUNTO* CT2 = conjunto_criar('L');
    verificar_se_tem_ls(CT2);
    conjunto_inserir(CT2, 4);
    conjunto_inserir(CT2, 5);
    conjunto_inserir(CT2, 6);
    conjunto_inserir(CT2, 7);
    conjunto_inserir(CT2, 8);
    conjunto_imprimir(CT1);
    printf("\n");
    conjunto_imprimir(CT2);
    
    

    printf("\nT1\n");
    CONJUNTO* interseccao_t1_t2 = conjunto_interseccao(CT1, CT2);
    
    conjunto_imprimir(interseccao_t1_t2);
    
    printf("T1\n");



}