#ifndef ITEM_H
    #define ITEM_H
    #include <stdbool.h>

    typedef struct item ITEM;

    ITEM *item_criar(int chave, void *valo0r);
    bool item_excluir(ITEM **item);
    int item_get_chave(ITEM *item);
    void *item_get_valor(ITEM *item);

#endif