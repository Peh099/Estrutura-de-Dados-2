#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
  int dado;
  struct no *esq, *dir;
} no;

typedef struct celula
{
  no *dado;
  struct celula *prox;
} celula;

int empilha(celula *p, no *x)
{
  celula *novo = malloc(sizeof(celula));
  if (novo == NULL)
    return 0;
  novo->dado = x;
  novo->prox = p->prox;
  p->prox = novo;
  return 1;
}

celula *criar_lista()
{
  celula *le = malloc(sizeof(celula));
  le->prox = NULL;
  return le;
}

int vazia(celula *pilha)
{
  if (pilha->prox == NULL)
    return 1;
  else
    return 0;
}

int desempilha(celula *p, no *y)
{
  celula *lixo = p->prox;
  if (lixo == NULL)
    return 0;
  p->prox = lixo->prox;
  y = lixo->dado;
  free(lixo);
  return 1;
}

void pre_ordem(no *raiz)
{
  celula *pilha;
  pilha = criar_lista();
  no *x;
  if (raiz != NULL)
  {
    empilha(pilha, raiz);
    while (!vazia(pilha))
    {
      desempilha(pilha, x);
      if (x != NULL)
      {
        empilha(pilha, x->esq);
      }
      else
      {
        if (vazia(pilha))
          break;
        desempilha(pilha, x);
        printf("%d\n", x->dado);
        empilha(pilha, x->dir);
      }
    }
  }
}
