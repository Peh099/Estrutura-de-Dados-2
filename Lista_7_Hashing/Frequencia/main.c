#include <stdio.h>
#include <stdlib.h>

typedef struct cont_freq
{
  char caracter;
  int frequencia;
} cont_freq;

int separa(cont_freq *v, int l, int r)
{
  int c = v[r].frequencia;
  int j = l;
  int t;
  for (int k = l; k < r; k++)
  {
    if (v[k].frequencia < c)
    {
      t = v[k].frequencia;
      v[k] = v[j];
      v[j].frequencia = t;
      j++;
    }
  }
  t = v[j].frequencia;
  v[j] = v[r];
  v[r].frequencia = t;
  return j;
}

void quicksortM3(cont_freq *v, int l, int r)
{
  int j;
  if (r <= l)
    return;
  if (v[(l + r) / 2].frequencia > v[r].frequencia)
  {
    int t;
    t = v[(l + r) / 2].frequencia;
    v[(l + r) / 2] = v[r];
    v[r].frequencia = t;
  }
  if (v[l].frequencia > v[(l + r) / 2].frequencia)
  {
    int t;
    t = v[l].frequencia;
    v[l] = v[(l + r) / 2];
    v[(l + r) / 2].frequencia = t;
  }
  if (v[r].frequencia > v[(l + r) / 2].frequencia)
  {
    int t;
    t = v[r].frequencia;
    v[r] = v[(l + r) / 2];
    v[(l + r) / 2].frequencia = t;
  }
  j = separa(v, l, r);
  quicksortM3(v, l, j - 1);
  quicksortM3(v, j + 1, r);
}

void iniciador_tabela_hash(cont_freq *tabela_hash, int tamanho)
{
  int i;

  for (i = 0; i < tamanho; i++)
  {
    tabela_hash[i].caracter = 0;
    tabela_hash[i].frequencia = 0;
  }
}

void print_resultado(cont_freq *tabela_hash, int contador, int tamanho)
{
  int i = 0;

  for (i = contador; i < tamanho; i++)
  {
    printf("%c %d\n", tabela_hash[i].caracter, tabela_hash[i].frequencia);
  }
  printf("\n");
}

int main()
{
  cont_freq *tabela_hash;
  int tamanho = 128; //Tamanho da tabela hash
  int contador = 0;
  char carater_informado;
  tabela_hash = (cont_freq *)malloc(sizeof(cont_freq) * tamanho);
  iniciador_tabela_hash(tabela_hash, tamanho);
  while (scanf("%c", &carater_informado) != EOF)
  {
    if (carater_informado != '\n')
    {
      tabela_hash[carater_informado].caracter = carater_informado; //atualiza o respectivo caracter na posicao relativa a tabela ascii
      tabela_hash[carater_informado].frequencia++;
    }
    else
    {
      quicksortM3(tabela_hash, 0, tamanho - 1);
      while (tabela_hash[contador].frequencia == 0)
      {
        contador++;
      }
      for (int j = contador; j < tamanho; j++)
      {
        printf("%d\n", tabela_hash[j].frequencia);
      }
      //print_resultado(tabela_hash, contador, tamanho);
      iniciador_tabela_hash(tabela_hash, tamanho);
      contador = 0;
    }
  }

  return 0;
}