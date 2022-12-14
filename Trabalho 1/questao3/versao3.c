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
    return;
  if (j < p)
    quickselect(v, p, j + 1, r);
  else
    quickselect(v, p, l, j - 1);
}

int main()
{
  int O = 0, Pi = 0, cont = 0, dec = 99;
  int i = 0, j = 0;
  //int v[1000000];
  int v2[101];
  char t = 'f';
  int temp = 0;
  while (scanf("%d %d", &O, &Pi) != EOF)
  {
    //printf("i:%d\n",i);
    //printf("Temp:%d\n",temp);
    //printf("Pi:%d\n",Pi);
    if (O == 1 && i < 99)
    {
      v2[i] = Pi;
      t = 't';
      i++;
    }
    else if (O == 1 && i >= 99)
    {
      t = 't';
      if (Pi < temp)
      {
        // printf("passou aqui\n");
        v2[dec] = Pi;
        dec--;
        temp = v2[dec];
      }
    }
    else if (O == 2)
    {
      if (Pi == i)
      {
        if (t == 't' && i < 99)
        {
          cont++;
          quicksortM3(v2, 0, Pi - 1);
          temp = v2[Pi - 1];
          t = 'f';
        }
        else if (t == 't' && i >= 99)
        {
          cont++;
          quicksortM3(v2, 0, Pi - 1);
          temp = v2[99];
          t = 'f';
          dec = 99;
        }
        //printf("cont:%d\n",cont);
        for (int k = 0; k < Pi; k++)
        {
          if (v2[k] != 0)
            printf("%d ", v2[k]);
        }
        printf("\n");
      }
      else
      {
        if (t == 't' && i < 99)
        {
          cont++;
          //printf("Pi:%d\n",Pi);
          quickselect(v2, Pi - 1, 0, i - 1);
          quicksortM3(v2, 0, Pi - 1);
          temp = v2[Pi - 1];
          t = 'f';
        }
        if (t == 't' && i == 99)
        {
          cont++;
          quickselect(v2, Pi - 1, 0, 99);
          quicksortM3(v2, 0, 99);
          temp = v2[99];
          i++;
          dec = 99;
          //printf("v2Ultimo:%d\n",v2[99]);
        }
        else if (t == 't' && i > 99)
        {
          quicksortM3(v2, 0, 99);
          temp = v2[99];
          dec = 99;
        }
        //printf("cont:%d\n",cont);
        for (int k = 0; k < Pi; k++)
        {
          if (v2[k] != 0)
            printf("%d ", v2[k]);
        }
        printf("\n");
      }
    }
    //printf("i:%d\n",i);
  }
  return 0;
}