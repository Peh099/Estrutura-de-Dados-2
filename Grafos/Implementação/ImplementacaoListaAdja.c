#include <stdio.h>
#include <stdlib.h>
//Lista de adjacencia
static int cnt;
int pre[1000];

typedef struct node *link;

struct node
{
  int v;
  link next;
};

struct graph
{
  int v, e;
  link *adj;
};

typedef struct
{
  int v;
  int w;
} Edge;

typedef struct graph *Graph;

Edge EDGE(int v, int w);
link new (int v, link next);
Graph GRAPHInit(int V);
void GRAPHInsert(Graph G, Edge e);
int GRAPHEdges(Edge a[], Graph G);
void tela_azul();
void GRAPHSearch(Graph G);
void dfsR(Graph G, Edge e);

int main(void)
{
  Graph grafo;
  grafo = GRAPHInit(3);
  Edge a[3];
  int tamanho = 1;
  Edge vertice;
  vertice = EDGE(0, 1);
  GRAPHInsert(grafo, vertice);
  vertice = EDGE(0, 2);
  GRAPHInsert(grafo, vertice);
  vertice = EDGE(1, 2);
  GRAPHInsert(grafo, vertice);
  tamanho = GRAPHEdges(a, grafo);

  vertice = EDGE(1, 2);
  printf("grafo v:%d\n", grafo->v);
  for (int v = 0; v < grafo->v; v++)
    pre[v] = -1;
  dfsR(grafo, vertice);
  printf("tamanho:%d\n", tamanho);
  for (int i = 0; i < 3; i++)
  {
    printf("%d %d\n", a[i].v, a[i].w);
  }

  for (int i = 0; i < 3; i++)
  {
    printf("%d\n", pre[i]);
  }

  return 0;
}

Edge EDGE(int v, int w)
{
  Edge edgezinho;
  edgezinho.v = v;
  edgezinho.w = w;
  return edgezinho;
}

link new (int v, link next)
{
  link x = malloc(sizeof *x);
  if (x == NULL)
    exit(1);
  x->v = v;
  x->next = next;
  return x;
}

Graph GRAPHInit(int V)
{
  int v;
  Graph G = malloc(sizeof(*G));
  G->v = V;
  G->e = 0;
  G->adj = malloc(V * sizeof(link));
  for (v = 0; v < V; v++)
    G->adj[v] = NULL;
  return G;
}

void GRAPHInsert(Graph G, Edge e)
{
  int v = e.v, w = e.w;
  G->adj[v] = new (w, G->adj[v]);
  G->adj[w] = new (v, G->adj[w]);
  G->e++;
}

int GRAPHEdges(Edge a[], Graph G)
{
  int v, E = 0;
  link t;
  for (v = 0; v < G->v; v++)
    for (t = G->adj[v]; t != NULL; t = t->next)
      if (v < t->v)
        a[E++] = EDGE(v, t->v);
  return E;
}

//Busca em profundidade
void dfsR(Graph G, Edge e)
{
  int t, w = e.w;
  link l;
  pre[w] = cnt++;
  for (l = G->adj[w]; l != NULL; l = l->next)
  {
    t = l->v;
    if (pre[t] == -1)
      dfsR(G, EDGE(w, t));
  }
}

void GRAPHSearch(Graph G)
{
  int v;
  int conexos = 0;
  cnt = 0;
  for (v = 0; v < G->v; v++)
    pre[v] = -1;
  for (v = 0; v < G->v; v++)
    if (pre[v] == -1)
    {
      dfsR(G, EDGE(v, v));
      conexos++;
    }
}
/*
void bfs(Graph G, Edge e)
{
  int v, w;
  Queueput(e);
  pre[e.w] =
}*/
