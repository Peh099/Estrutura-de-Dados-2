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

void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado)
{
  int i, vert, NV, cont = 1, *fila, IF = 0, FF = 0;
  for (i = 0; i < gr->nro_vertices; i++)
    visitado[i] = 0;
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
      if (!visitado[gr->arestas[vert][i]])
      {
        FF = (FF + 1) % NV;
        fila[FF] = gr->arestas[vert][i];
        visitado[gr->arestas[vert][i]] = cont;
      }
    }
  }
  free(fila);
}

int procuraMenorDistancia(float *dist, int *visitado, int NV)
{
  int i, menor = -1, primeiro = 1;
  for (i = 0; i < NV; i++)
  {
    if (dist[i] >= 0 && visitado[i] == 0)
    {
      if (primeiro)
      {
        menor = i;
        primeiro = 0;
      }
      else
      {
        if (dist[menor] > dist[i])
          menor = i;
      }
    }
  }
  return menor;
}

void menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist)
{
  int i, cont, NV, ind, *visitado, vert;
  cont = NV = gr->nro_vertices;
  visitado = (int *)malloc(NV * sizeof(int));
  for (i = 0; i < NV; i++)
  {
    ant[i] = -1;
    dist[i] = -1;
    visitado[i] = 0;
  }
  dist[ini] = 0;
  while (cont > 0)
  {
    vert = procuraMenorDistancia(dist, visitado, NV);
    //printf("u = %d\n",u);
    if (vert == -1)
      break;

    visitado[vert] = 1;
    cont--;
    for (i = 0; i < gr->grau[vert]; i++)
    {
      ind = gr->arestas[vert][i];
      if (dist[ind] < 0)
      {
        dist[ind] = dist[vert] + 1; //ou peso da aresta
        ant[ind] = vert;
      }
      else
      {
        if (dist[ind] > dist[vert] + 1)
        {
          dist[ind] = dist[vert] + 1; //ou peso da aresta
          ant[ind] = vert;
        }
      }
    }
  }

  free(visitado);
}

int main(void)
{
  int V = 0;
  int v = 0, w = 0, d = 0;
  int t = 0, x = 0;
  int eh_digrafo = 1, status = 0, passou = 0, temp = 0;
  int *ant;
  float *dist;
  scanf("%d", &V);
  Grafo *gr;
  gr = cria_Grafo(V, V, 0);
  ant = malloc(sizeof(int) * V);
  dist = malloc(sizeof(float) * V);
  scanf("%d %d %d", &v, &w, &d);

  while (temp == 0)
  {
    if (d == 1)
    {
      insereAresta(gr, v, w, eh_digrafo, 0);
    }
    if (d == 2)
    {
      insereAresta(gr, v, w, eh_digrafo, 0);
      insereAresta(gr, w, v, eh_digrafo, 0);
    }
    scanf("%d %d %d", &v, &w, &d);
    if (v == 0 && w == 0 & d == 0)
    {
      temp = 1;
    }
  }
  if (v == 0 && w == 0 && d == 0)
  {
    while (scanf("%d %d", &t, &x) != EOF)
    {
      status = 0;
      //passou = 0;
      menorCaminho_Grafo(gr, t, ant, dist);
      //for (int i = 0; i < 7; i++)
      //{
      //printf("%f ", dist[i]);
      //}
      if (dist[x] > 0)
      {
        //printf("Ida\n");
        status = 1;
        passou = 1;
      }
      menorCaminho_Grafo(gr, x, ant, dist);
      if (dist[t] > 0)
      {
        if (status == 1)
        {
          printf("ida e volta\n");
          status = 0;
          passou = 1;
        }
        else
        {
          printf("Volta\n");
          passou = 1;
        }
      }
      else if (status == 1)
      {
        printf("Ida\n");
      }
      if (passou == 0)
      {
        printf("nem ida nem volta!\n");
      }
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