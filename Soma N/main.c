#include <stdio.h>
#include <stdlib.h>

int main()
{
  int n, prov, fim = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &prov);
    fim += prov;
  }
  printf("%d", fim);

  return 0;
}