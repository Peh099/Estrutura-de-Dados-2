#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
  unsigned long endereco;
  unsigned long anterior;
  unsigned long prox;
} no;

void merge(no *v, int left, int right1, int right2)
{
  no *vet1 = malloc(sizeof(no) * (right2 - left + 1));
  int k = 0;
  int i = left;
  int j = right1 + 1;

  while (i <= right1 && j <= right2)
  {
    if (v[i].endereco <= v[j].endereco)
      vet1[k++] = v[i++];
    else
      vet1[k++] = v[j++];
  }

  while (i <= right1)
    vet1[k++] = v[i++];
  while (j <= right2)
    vet1[k++] = v[j++];
  k = 0;
  for (i = left; i <= right2; i++)
    v[i] = vet1[k++];
  free(vet1);
}

void mergeSortRecursive(no *v, int left, int right)
{
  if (left >= right)
    return;
  int meio = (right + left) / 2;
  mergeSortRecursive(v, left, meio);
  mergeSortRecursive(v, meio + 1, right);
  merge(v, left, meio, right);
}

int bb(no v[], int key, int Tam)
{
  //printf("%d ",key);
  int left = 0;
  int right = Tam - 1;
  int mid;
  while (left <= right)
  {
    mid = (left + right) / 2;

    //printf("%d ",mid);
    if (key == v[mid].endereco)
      return mid;
    if (key < v[mid].endereco)
    {
      //printf("menor\n");
      right = mid - 1;
    }
    else
      left = mid + 1;
  }
  return -1;
}

int main()
{
  no v[250000], ptr1, ptr2;
  int i = 0, c = 0;
  while (scanf("%x %x %x", &v[i].endereco, &v[i].anterior, &v[i].prox) != EOF)
  {
    if (i == 0)
    {
      ptr1.endereco = v[0].endereco;
      ptr1.anterior = v[0].anterior;
      ptr1.prox = v[0].prox;
    }
    else if (i == 1)
    {
      ptr2.endereco = v[1].endereco;
      ptr2.anterior = v[1].anterior;
      ptr2.prox = v[1].prox;
    }
    i++;
  }
  mergeSortRecursive(v, 0, i);
  for (int j = 0; j < i; j++)
  {
    int d = 0;
    d = bb(v, v[j].prox, i);
    printf("%d\n", d);
  }

  return 0;
}