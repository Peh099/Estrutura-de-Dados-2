#include <stdio.h>
#include <stdlib.h>
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
  int *vet;
  scanf("%d %d", &n, &m);
  vet = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &vet[i]);
  }
  for (int i = 0; i < m; i++)
  {
    scanf("%d", &proc);
    printf("%d\n", bb(vet, n, proc));
  }
  free(vet);
  return 0;
}