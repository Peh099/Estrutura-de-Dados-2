#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
  int dado;
  struct no *esq, *dir;
} no;

no insert(no *h,int x){
  int v=x;
  if(h==NULLNODE) return new(x,null,null);
}