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
void selecao(Item *v, int l, int r)
{
  if (l == r)
    return;

  int min = l;
  for (int j = l + 1; j <= r; j++)
    if (less(v[j], v[min]))
      min = j;
  exch(v[min], v[l]);
  selecao(v, l + 1, r);
}
int main()
{
  int v[1000], j = 0, i = 0;
  while (scanf("%d", &j) != EOF)
  {
    v[i] = j;
    i++;
  }
  selecao(v, 0, i - 1);
  for (int k = 0; k < i; k++)
  {
    printf("%d ", v[k]);
  }
  return 0;
}