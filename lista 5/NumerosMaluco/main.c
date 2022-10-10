#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int bb(int v[], int key, int Tam)
{
  int left = 0;
  int right = Tam - 1;
  int mid;
  while (left <= right)
  {
    mid = (left + right) / 2;
    if (key == v[mid])
      return mid;
    if (key < v[mid])
      right = mid - 1;
    else
      left = mid + 1;
  }
  return -1;
}

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

void quicksort(int *v, int l, int r)
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
  quicksort(v, l, j - 1);
  quicksort(v, j + 1, r);
}

int main()
{
  int N;
  int *vet;
  int temp;
  int *vet2;
  int j = 0, cont = 0;
  scanf("%d", &N);
  vet = (int *)malloc(N * sizeof(int));
  vet2 = (int *)malloc((N * 2) * sizeof(int));
  for (int i = 0; i < N; i++)
  {
    scanf("%d", &vet[i]);
  }
  quicksort(vet, 0, N - 1);
  temp = N;
  for (int i = 0; i < N; i++)
  {
    if (bb(vet, vet[i], temp) != -1)
    {
      vet[i] = 0;
      temp = temp - 1;
    }
    else
    {
      vet2[cont] = vet[i];
      cont++;
    }
  }

  for (int i = 0; i < N; i++)
  {
    printf("%d ", vet2[i]);
  }
  /*
  if(N%2==0){
    int temp;
    int cont=N;
    for(int i=0,k=0;i<(N/2);i++,k+=2){
    printf("i: %d\n",i);
    temp=vet[k]+vet[k+1];
    if(bb(vet,temp,N-1)==-1){
      vet[cont++]=temp;
    };
    j++;
    }
  }
  quicksort(vet,0,N+j-1);
  //printf("%d",vet[4]);
  for(int k=0,p=0;k<j;k++,p+=4){
      printf("%d\n",vet[p]);
  }
  printf("Elementos: %d",N+j);
  */
  return 0;
}