#include <stdio.h>
#include <stdlib.h>
#define vertex int

static int cnt;
int pre[1000];

typedef struct
{
  int v;
  int w;
} Edge;

struct graph
{
  /* data */
  int v;
  int e;
  int **adj;
};

typedef struct graph *Graph;
/* MAtriz de adjacencia*/
Edge EDGE(int v, int w);
Graph GRAPHInit(int v);
void GRAPHInsertE(Graph G, Edge e);
void GRAPHInsertE(Graph G, Edge e);
void GRAPHRemove(Graph G, Edge e);
int GRAPHEdges(Edge a[], Graph G);
static int **MATRIXint(int r, int c, int val);

int main(void)
{
  printf("pedro");
  return 0;
}

Edge EDGE(int v, int w)
{
  Edge edgezinho;
  edgezinho.v = v;
  edgezinho.w = w;
  return edgezinho;
}

Graph GRAPHInit(int v)
{
  Graph G = malloc(sizeof(*G));
  G->v = v;
  G->e = 0;
  G->adj = MATRIXint(v, v, 0);
}

void GRAPHInsertE(Graph G, Edge e)
{
  int v = e.v, w = e.w;
  if (G->adj[v][w] == 0)
    G->e++;
  G->adj[v][w] = 1;
  G->adj[w][v] = 1;
}

void GRAPHRemove(Graph G, Edge e)
{
  int v = e.v, w = e.w;
  if (G->adj[v][w] == 1)
    G->e--;
  G->adj[v][w] = 0;
  G->adj[w][v] = 0;
}

int GRAPHEdges(Edge a[], Graph G)
{
  int v, w, E = 0;
  for (v = 0; v < G->v; v++)
    for (w = v + 1; w < G->v; w++)
      if (G->adj[v][w] == 1)
        a[E++] = EDGE(v, w);
  return E;
}

static int **MATRIXint(int r, int c, int val)
{
  int **m = malloc(r * sizeof(int *));
  for (vertex i = 0; i < r; ++i)
    m[i] = malloc(c * sizeof(int));
  for (vertex i = 0; i < r; ++i)
    for (vertex j = 0; j < c; ++j)
      m[i][j] = val;
  return m;
}
// busca em profundidade

void dfsR(Graph G, Edge e)
{
  int t, w = e.w;
  pre[w] = cnt++;
  for (t = 0; t < G->v; t++)
    if (G->adj[w][t] != 0)
      if (pre[t] == -1)
        dfsR(G, EDGE(w, t));
}

void GRAPHSearch(Graph G)
{
  int v;
  int conexos = 0;
  cnt = 0;
  for (v = 0; v<G->v; v++)
    pre[v] = -1;
  for (v = 0; v<G->v; v++)
    if (pre[v] == -1)
    {
      dfsR(G, EDGE(v, v));
      conexos++;
    }
}

/*
int main (){
  iniciagraph();
  for(int v=0;v<G->v,v++)
    pre[v]=-1;
  dfsR(G,EDGE(0,0));
}
*/