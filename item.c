#include <item.h>
#include <stdlib.h>

typedef struct item ITEM;
struct item{
    int chave;
    void *conteudo;
};

ITEM *item_criar(int chave, void *conteudo){
    ITEM *item = (ITEM *) malloc(sizeof(ITEM));
    if (item == NULL) return NULL;
    item->chave = chave;
    item->conteudo = conteudo;
}

int item_get_chave(ITEM *item){
    if(item == NULL) return -1;
    return item->chave;
}

bool item_excluir(ITEM **item){
    if (*item == NULL) return false;
    free(*item);
    *item = NULL;
    return true;
}

void *item_get_valor(ITEM *item){
    if (item == NULL) return;
    return item->conteudo;
}