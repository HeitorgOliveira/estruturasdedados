#ifndef AB_H
    #define AB_H
    #include <stdbool.h>
    #include <item.h>

    typedef struct ab AB;

    AB *ab_criar_arvore();
    bool ab_inserir_lado(AB *T, ITEM *item, int lado, int chave);
    ITEM *ab_encontrar(AB *T, int chave);
    bool ab_apagar_no(AB *T, int chave);
    bool ab_excluir(AB **T);

#endif