#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula
{
  char palavra[27];
  struct celula *prox;
} celula;

celula *enfileira(celula *f, char x[27])
{
  celula *novo = malloc(sizeof(celula));
  novo->prox = f->prox;
  f->prox = novo;
  strcpy(f->palavra, x);
  return novo;
}

celula *criar_lista()
{
  celula *le = malloc(sizeof(celula));
  le->prox = le;
  return le;
}

void imprime_lista(celula *le)
{
  for (celula *elem = le->prox; elem != le; elem = elem->prox)
  {
    printf("%s\n", elem->palavra);
  }
}

int main()
{
  celula *le;
  char palavra[27];
  char vet[100000][27];
  char status;
  int i = 0;
  int c = 0;
  le = criar_lista();
  char ultimaletra;
  int tamanho;

  while (scanf("%s", palavra) != EOF)
  {
    strcpy(vet[c], palavra);
    c++;
  }

  for (int j = 0; j < c; j++, i++)
  {
    f(i > 0)
    {
      tamanho = strlen(vet[j]);
      if (ultimaletra - 32 == vet[j][0])
      {
        strcpy(vet[c], palavra);
        c++;
      }
      else
      {
        le = enfileira(le, palavra);
        ultimaletra = palavra[tamanho - 1];
      }
    }
    else
    {
      tamanho = strlen(palavra);
      ultimaletra = palavra[tamanho - 1];
      le = enfileira(le, palavra);
    }
  }

  char vet1[100][27];
  int cont = 0;
  for (int k = 0; k < c; k++)
  {
    if (ultimaletra - 32 == vet[k][0])
    {
      strcpy(vet1[cont], vet[k]);
      cont++;
    }
    else
    {
      tamanho = strlen(vet[k]);
      ultimaletra = vet[k][tamanho - 1];
      le = enfileira(le, vet[k]);
    }
  }
  for (int k = 0; k < cont; k++)
  {
    if (ultimaletra - 32 == vet1[k][0])
    {
      //strcpy(vet1[cont], vet[k]);
      //cont++;
    }
    else
    {
      le = enfileira(le, vet1[k]);
    }
  }
  imprime_lista(le);
  free(le);
  return 0;
}
