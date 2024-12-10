#ifndef RB_H
    #define RB_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct ls LS;
    LS* ls_criar(int tam);
    int encontrar_posicao(LS* ls, int valor);
#endif