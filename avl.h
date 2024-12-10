#ifndef AVL_H
    #define AVL_H
    #include <stdbool.h>

    typedef struct avl AVL;

    AVL *avl_criar();
    bool avl_inserir(AVL *T, int numero);
    bool avl_excluir(AVL *T, int numero);
    bool avl_apagar(AVL **T);
    void avl_imprimir(AVL *T);
    AVL *avl_interseccao(AVL *T1, AVL *T2);
    AVL *avl_uniao(AVL *T1, AVL *T2);
    bool avl_pertence(AVL *T, int chave);

#endif