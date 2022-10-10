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
  int i, j;
  instrucao temp;

  for (i = 1; i < right; i++)
  {
    temp = vet[i];
    for (j = i; (j > 0) && (temp.number < vet[j - 1].number); j--)
    {
      vet[j] = vet[j - 1];
    }
    vet[j] = temp;
  }
}

int bb(instrucao v[], int key, int Tam)
{
  int left = 0;
  int right = Tam - 1;
  int mid;
  while (left <= right)
  {
    mid = (left + right) / 2;
    if (key == v[mid].number)
      return mid;
    if (key < v[mid].number)
      right = mid - 1;
    else
      left = mid + 1;
  }
  return -1;
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
    temp = bb(p, numbers, n);
    if (temp != -1)
    {
      printf("%s\n", p[temp].keyword);
    }
    else
    {
      printf("undefined\n");
    }
  }
  free(p);

  return 0;
}