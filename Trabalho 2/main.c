#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct matriz
{
  int pontos;
} matriz;

void iniciador_tabela_hash(int *tabela_hash, int tamanho)
{
  int i;

  for (i = 0; i < tamanho; i++)
  {
    tabela_hash[i] = 0;
    tabela_hash[i] = 0;
  }
}

void gera_matriz(int matriz[6][6])
{

  int i, j, numAleatorios;

  srand(time(NULL));

  // gera os números aleatórios e imprime a matriz
  for (i = 0; i < 6; i++)
  {
    for (j = 0; j < 6; j++)
    {
      numAleatorios = (rand() % 99) + 1;
      matriz[i][j] = numAleatorios;
    }
  }
}
int sondagem(int linha, int coluna)
{
}

int main()
{
  matriz *tabela_hash;
  int Matriz[6][6];
  int l, c, p, t;
  scanf("%d %d %d %d", &l, &c, &p, &t);
  tabela_hash = (matriz *)malloc(sizeof(matriz) * t);
  iniciador_tabela_hash(tabela_hash, t);
  gera_matriz(Matriz);
  Matriz[l][c] = p;
  printf("%d", Matriz[l][c]);
  return 0;
}