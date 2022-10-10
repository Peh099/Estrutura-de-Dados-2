#include <stdio.h>
#include <stdlib.h>

int main()
//while(scanf("%15s", words) != EOF)
{
  int number, cont = 0;
  while (scanf("%d", &number) != EOF)
  {
    cont++;
  }
  printf("%d", cont);

  return 0;
}