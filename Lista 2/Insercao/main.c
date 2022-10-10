#include <stdio.h>
#include <stdlib.h>
typedef int Item;
#define less(A, B) ((A) < (B))
#define lesseq(A, B) ((A) <= (B))
#define exch(A, B) \
  {                \
    Item t;        \
    t = A;         \
    A = B;         \
    B = t;         \
  }
#define cmpexch(A, B) \
  {                   \
    if (less(B, A))   \
      exch(A, B);     \
  }

void insercao(Item *v, int l, int r)
{
  for (int i = r; i > l; i--)
    cmpexch(v[i - i], v[i]);

  for (int i = l + 2; i <= r; i++)
  {
    int j = i;
    Item tmp = v[j];
    while (less(tmp, v[j - 1]))
    {
      v[j] = v[j - 1];
      j--;
    }
    v[j] = tmp;
  }
}

int main()
{
  int v[50000], j = 0, i = 0;
  while (scanf("%d", &j) != EOF)
  {
    v[i] = j;
    i++;
  }

  insercao(v, 0, i - 1);
  for (int k = 0; k < i; k++)
  {
    printf("%d ", v[k]);
  }
  return 0;
}