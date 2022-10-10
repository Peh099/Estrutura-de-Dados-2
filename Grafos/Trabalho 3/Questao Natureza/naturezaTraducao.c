#include <stdio.h>
#include <stdlib.h>

struct grafo
{
  int eh_ponderado;
  int nro_vertices;
  int grau_max;
  int **arestas;
  float **pesos;
  int *grau;
};

typedef struct grafo Grafo;

Grafo *cria_grafo(int nro_vertices, int grau_max, int eh_ponderado);
void libera_grafo(Grafo *grafo);
int insere_aresta(Grafo *grafo, int orig, int dest, int eh_digrafo, float peso);
int remove_aresta(Grafo *grafo, int orig, int dest, int eh_digrafo);
int dfs(Grafo *grafo, int ini, int *visitado, int cont, int qtd, int indice);
int dfs_aux(Grafo *grafo, int ini, int *visitado);
int pesquisa_grafo(Grafo *grafo, int ini, int *visitado, int J);

int main(void)
{
  Grafo *grafo;
  int V, J, eh_digrafo = 0, v, w;
  int cont = 0, i, conexos;
  int *vis;

  scanf("%d %d", &V, &J);

  grafo = cria_grafo(V, V, 0);
  vis = malloc(sizeof(int) * V);

  while (scanf("%d %d", &v, &w) != EOF)
    insere_aresta(grafo, v, w, eh_digrafo, 0);

  //printf("J: %d\n", J);

  conexos = pesquisa_grafo(grafo, 0, vis, J);

  //printf("%d\n", conexos);

  libera_grafo(grafo);

  return 0;
}

Grafo *cria_grafo(int nro_vertices, int grau_max, int eh_ponderado)
{
  Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));

  if (grafo != NULL)
  {
    int i;
    grafo->nro_vertices = nro_vertices;
    grafo->grau_max = grau_max;
    grafo->eh_ponderado = (eh_ponderado != 0) ? 1 : 0;
    grafo->grau = (int *)malloc(nro_vertices * sizeof(int));
    grafo->arestas = (int **)malloc(nro_vertices * (sizeof(int *)));

    for (i = 0; i < nro_vertices; i++)
      grafo->arestas[i] = (int *)malloc(grau_max * sizeof(int));
    if (grafo->eh_ponderado)
    {
      grafo->pesos = (float **)malloc(nro_vertices * sizeof(float *));
      for (i = 0; i < nro_vertices; i++)
        grafo->pesos[i] = (float *)malloc(grau_max * sizeof(float));
    }
  }

  return grafo;
}

void libera_grafo(Grafo *grafo)
{
  if (grafo != NULL)
  {
    int i;
    for (i = 0; i < grafo->nro_vertices; i++)
      free(grafo->arestas[i]);
    free(grafo->arestas);

    if (grafo->eh_ponderado)
    {
      for (i = 0; i < grafo->nro_vertices; i++)
        free(grafo->pesos[i]);
      free(grafo->pesos);
    }

    free(grafo->grau);
    free(grafo);
  }
}

int insere_aresta(Grafo *grafo, int orig, int dest, int eh_digrafo, float peso)
{
  /* verify if is a existent vertex */
  if (grafo == NULL)
    return 0;

  if (orig < 0 || orig >= grafo->nro_vertices)
    return 0;

  if (dest < 0 || dest >= grafo->nro_vertices)
    return 0;

  grafo->arestas[orig][grafo->grau[orig]] = dest;

  if (grafo->eh_ponderado)
    grafo->pesos[orig][grafo->grau[orig]] = peso;

  grafo->grau[orig]++;

  if (eh_digrafo == 0)                         /* não dígrafo */
    insere_aresta(grafo, dest, orig, 1, peso); /* insert another vertex if it's a digraph */

  return 1;
}

int remove_aresta(Grafo *grafo, int orig, int dest, int eh_digrafo)
{
  if (grafo == NULL)
    return 0;

  if (orig < 0 || orig >= grafo->nro_vertices)
    return 0;

  if (dest < 0 || dest >= grafo->nro_vertices)
    return 0;

  int i;

  while (i < grafo->grau[orig] && grafo->arestas[orig][i] != dest)
    i++;

  if (i == grafo->grau[orig])
    return 0;

  grafo->grau[orig]--;
  grafo->arestas[orig][i] = grafo->arestas[orig][grafo->grau[orig]];

  if (grafo->eh_ponderado)
    grafo->pesos[orig][i] = grafo->pesos[orig][grafo->grau[orig]];

  if (eh_digrafo == 0)
    remove_aresta(grafo, dest, orig, 1);

  return 1;
}

int dfs_aux(Grafo *grafo, int ini, int *visitado)
{
  int i;
  //int cont = 1;

  for (i = 0; i < grafo->nro_vertices; i++)
    visitado[i] = 0;
}

int flag;
int passou = 0;
int passou2 = 0;

int dfs(Grafo *grafo, int ini, int *visitado, int cont, int qtd, int indice)
{
  int i;
  visitado[ini] = cont;
  if (qtd < 6)
    qtd++;
  //printf("visitado:%d\n",visitado[ini]);
  flag = qtd;

  for (i = 0; i < grafo->grau_max; i++)
  {
    if (!visitado[grafo->arestas[ini][i]])
    {
      dfs(grafo, grafo->arestas[ini][i], visitado, cont + 1, qtd++, indice);
      //printf("grafo:%d\n",grafo->arestas[ini][i]);
      if ((grafo->arestas[ini][i]) == indice)
      {
        passou = 1;
      }
    }
  }

  return flag;
}

int pesquisa_grafo(Grafo *grafo, int ini, int *visitado, int J)
{
  int i, cont = 1, conexos = 0, qtd = 0, j;
  int maior_componente = 0, menor_indice = 0, empate = 0;
  int esta_la = 0, encontrou = 0;

  dfs_aux(grafo, ini, visitado); /* marca todos os vértices como não visitado */

  for (i = 0; i < grafo->grau_max; i++)
  {
    if (i == J)
      encontrou = 1;
    else
      encontrou = 0;

    //printf("%d\n",visitado[i]);

    if (visitado[i] == 0)
    {
      //printf("encontrou:%d\n",encontrou);
      flag = 0;
      passou = 0;
      qtd = 0;
      cont = 1;
      //printf("i:%d\n", i);
      qtd = dfs(grafo, i, visitado, cont, qtd, J);
      //printf("passou:%d\n",passou);
      /*if(qtd==6){
          printf("igual 6\n");
      }*/
      //printf("qtd:%d\n",qtd);
      //printf("maior:%d\n",maior_componente);
      if (qtd == 4)
      {
        // printf("%d\n",i);
      }
      if (qtd > maior_componente)
      {
        // printf("maior:%d\n",maior_componente);
        //printf("i:%d\n", i);
        maior_componente = qtd;
        //printf("maior:%d\n",maior_componente);
        menor_indice = i;
        //printf("qtd maior componente: %d\n", maior_componente);
        //printf("menor indice: %d\n", menor_indice);
        if (encontrou == 1)
          esta_la = 1;

        else
          esta_la = 0;

        if (passou == 1)
        {
          passou2 = 1;
          //printf("passou!");
        }

        empate = 0;
      }
      else if (qtd == maior_componente)
      {
        if (passou == 1)
        {
          empate = 1;
          passou2 = 1;
        }
        if (maior_componente == 1)
        {
          passou2 = 1;
        }
      }
      if (qtd == maior_componente && passou2 == 1)
      {
        empate = 1;
        //printf("deu empate!");
      }
      conexos++;
    }

    //printf("encontrou %d\n", encontrou);
    //printf("esta_la %d\n", esta_la);
  }
  //printf("passou2:%d\n",passou2);
  //printf("maior componente:%d\n",maior_componente);
  //printf("menor:%d\n",menor_indice);
  if (empate == 1 && passou2 == 0)
  {
    printf("Bora pra estrada\n");
  }
  if (esta_la == 1 || passou2 == 1)
    if (maior_componente == 1)
      printf("Fique em casa\n");
    else
      printf("Bora pra estrada\n");

  else if (empate != 1)
  {
    printf("Vamos para %d\n", menor_indice);
  }

  return conexos;
}