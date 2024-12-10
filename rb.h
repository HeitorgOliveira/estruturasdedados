#ifndef RB_H
    #define RB_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct rb RB;
    RB* rb_criar();
    bool rb_inserir(RB *rb, int chave);
    bool rb_remover(RB *rb, int chave);
    void rb_apagar(RB **rb);
    void rb_imprimir(RB *rb);
    bool pertence(RB *rb, int chave);
#endif