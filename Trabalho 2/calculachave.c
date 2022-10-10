#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int vetor[27];
  int linha, coluna;
  float pi = 3.14159265;
  int chave;
  for (int i = 0; i < 4; i++)
  {
    scanf("%d %d", &linha, &coluna);
    chave = (linha * pi) + (coluna * pi) * pi + (linha);
    vetor[i] = chave;
    //printf("i:%d\n", i);
  }
  for (int i = 0; i < 4; i++)
  {
    printf("%d\n", vetor[i]);
  }
  return 0;
}