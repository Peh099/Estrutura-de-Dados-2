#include <stdio.h>
#include <stdlib.h>

typedef struct forma_palav
{
  char caracter;
  int codigo;
} forma_palav;

int separa(forma_palav *v, int l, int r)
{
  int c = v[r].codigo;
  int j = l;
  int t;
  for (int k = l; k < r; k++)
  {
    if (v[k].codigo < c)
    {
      t = v[k].codigo;
      v[k] = v[j];
      v[j].codigo = t;
      j++;
    }
  }
  t = v[j].codigo;
  v[j] = v[r];
  v[r].codigo = t;
  return j;
}

void quicksortM3(forma_palav *v, int l, int r)
{
  int j;
  if (r <= l)
    return;
  if (v[(l + r) / 2].codigo > v[r].codigo)
  {
    int t;
    t = v[(l + r) / 2].codigo;
    v[(l + r) / 2] = v[r];
    v[r].codigo = t;
  }
  if (v[l].codigo > v[(l + r) / 2].codigo)
  {
    int t;
    t = v[l].codigo;
    v[l] = v[(l + r) / 2];
    v[(l + r) / 2].codigo = t;
  }
  if (v[r].codigo > v[(l + r) / 2].codigo)
  {
    int t;
    t = v[r].codigo;
    v[r] = v[(l + r) / 2];
    v[(l + r) / 2].codigo = t;
  }
  j = separa(v, l, r);
  quicksortM3(v, l, j - 1);
  quicksortM3(v, j + 1, r);
}

void iniciador_tabela_hash(forma_palav *tabela_hash, int tamanho)
{
  int i;

  for (i = 0; i < tamanho; i++)
  {
    tabela_hash[i].caracter = 0;
    tabela_hash[i].codigo = 0;
  }
}

void print_resultado(forma_palav *tabela_hash, int contador, int tamanho)
{
  int i = 0;

  for (i = contador; i < tamanho; i++)
  {
    printf("%c %d\n", tabela_hash[i].caracter, tabela_hash[i].codigo);
  }
  printf("\n");
}

int main()
{
  forma_palav *tabela_hash;
  int tamanho = 1048576; //Tamanho da tabela hash
  int number;
  int contador = 0;
  int menor = 1048576;
  char carater_informado;
  char c = 'f';
  tabela_hash = (forma_palav *)malloc(sizeof(forma_palav) * tamanho);
  iniciador_tabela_hash(tabela_hash, tamanho);
  int i = 0;
  while (scanf("%d %c", &number, &carater_informado) != EOF)
  {
    while (tabela_hash[i].codigo != 0)
    {
      if (tabela_hash[i].codigo == number)
      {
        c = 't';
      }
      i = (i + 1 % tamanho);  
    }
    if (c = 'f')
    {
      tabela_hash[i].caracter = carater_informado;
      tabela_hash[i].codigo = number;
      printf("%c", tabela_hash[i].caracter);
      
    }
    c = 'f';
  }
    for(int j=0;j<contador;j++){
        if(tabela_hash[j].caracter!=0)
        printf("%c", tabela_hash[j].caracter);
    }
    //printf("%c", tabela_hash[525].caracter);
    //print_resultado(tabela_hash, menor, contador);

    return 0;
  }