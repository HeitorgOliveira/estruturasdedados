#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "ls.h" 
#include "conjunto.h"
int main(void){
    CONJUNTO *CT1, *CT2;
    int n_a, n_b, x;
    int operacao;
    int tipo;
    unsigned char c;

    printf("Digite o tipo de conjunto que deseja criar: '0' para AVL e '1' para Lista Sequencial\n");
    scanf("%d", &tipo);
    if(tipo==0){
        c = 'A';
    }else{
        c = 'L';
    }
    CT1 = conjunto_criar(c);
    CT2 = conjunto_criar(c);

    scanf("%d %d", &n_a, &n_b);

    for(int i=0; i<n_a; i++){
        scanf("%d",&x);
        conjunto_inserir(CT1, x);
    }
    for(int i=0; i<n_b; i++){
        scanf("%d",&x);
        conjunto_inserir(CT2, x);
    }
    scanf("%d", &operacao);
    
    switch(operacao){
        case 1:{//pertencimento ao conjunto 1
            scanf("%d", &x);
            if(conjunto_pertence(CT1, x)){
                printf("Pertence.", x);
            }else{
                printf("Nao pertence.", x);
            }
            break;
        }
        case 2:{// uniao
            CONJUNTO *uniao = conjunto_uniao(CT1, CT2);
            conjunto_imprimir(uniao);
            break;
        }
        case 3:{// interseccao
            CONJUNTO *interseccao = conjunto_interseccao(CT1, CT2);
            conjunto_imprimir(interseccao);
            break;
        }
        case 4:{// remocao
            scanf("%d", &x);
            conjunto_remover(CT1, x);
            conjunto_imprimir(CT1);
            break;
        }
    }
    conjunto_apagar(&CT1);
    conjunto_apagar(&CT2);
    
    
}