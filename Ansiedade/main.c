#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int number = 0, cont, j = 0;
  cont = 0;
  char palavra[3];

  while (scanf("%s", palavra) != EOF)
  {
    for (int i = 0; i < 9; i++)
    {
      scanf("%s", palavra);
      if (strcmp(palavra, "sim") == 0)
      {
        cont++;
      }
      if (cont == 2)
      {
        cont = 3;
        number++;
      }
    }
    cont = 0;
  }
  printf("%d", number);

  return 0;
}