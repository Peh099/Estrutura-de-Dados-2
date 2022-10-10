#include <stdio.h>
#include <stdlib.h>

int main()
{
  int n;
  while (scanf("%d", &n) != EOF && n != 42)
  {
    printf("%d\n", n);
  }
  return 0;
}