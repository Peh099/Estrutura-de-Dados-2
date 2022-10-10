#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int number;
  char keyword[15];
} instrucao;

void insertionSort(instrucao vet[], int left, int right)
{
  int temp, i, j;
  char tempkey[15];

  for (i = 0; i < right; i++)
  {
    temp = vet[i].number;
    strcpy(tempkey, vet[i].keyword);
    for (j = i; (j > 0) && (temp < vet[j - 1].number); j--)
    {
      vet[j].number = vet[j - 1].number;
      strcpy(vet[j].keyword, vet[j - 1].keyword);
    }
    vet[j].number = temp;
    strcpy(vet[j].keyword, tempkey);
  }
}

int bb(int x, instrucao v[], int e, int d)
{
  int meio = (e + d) / 2;
  if (v[meio].number == x)
    return meio;
  if (e >= d)
    return -1;
  else if (v[meio].number < x)
    return bb(x, v, meio + 1, -d);
  else
    return bb(x, v, e, meio - 1);
}

int main()
{
  int n = 0;
  scanf("%d", &n);
  instrucao *p = malloc(n * sizeof(instrucao));

  for (int i = 0; i < n; i++)
  {
    scanf("%d %s", &p[i].number, p[i].keyword);
  }

  insertionSort(p, 0, n);

  int numbers, cont = 0, temp = 0;
  while (scanf("%d", &numbers) != EOF)
  {
    temp = bb(numbers, p, 0, n);
    if (temp != -1)
    {
      printf("%s\n", p[temp].keyword);
    }
    else
    {
      printf("undefined\n");
    }
  }

  return 0;
}