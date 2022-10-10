#include <stdio.h>
#include <stdlib.h>
void merge(int *v, int left, int right1, int right2)
{
  int *vet1 = malloc(sizeof(int) * (right2 - left + 1));
  int k = 0;
  int i = left;
  int j = right1 + 1;

  while (i <= right1 && j <= right2)
  {
    if (v[i] <= v[j])
      vet1[k++] = v[i++];
    else
      vet1[k++] = v[j++];
  }

  while (i <= right1)
    vet1[k++] = v[i++];
  while (j <= right2)
    vet1[k++] = v[j++];
  k = 0;
  for (i = left; i <= right2; i++)
    v[i] = vet1[k++];
  free(vet1);
}
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
void mergeSortRecursive(int *v, int left, int right)
{
  if (left >= right)
    return;
  int meio = (right + left) / 2;
  mergeSortRecursive(v, left, meio);
  mergeSortRecursive(v, meio + 1, right);
  merge(v, left, meio, right);
}

int main()
{
  int n, *v, proc;
  scanf("%d", &n);
  v = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &v[i]);
  }
  mergeSortRecursive(v, 0, n - 1);

  while (scanf("%d", &proc) != EOF)
  {
    if (bb(v, proc, n) == -1)
    {
      printf("nao\n");
    }
    else
    {
      printf("sim\n");
    }
  }
  return 0;
}
