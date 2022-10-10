#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
  char palavrajapones[80];
  char traducao[80];
} vetor;

int separa(int *v, int l, int r)
{
  int c = v[r];
  int j = l;
  int t;
  for (int k = l; k < r; k++)
  {
    if (v[k] < c)
    {
      t = v[k];
      v[k] = v[j];
      v[j] = t;
      j++;
    }
  }
  t = v[j];
  v[j] = v[r];
  v[r] = t;
  return j;
}
void quicksort(int *v, int l, int r)
{
  int j;
  if (r <= l)
    return;
  if (v[(l + r) / 2] > v[r])
  {
    int t;
    t = v[(l + r) / 2];
    v[(l + r) / 2] = v[r];
    v[r] = t;
  }
  if (v[l] > v[(l + r) / 2])
  {
    int t;
    t = v[l];
    v[l] = v[(l + r) / 2];
    v[(l + r) / 2] = t;
  }
  if (v[r] > v[(l + r) / 2])
  {
    int t;
    t = v[r];
    v[r] = v[(l + r) / 2];
    v[(l + r) / 2] = t;
  }
  j = separa(v, l, r);
  quicksort(v, l, j - 1);
  quicksort(v, j + 1, r);
}

int main()
{
  int t;
  int m = 0, n = 0;
  scanf("%d", &t);
  scanf("%d %d", &m, &n);
  vetor *new = malloc(m * sizeof(vetor));
  for (int i = 0; i < m; i++)
  {
    scanf("%s", new[i].palavrajapones);
    scanf(" %[^\n]", new[i].traducao);
  }

  for (int j = 0; j < n; j++)
  {
  }
  return 0;
}
