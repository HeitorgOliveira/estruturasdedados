#ifndef LS_H
    #define LS_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "avl.h"

    typedef struct ls LS;
    LS* ls_criar();
    bool ls_inserir(LS* ls, int valor);
    bool ls_excluir(LS* ls, int valor);
    bool ls_apagar(LS* ls);
    void ls_imprimir(LS* ls);
    LS* ls_interseccao(LS* A, LS* B);
    LS* ls_uniao(LS* A, LS* B);
    bool ls_pertence(LS* ls, int chave);
    bool ls_insere_em_avl(AVL* avl, LS* ls);
#endif