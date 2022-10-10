#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertion(int *v, int l, int r)
{
  for (int i = r; i > l; i--)
    if (v[i] < v[i - i])
    {
      int t;
      t = v[i - i];
      v[i - i] = v[i];
      v[i] = t;
    }

  for (int i = l + 2; i <= r; i++)
  {
    int j = i;
    int tmp = v[j];
    while (tmp < v[j - 1])
    {
      v[j] = v[j - 1];
      j--;
    }
    v[j] = tmp;
  }
}

int separa(int *v, int l, int r)
{
  int c = v[r];
  int j = l;
  int t;
  for (int k = l; k < r; k++)
  {
    if (v[k] <= c)
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
  if (r - l <= 32)
    return;

  int t;
  t = v[(l + r) / 2];
  v[(l + r / 2)] = v[r - 1];
  v[r - 1] = t;
  if (v[r - 1] < v[l])
  {
    int t;
    t = v[l];
    v[l] = v[r - 1];
    v[r - 1] = t;
  }
  if (v[r] < v[l])
  {
    int t;
    t = v[l];
    v[l] = v[r];
    v[r] = t;
  }
  if (v[r] < v[r - 1])
  {
    int t;
    t = v[r - 1];
    v[r - 1] = v[r];
    v[r] = t;
  }

  j = separa(v, l + 1, r - 1);
  quicksort(v, l, j - 1);
  quicksort(v, j + 1, r);
}

void qSM3Insertion(int *v, int l, int r)
{
  quicksort(v, l, r);
  insertion(v, l, r);
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
  qSM3Insertion(v, 0, n - 1);
  for (int i = 0; i < n; i++)
  {
    printf("%d ", v[i]);
  }
  printf("\n");
  free(v);
  return 0;
}
