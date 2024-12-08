#ifndef ABB_H
    #define ABB_H
    #include <stdbool.h>
    #include <item.h>
    typedef struct abb ABB;

    ABB *abb_criar();
    bool abb_inserir(ABB *T, ITEM *item);
    ITEM *abb_busca(ABB *T, int chave);
    bool abb_excluir_item(ABB *T, int chave);

#endif