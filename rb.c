#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct no{
    struct no *esquerda;
    struct no *direita;
    bool vermelho;
    int chave;
};