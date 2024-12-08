#ifndef AVL_H
    #define AVL_H
    #include <stdbool.h>
    #include <item.h>

    typedef struct avl AVL;

    AVL *avl_criar();
    bool avl_inserir(AVL *T, ITEM *item);
    bool avl_excluir(AVL *T, int chave);

#endif