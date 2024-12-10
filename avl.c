#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct avl AVL;
typedef struct no NO;

struct no{
    NO *esq;
    NO *dir;
    int FB;
    int numero;
};

struct avl{
    NO *raiz;
};

// A função avl_criar cria uma árvore AVL e a retorna
AVL *avl_criar(){
    AVL *avl = (AVL*) malloc(sizeof(AVL));
    if (avl == NULL) return NULL;
    avl->raiz = NULL;
    return avl;
}

// A função avl_cria_no cria um nó com o número informado pelo usuário
NO *avl_cria_no(int numero){
    NO *no = (NO*) malloc(sizeof(NO));
    if (no == NULL) return NULL;
    no->numero = numero;
    no->esq = no->dir = NULL;
    no->FB = 0;
    return no;
}

// A função altura é uma função auxiliar que retorna a altura de um nó
int altura(NO *raiz){
    if (raiz == NULL) return 0;
    int esquerda = altura(raiz->esq);
    int direita = altura(raiz->dir);
    return 1 + (direita > esquerda ? direita : esquerda);
}

// A função balanceada é uma função auxiliar que verifica se a árvore está balanceada ou não
bool balanceada(NO *raiz){
    if (raiz == NULL) return true;
    int esquerda = altura(raiz->esq);
    int direita = altura(raiz->dir);
    if (abs(esquerda - direita) > 1){
        return false;
    }else return (balanceada(raiz->esq) && balanceada(raiz->dir));
}

// Abaixo estão as funções mais importantes das árvores AVL: As rotações.
// As rotações garantem que o fator de balanceamento da árvore não exceda modulo 1
// em geral existem 4 tipos de rotações: As rotações esquerdas, direitas, duplas esquerdas e duplas direitas

// A função avl_rotaciona_esquerda é responsável por rotacionar a árvore para a esquerda
NO *avl_rotaciona_esquerda(NO *no){
    // A rotação se baseia em uma troca de vetores, nesse caso fazemos o nó da esquerda trocar de lugar com o da direita
    NO *aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    no->FB = aux->FB = 0;
    return aux;
}

// A função avl_rotaciona_direita rotaciona a árvore para a direita
NO *avl_rotaciona_direita(NO *no){
    NO *aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;

    no->FB = aux->FB = 0;
    return aux;
}

// Rotação dupla esquerda
NO *avl_rotaciona_dupla_esquerda(NO *no){
    // Rotacionamos uma vez para a direita e deopis para e esquerda
    no->dir = avl_rotaciona_direita(no->dir);
    return avl_rotaciona_esquerda(no);
}

// Rotação dupla direita
NO *avl_rotaciona_dupla_direita(NO *no){
    // Simplesmente rotacionamos uma vez para a esquerda e depois rotacionamos para a direita
    no->esq = avl_rotaciona_esquerda(no->esq);
    return avl_rotaciona_direita(no);
}

// A função auxiliar avl_inserir_aux() insere um nó na árvore AVL e faz as verificações de balanceamento.
// Caso seja necessário, chamamos as funções responsáveis pela rotação para balancear a árvore.
NO *avl_inserir_aux(NO *raiz, NO *no){
    // Inserimos o nó
    if (raiz == NULL){
        return no;
    }
    else if (raiz->numero > no->numero){
        raiz->esq = avl_inserir_aux(raiz->esq, no);
    }else{
        raiz->dir = avl_inserir_aux(raiz->dir, no);
    }

    // Verificamos o balanceamento
    raiz->FB = altura(raiz->esq) - altura(raiz->dir);

    // Caso o fator de balanceamento (FB = altura da esquerda - altura da direita) seja igual a dois, ou seja, a árvore está
    // desbalanceada, com o lado esquerdo mais alto que o direito, nós chamamos uma rotação para a direita. Simples ou dupla
    if (raiz->FB == 2){
        // Caso seu filho esquerdo não esteja com FB = -1, ou seja, não tenha sinais trocados com a raiz, nós chamamos uma
        // rotação simples para a direita
        if (raiz->esq->FB >= 0) raiz = avl_rotaciona_direita(raiz);
        // Caso tenham sinais trocados chamamos uma rotação dupla para a direita
        else raiz = avl_rotaciona_dupla_direita(raiz);
    }
    // Se a árvore estiver com a altura direita maior que a esquerda precisamos fazer uma rotação para a esquerda, seja ela
    // simples ou dupla
    if (raiz->FB == -2){
        // Se o sinal de seu filho direito for o mesmo que a raiz, chamaos uma rotação simples para a esquerda
        if (raiz->dir->FB <= 0) raiz = avl_rotaciona_esquerda(raiz);
        // Se seu filho direito tiver o sinal contrárioà raiz, realizamos uma rotação dupla à direita
        else raiz = avl_rotaciona_dupla_esquerda(raiz);
    }
    return raiz;
}

// A função avl_inserir insere na árvore um nó com o número informado pelo usuário
// Para isso fizemos uso da função auxiliar avl_inserir_aux()
bool avl_inserir(AVL *T, int numero){
    if (T == NULL) return false;
    NO *p = avl_cria_no(numero);
    if (p == NULL) return false;
    T->raiz = avl_inserir_aux(T->raiz, p);
    return true;
}

// A função avl_buscar_no_aux() percorre a árvore em in-order procurando pela chave
int *avl_buscar_aux(NO *raiz, int chave){
    if (raiz == NULL) return NULL;
    // visita a raiz
    if (raiz->numero == chave) return &(raiz->numero);
    // percorre a esquerda da árvore
    if (raiz->numero > chave) return avl_buscar_aux(raiz->esq, chave);
    // percorre a direita da árvore
    return avl_buscar_aux(raiz->dir, chave);
}

// A função avl_buscar procura por um nó com a chave escolhida e retorna um ponteiro para seu número
// para isso usamos a função auxiliar avl_buscar_aux()
int *avl_buscar(AVL *T, int chave){
    if (T == NULL || T->raiz == NULL) return NULL;
    return avl_buscar_aux(T->raiz, chave);
}

// A função troca_max_esq() é a função auxiliar para a remoção de nós com dois filhos.
// a função percorre a direita do nó mais à esquerda da raiz até chegar numa folha.
// após isso trocamos o nó a ser removido com a folha e apagamos ele
void troca_max_esq(NO *troca, NO *raiz, NO *ant){
    // Enquando o nó tiver filhos à direita, chamamos a função recursivamente para chegar no maior valor
    if (troca->dir != NULL){
        troca_max_esq(troca->dir, raiz, troca);
    }
    // Ao chegarmos na folha verificamos se percorremos pelo menos um nó para a direita
    // se a raiz é igual ao anterior, ou seja, não percorremos nenhum nó à direita, nós pegamos o nó à esquerda de anterior
    // para ser o novo nó acima
    else if (raiz == ant){
        ant->esq = troca->esq;
    }
    // Se pelo menos um nó à direita foi percorrido, trocamos essa folha para que seja o novo nó
    else{
        ant->dir = troca->esq;
    }
    // trocamos o valor dos números dos nós e apagamos o alvo
    raiz->numero = troca->numero;
    free(troca);
    troca = NULL;
    return;
}

// A função avl_excluir_aux remove o nó alvo da árvore usando a abordagem estudada em aula
// 1 - se o nó for uma folha, apenas excluimos ele
// 2 - se o nó tiver um filho, trocamos ele de lugar com o seu filho, levando o alvo para o caso 1.
// 3 - se o nó tiver dois filhos, trocamos ele de lugar com: 3.1 - O maior filho à esquerda 3.2 - o menor filho à direita e retornamos ao caso 1
// nesse caso fizemos a abordagem em que o maior filho à esquerda é removido.
bool avl_excluir_aux(NO **raiz, int chave){
    if (*raiz == NULL) return false;
    // Para a remoção optamos por um percurso em postorder
    if ((*raiz)->numero > chave){
        return avl_excluir_aux(&(*raiz)->esq, chave);
    }
    else if((*raiz)->numero < chave){
        return avl_excluir_aux(&(*raiz)->dir, chave);
    }
    else{
        NO *p = *raiz;
        // Aqui contemplamos ambos os casos 1 e 2.
        if(p->esq == NULL || p->dir == NULL){
            if (p->esq == NULL){
                // Se a esquerda for vazia, trocamos de lugar com a direita
                *raiz = p->dir;
            }else{
                // Se a direita for vaiza trocamos de lugar com a esquerda
                *raiz = p->esq;
            }
            // apagamos o nó folha
            free(p);
            p = NULL;
        }
        else{
            // Caso o nó tenha dois filhos chamamos a função auxiliar troca_max_esq(), que remove o nó trocando ele de lugar
            // com o maior nó à esquerda
            troca_max_esq((*raiz)->esq, *raiz, *raiz);
        }
        return true;
    }
}

// A função avl_excluir apaga um nó da árvore dado seu número (chave).
// Para isso chamamos a função auxiliar avl_excluir_aux()
bool avl_excluir(AVL *T, int chave){
    if (T == NULL || T->raiz == NULL) return false;
    NO *p = T->raiz;
    return avl_excluir_aux(&p, chave);
}

// A função avl_apagar_aux apaga todos os nós da árvore. Para isso fizemos uso do percurso postorder
bool avl_apagar_aux(NO **raiz){
    if (*raiz == NULL) return false;
    // Percorremos a esquerda da árvore.
    avl_apagar_aux(&(*raiz)->esq);
    // Percorremos a direita da árvore.
    avl_apagar_aux(&(*raiz)->dir);
    // Apagamos o nó
    free(*raiz);
    *raiz = NULL;
    return true;
}

// A função avl_apagar apaga todos os nós contidos na árvore por meio de uma função auxiliar e depois apaga a estrutura árvore
bool avl_apagar(AVL **T){
    if (*T == NULL) return false;
    avl_apagar_aux(&(*T)->raiz);
    // apagamos os nós
    free(*T);
    *T = NULL;
    // apagamos a árvore
    return true;
}

// A função avl_imprimir_aux percorre a árvore com o percurso in-order exibindo o valor de seus nós
// escolhemos o percurso in-order pois é uma característica das árvores binárias de busca que os valores exibidos no
// percurso in-order estejam em ordem crescente. 
void avl_imprimir_aux(NO *raiz){
    if (raiz == NULL) return;
    // percorremos a esquerda da árvore
    avl_imprimir_aux(raiz->esq);
    // Visitamos o nó exibindo o valor de seu número
    printf("Número: %d\n", raiz->numero);
    // percorremos a esquerda da árvore
    avl_imprimir_aux(raiz->dir);
}

//A função avl_imprimir exibe todos os números armazenados na árvore escolhida
// para isso chamamos a função auxiliar avl_imprimir_aux().
void avl_imprimir(AVL *T){
    if (T == NULL || T->raiz == NULL) return;
    avl_imprimir_aux(T->raiz);
}

// A função avl pertence deve retornar um booleano (true ou false) de acordo com a existência ou não de um número
// na árvore alvo. Para isso fizemos uso de uma outra função "avl_buscar()"
// A função avl_buscar retorna um ponteiro para o número o encontre e retorna NULL em caso contrário
// usei essa função então para auxiliar na formação da função avl_pertence(), assim se o ponteiro retornado for NULL
// o elemento não pertence à árvore e deve ser retornado false. Em caso contrário retorna-se true.
bool avl_pertence(AVL *T, int chave){
    return (avl_buscar(T, chave) != NULL);
}


// A função auxiliar avl_uniao_aux() preenche a árvore T com os elementos da árvore que contenha o nó raiz
// Assim ela auxilia na função união pois colocamos todos os elementos de uma árvore original na árvore destino.
void avl_uniao_aux(AVL *T, NO *raiz){
    if (raiz == NULL) return;
    // Aqui decidi por usar um percurso em-ordem para variar o uso de percursos, mas qualquer um dos três percursos
    // em-ordem pos-ordem pre-ordem funcionam.
    avl_uniao_aux(T, raiz->esq);
    avl_inserir(T, raiz->numero);
    avl_uniao_aux(T, raiz->dir);
}


// A função avl_uniao() junta todos os elementos de duas arvores e insere esses elementos em uma terceira árvore
// que será retornada pela função.
AVL *avl_uniao(AVL *T1, AVL *T2){
    // criamos a árvore que vamos retornar
    AVL *T = avl_criar();
    if (T1 == NULL || T2 == NULL) return T;
    // Inserimos todos os elementos de T1 na árvore auxiliar.
    avl_uniao_aux(T, T1->raiz);
    // Inserimos todos os elementos de T2 na árvore auxiliar.
    avl_uniao_aux(T, T2->raiz);
    // Retornamos a árvore que ficou formada pelas junção das duas outras árvores.
    return T;
}

// Função auxiliar da função de interseccao
// A função percorre a árvore que contém raiz1 e verifica se seus nós
// também pertencem à T2 por meio da função pertence. caso o elemento esteja
// nas duas árvores, inserimos ele na arvore do argumento que será retornada.
AVL *interseccao_aux(NO *raiz1, AVL *T2, AVL *interseccao){
    if (raiz1 == NULL || T2 == NULL) return interseccao;

    // Aqui os nós que percorremos pertencem todos à uma árvore e os nós que verificamos no pertence(); pertencem a outra arvore.
    if (avl_pertence(T2, raiz1->numero)){
        // Caso o nó da arvore 1 esteja na arvore 2 inserimos ele na arvore auxiliar que será retornada.
        avl_inserir(interseccao, raiz1->numero);
    }

    // A abordagem utilizada para a função auxiliar foi um percurso em pre-order, assim primeiro visitamos o nó e depois
    // percorremos a esquerda e direita da arvore respectivamente.
    interseccao_aux(raiz1->esq, T2, interseccao);
    interseccao_aux(raiz1->dir, T2, interseccao);
    return interseccao;
}

// A função avl_interseccao verifica elementos que estejam contidos tanto em T1 como em T2
// e insere esses elementos em outra arvore que será retornada pela função.
AVL *avl_interseccao(AVL *T1, AVL *T2){
    // Inicializamos a arvore que será retornada.
    AVL *intersec = avl_criar();
    if (T1 == NULL || T2 == NULL) return intersec;
    // chamamos a função auxiliar.
    return interseccao_aux(T1->raiz, T2, intersec);
}
