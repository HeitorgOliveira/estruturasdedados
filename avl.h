#ifndef AVL_H
    #define AVL_H
    #include <stdbool.h>

    typedef struct avl AVL;

    AVL *avl_criar();
    bool avl_inserir(AVL *T, int numero);
    bool avl_excluir(AVL *T, int numero);
    int *avl_buscar(AVL *T, int numero);
    bool avl_apagar(AVL **T);

#endif