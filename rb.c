#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rb.h"

typedef struct no NO;
typedef struct no{
    NO* esquerda;
    NO*direita;
    bool vermelho;
    int chave;
}

struct rb{
    NO*
};
