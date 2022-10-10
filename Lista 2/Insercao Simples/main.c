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

void insercaosimples(Item *v, int l, int r)
{
  for (int i = l + 1; i <= r; i++)
    for (int j = i; j > l; j--)
      cmpexch(v[j - 1], v[j]);
}

int main()
{
  int v[1000], j = 0, i = 0;
  while (scanf("%d", &j) != EOF)
  {
    v[i] = j;
    i++;
  }

  insercaosimples(v, 0, i - 1);
  for (int k = 0; k < i; k++)
  {
    printf("%d ", v[k]);
  }
  return 0;
}