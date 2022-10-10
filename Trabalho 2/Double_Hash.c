#include <stdio.h>
#include <stdlib.h>

#define hash(V, M) (V % M)
#define hashtwo(V, M) (V % 97 + 1)

typedef struct Item
{
  int chave;
  int chave2;
  long e1, e2;
  long elemento;
} Item;

Item NULLItem = {
    0, 0, 0, 0, 0};

#define key(x) (x.chave)
#define key2(x) (x.chave2)
#define less(a, b) (key(a) < key(b))
#define null(A) (key(ht[A]) == key(NULLItem))
static int N;
int M = 100;

static Item *ht;

void HTInit(int max)
{
  int i;
  N = 0, M = 2 * max;
  ht = malloc(sizeof(Item) * M);
  for (int i = 0; i < M; i++)
  {
    ht[i] = NULLItem;
  }
}

int HTCount()
{
  return N;
}

void expand(int chave);

void HTinsert(Item item, int chave)
{
  int V = chave;
  int i = hash(V, M);
  int k = hashtwo(V, M);
  while (!null(i))
    i = (i + k) % M;
  ht[i] = item;
  N++;
  if (N >= M / 2)
    expand(chave);
}

Item HTsearch(int chave)
{
  int V = chave;
  int i = hash(V, M);
  int k = hashtwo(V, M);
  while (!null(i))
    if (V == key(ht[i]))
      return ht[i];
    else
      i = (i + k) % M;
  return NULLItem;
}

void expand(int chave)
{
  int i;
  Item *t = ht;
  ht = malloc(sizeof(Item) * M * 2);
  M = M * 2;
  for (i = 0; i < M / 2; i++)
    if (key(t[i]) != key(NULLItem))
      HTinsert(t[i], chave);
  free(t);
}

int main(void)
{
  int linha, coluna;
  float pi = 3.14159265;
  int chave;
  Item matriz;
  scanf("%d %d", &linha, &coluna);
  chave = (linha * pi) + (coluna * pi) * pi + (linha);
  matriz.chave = chave;
  matriz.chave2 = coluna;
  matriz.elemento = 2500;
  HTInit(300);
  HTinsert(matriz, chave);
  scanf("%d %d", &linha, &coluna);
  chave = (linha * pi) + (coluna * pi) * pi + (linha);
  matriz.chave = chave;
  matriz.chave2 = coluna;
  matriz.elemento = 3500;
  HTinsert(matriz, chave);
  matriz = HTsearch((7 * pi) + (4 * pi) * pi + (7));
  printf("Retornou a pontuacao: %d \n", matriz.elemento);

  return 0;
}
