#include <stdio.h>
#include <stdlib.h>
typedef struct
{
  int *v;
  int position;
} vetor;

void merge(int *v, int left, int right1, int right2)
{
  int *vet1 = malloc(sizeof(int) * (right2 - left + 1));
  int k = 0;
  int i = left;
  int j = right1 + 1;

  while (i <= right1 && j <= right2)
  {
    if (v[i] <= v[j])
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

void mergeSortRecursive(int *v, int left, int right)
{
  if (left >= right)
    return;
  int meio = (right + left) / 2;
  mergeSortRecursive(v, left, meio);
  mergeSortRecursive(v, meio + 1, right);
  merge(v, left, meio, right);
}
int bb(int *v, int n, int x)
{
  int e = -1;
  int d = n;
  while (e < d - 1)
  {
    int m = (e + d) / 2;
    if (v[m] < x)
      e = m;
    else
      d = m;
  }
  return d;
}

int main()
{
  int n, m, proc;
  vetor new;
  scanf("%d %d", &n, &m);
  new.v = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &new.v[i]);
    new.position = i;
  }
  mergeSortRecursive(new.v, 0, n);
  for (int i = 0; i < m; i++)
  {
    scanf("%d", &proc);
    printf("%d", bb(new.v, n, proc));
  }

  return 0;
}
