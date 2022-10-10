#include <stdio.h>
#include <stdlib.h>

int separa(int *v, int l, int r)
{
  int c = v[r];
  int j = l;
  int t;
  for (int k = l; k < r; k++)
  {
    if (v[k] < c)
    {
      t = v[k];
      v[k] = v[j];
      v[j] = t;
      j++;
    }
  }
  t = v[j];
  v[j] = v[r];
  v[r] = t;
  return j;
}

void quicksortM3(int *v, int l, int r)
{
  int j;
  if (r <= l)
    return;
  if (v[(l + r) / 2] > v[r])
  {
    int t;
    t = v[(l + r) / 2];
    v[(l + r) / 2] = v[r];
    v[r] = t;
  }
  if (v[l] > v[(l + r) / 2])
  {
    int t;
    t = v[l];
    v[l] = v[(l + r) / 2];
    v[(l + r) / 2] = t;
  }
  if (v[r] > v[(l + r) / 2])
  {
    int t;
    t = v[r];
    v[r] = v[(l + r) / 2];
    v[(l + r) / 2] = t;
  }
  j = separa(v, l, r);
  quicksortM3(v, l, j - 1);
  quicksortM3(v, j + 1, r);
}

void quickselect(int *v, int p, int l, int r)
{
  int j;
  if (v[(l + r) / 2] > v[r])
  {
    int t;
    t = v[(l + r) / 2];
    v[(l + r) / 2] = v[r];
    v[r] = t;
  }
  if (v[l] > v[(l + r) / 2])
  {
    int t;
    t = v[l];
    v[l] = v[(l + r) / 2];
    v[(l + r) / 2] = t;
  }
  if (v[r] > v[(l + r) / 2])
  {
    int t;
    t = v[r];
    v[r] = v[(l + r) / 2];
    v[(l + r) / 2] = t;
  }
  j = separa(v, l, r);
  //printf("j:%d\n",j);
  if (j == p)
  {
    return;
  }
  if (j < p)
    quickselect(v, p, j + 1, r);
  else
    quickselect(v, p, l, j - 1);
}

int main()
{
  int O = 0, Pi = 0;
  int i = 0, j = 0;
  int v[500000];
  int temp = 0;
  int index = 0;
  char t = 't';
  int maior = 0;
  while (scanf("%d %d", &O, &Pi) != EOF)
  {
    //printf("Pi:%d Temp:%d\n",Pi,temp);
    if (O == 1 && Pi < temp)
    {
      // printf("passou aqui\n ");
      t = 't';
    }
    else if (O == 1 && Pi > temp)
    {
      //printf("nao passou aqui\n ");
    }
    if (O == 1)
    {
      v[i] = Pi;
      i++;
    }
    else
    {
      if (Pi == i)
      {
        if (t == 't')
        {
          quicksortM3(v, 0, Pi - 1);
          temp = v[Pi - 1];
          t = 'f';
          //printf("maiorPrimeiro:%d\n",v[maior-1]);
        }
        for (int k = 0; k < Pi; k++)
        {
          if (v[k] != 0)
            printf("%d ", v[k]);
        }
        printf("\n");
      }
      else
      {
        if (t == 't')
        {
          //printf("Pi:%d\n",Pi);
          quickselect(v, Pi - 1, 0, i - 1);
          quicksortM3(v, 0, Pi - 1);
          temp = v[Pi - 1];
          index = Pi - 1;
          //printf("index:%d\n",index);
          t = 'f';
          //printf("maiorSegundo:%d\n",temp);
        }
        else
        {
          //temp=v[Pi-1];
          quicksortM3(v, index, i - 1);
          //printf("maiorSegundo2:%d\n",temp);
        }
        //j++;
        //printf("j:%d\n",j);
        for (int k = 0; k < Pi; k++)
        {
          if (v[k] != 0)
            printf("%d ", v[k]);
        }
        printf("\n");
      }
    }
  }
  return 0;
}