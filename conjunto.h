#ifndef CONJUNTO_H
#define CONJUNTO_H
  #include "avl.h" 
  #include "ls.h" 
 typedef struct conjunto CONJUNTO;

  CONJUNTO *conjunto_criar(unsigned char tipo);
  bool conjunto_inserir(CONJUNTO *s, int elemento);
  bool conjunto_remover(CONJUNTO *s, int elemento);
  void conjunto_apagar(CONJUNTO **s);
  void conjunto_imprimir(CONJUNTO *s);
  bool conjunto_pertence(CONJUNTO *A, int elemento);
  CONJUNTO *conjunto_uniao(CONJUNTO *A, CONJUNTO *B);
  CONJUNTO *conjunto_interseccao(CONJUNTO *A, CONJUNTO *B);
  void verificar_se_tem_ls(CONJUNTO* s);
  
#endif