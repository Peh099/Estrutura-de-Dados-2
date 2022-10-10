#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cont_st
{
  char character;
  int count;
} cont_st;

int separa(cont_st *v, int l, int r)
{
  int c = v[r].count;
  int j = l;
  int t;
  for (int k = l; k < r; k++)
  {
    if (v[k].count < c)
    {
      t = v[k].count;
      v[k] = v[j];
      v[j].count = t;
      j++;
    }
  }
  t = v[j].count;
  v[j] = v[r];
  v[r].count = t;
  return j;
}

void quicksortM3(cont_st *v, int l, int r)
{
  int j;
  if (r <= l)
    return;
  if (v[(l + r) / 2].count > v[r].count)
  {
    int t;
    t = v[(l + r) / 2].count;
    v[(l + r) / 2] = v[r];
    v[r].count = t;
  }
  if (v[l].count > v[(l + r) / 2].count)
  {
    int t;
    t = v[l].count;
    v[l] = v[(l + r) / 2];
    v[(l + r) / 2].count = t;
  }
  if (v[r].count > v[(l + r) / 2].count)
  {
    int t;
    t = v[r].count;
    v[r] = v[(l + r) / 2];
    v[(l + r) / 2].count = t;
  }
  j = separa(v, l, r);
  quicksortM3(v, l, j - 1);
  quicksortM3(v, j + 1, r);
}

void resolvelinha()
{
  struct cont_st TH[128];
  memset(TH, 0, sizeof(struct cont_st) * 128);
  char b;
  while (scanf("%c", &b) == 1 && b != '\n')
  {
    TH[b].character = b;
    TH[b].count++;
  }
  quicksortM3(TH, 0, 127);
  int i = 0;
  while (TH[i].count == 0)
    i++;
  while (i < 128)
  {
    printf("%hd %d/n", TH[i].character, TH[i].count);
    i++;
  }
  printf("\n");
}

int main()
{
  struct cont_st TH[128];
  memset(TH, 0, sizeof(struct cont_st) * 128);
  char b;
  while (scanf("%c", &b) == 1 && b != '\n')
  {
    TH[b].character = b;
    TH[b].count++;
  }
  quicksortM3(TH, 0, 127);
  for (int j = 0; j < 127; j++)
  {
    printf("%d \n", TH[j].count);
  }
  int i = 0;
  while (TH[i].count == 0)
    i++;
  while (i < 128)
  {
    //printf("%d %d\n", TH[i].character, TH[i].count);
    i++;
  }
  printf("\n");

  return 0;
}