#include <stdio.h>
#include <stdlib.h>

typedef struct grafo Grafo;

struct grafo
{
  int eh_ponderado;
  int nro_vertices;
  int grau_max;
  int **arestas;
  float **pesos;
  int *grau;
};

Grafo *cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado)
{
  Grafo *gr = (Grafo *)malloc(sizeof(struct grafo));
  if (gr != NULL)
  {
    int i;
    gr->nro_vertices = nro_vertices;
    gr->grau_max = grau_max;
    gr->eh_ponderado = (eh_ponderado != 0) ? 1 : 0;
    gr->grau = (int *)calloc(nro_vertices, sizeof(int));
    gr->arestas = (int **)malloc(nro_vertices * sizeof(int *));
    for (i = 0; i < nro_vertices; i++)
      gr->arestas[i] = (int *)malloc(grau_max * sizeof(int));
    if (gr->eh_ponderado)
    {
      gr->pesos = (float **)malloc(nro_vertices * sizeof(float *));
      for (i = 0; i < nro_vertices; i++)
        gr->pesos[i] = (float *)malloc(grau_max * sizeof(float));
    }
  }
  return gr;
}

void libera_Grafo(Grafo *gr)
{
  if (gr != NULL)
  {
    int i;
    for (i = 0; i < gr->nro_vertices; i++)
      free(gr->arestas[i]);
    free(gr->arestas);

    if (gr->eh_ponderado)
    {
      for (i = 0; i < gr->nro_vertices; i++)
        free(gr->pesos[i]);
      free(gr->pesos);
    }
    free(gr->grau);
    free(gr);
  }
}

int insereAresta(Grafo *gr, int orig, int dest, int eh_digrafo, float peso)
{
  if (gr == NULL)
    return 0;
  if (orig < 0 || orig >= gr->nro_vertices)
    return 0;
  if (dest < 0 || dest >= gr->nro_vertices)
    return 0;

  gr->arestas[orig][gr->grau[orig]] = dest;
  if (gr->eh_ponderado)
    gr->pesos[orig][gr->grau[orig]] = peso;
  gr->grau[orig]++;

  if (eh_digrafo == 0)
    insereAresta(gr, dest, orig, 1, peso);
  return 1;
}

int removeAresta(Grafo *gr, int orig, int dest, int eh_digrafo)
{
  if (gr == NULL)
    return 0;
  if (orig < 0 || orig >= gr->nro_vertices)
    return 0;
  if (dest < 0 || dest >= gr->nro_vertices)
    return 0;
  int i = 0;
  while (i < gr->grau[orig] && gr->arestas[orig][i] != dest)
    i++;
  if (i == gr->grau[orig])
    return 0;
  gr->grau[orig]--;
  gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
  if (gr->eh_ponderado)
    gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];
  if (eh_digrafo == 0)
    removeAresta(gr, dest, orig, 1);
  return 1;
}

void buscaProfundidade(Grafo *gr, int ini, int *visitado, int cont)
{
  int i;
  visitado[ini] = cont;
  for (i = 0; i < gr->grau[ini]; i++)
  {
    if (!visitado[gr->arestas[ini][i]])
      buscaProfundidade(gr, gr->arestas[ini][i], visitado, cont + 1);
  }
}

void buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado)
{
  int i, cont = 1;
  for (i = 0; i < gr->nro_vertices; i++)
    visitado[i] = 0;
  buscaProfundidade(gr, ini, visitado, cont);
}

void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado, char *visitadoc)
{
  //printf("passou aq\n");
  int i, vert, NV, cont = 1, *fila, IF = 0, FF = 0;
  /*for (i = 0; i < gr->nro_vertices; i++)
    visitado[i] = 0;*/
  NV = gr->nro_vertices;
  fila = (int *)malloc(NV * sizeof(int));
  FF++;
  fila[FF] = ini;
  visitado[ini] = cont;
  while (IF != FF)
  {
    IF = (IF + 1) % NV;
    vert = fila[IF];
    cont++;
    for (i = 0; i < gr->grau[vert]; i++)
    {
      if (cont > 2)
      {
        if (visitadoc[gr->arestas[vert][i]] != 'N')
        {
          visitadoc[gr->arestas[vert][i]] = 'S';
        }
      }
      else
      {
        visitadoc[gr->arestas[vert][i]] = 'N';
      }
      if (!visitado[gr->arestas[vert][i]])
      {
        FF = (FF + 1) % NV;
        fila[FF] = gr->arestas[vert][i];
        visitado[gr->arestas[vert][i]] = cont;
        //printf("cont:%d\n",cont);
      }
    }
  }
  free(fila);
}

int main(void)
{
  int N = 0, M = 0, J = 0;
  int A = 0;
  int indice;
  int number;
  Grafo *gr;
  int eh_digrafo = 0;
  scanf("%d %d %d", &N, &M, &J);
  gr = cria_Grafo(N, N, 0);
  for (int i = 0; i < N; i++)
  {
    scanf("%d ", &A);
    //printf("A:%d\n",A);
    for (int j = 0; j < A; j++)
    {
      scanf("%d", &indice);
      //printf("indice:%d \n",indice);
      insereAresta(gr, i, indice, eh_digrafo, 0);
    }
  }
  int *vis;
  char *visc;
  vis = malloc(sizeof(int) * 2 * N);
  visc = malloc(sizeof(char) * 2 * N);

  for (int k = 0; k < M; k++)
  {
    scanf("%d", &number);
    //printf("%d \n",number);
    visc[number] = 'N';
    buscaLargura_Grafo(gr, number, vis, visc);
  }

  /*for (int i = 0; i < N; i++)
  {
    printf("%c ", visc[i]);
  }*/

  for (int i = 0; i < J; i++)
  {
    scanf("%d", &indice);
    if (visc[indice] == 'S')
    {
      printf("Nao vou estar la\n");
    }
    else if (visc[indice] == 'N')
    {
      printf("Eu vou estar la\n");
    }
    else
    {
      printf("Nao vou estar la\n");
    }
  }
  /*int eh_digrafo = 0;
  Grafo *gr;
  gr = cria_Grafo(5, 5, 0);
  insereAresta(gr, 0, 1, eh_digrafo, 0);
  insereAresta(gr, 1, 3, eh_digrafo, 0);
  insereAresta(gr, 1, 2, eh_digrafo, 0);
  insereAresta(gr, 2, 4, eh_digrafo, 0);
  insereAresta(gr, 3, 0, eh_digrafo, 0);
  insereAresta(gr, 3, 4, eh_digrafo, 0);
  insereAresta(gr, 4, 1, eh_digrafo, 0);
  //insereAresta(gr, 1, 4, eh_digrafo, 0);
  //insereAresta(gr, 4, 2, eh_digrafo, 0);
  int vis[4];

  //buscaProfundidade_Grafo(gr,0,vis);
  buscaLargura_Grafo(gr, 2, vis);

  for (int i = 0; i < 5; i++)
  {
    printf(" %d\n", vis[i]);
  }
  //removeAresta(gr, 0, 1, 0);

  //libera_Grafo(gr);*/

  return 0;
}