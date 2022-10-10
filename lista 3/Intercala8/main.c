#include <stdio.h>
#include <stdlib.h>
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
Item *intercala(Item *a, int la, int ra, Item *b, int lb, int rb)
{
}

int main()
{
  int number[8];
  int *v1;
  for (int i = 0; i < 8; i++)
  {
    scanf("%d", &number[i]);

    while
    //scanf("%d",)
  }
  return 0;
}