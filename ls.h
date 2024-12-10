#ifndef LS_H
    #define LS_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct ls LS;
    LS* ls_criar(int tam);
    bool ls_inserir(LS* ls, int valor);
    void ls_imprimir(LS* ls);
    bool ls_remover(LS* ls, int valor);
#endif