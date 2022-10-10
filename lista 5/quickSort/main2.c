#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

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
  int *v, n;
  scanf("%d", &n);
  v = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &v[i]);
  }
  quicksort(v, 0, n - 1);
  for (int i = 0; i < n; i++)
  {
    printf("%d ", v[i]);
  }
  return 0;
}
