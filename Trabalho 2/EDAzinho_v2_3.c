#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 262139

/*
	sondagem L' C' P
	dominacao P
*/
struct itens
{
  int pontuacao;
  int row;
  int column;
  int chave;
  int status;
};

struct hash
{
  int qtd, TABLE_SIZE;
  struct itens **item; /* um ponteiro cria o vetor o outro armazena o endereço */
};

struct fila_prioridade
{
  int qtd;
  struct itens dados[MAX];
};

typedef struct hash Hash;
typedef struct fila_prioridade FilaPrio;
typedef struct itens Matriz;

Hash *criaHash(int TABLE_SIZE);
void liberaHash(Hash *hash_table);
int insereHash_enderAberto(Hash *hash_table, struct itens item);
int buscaHash_enderAberto(Hash *hash_table, int valor, struct itens *item);
int sondagemLinear(int pos, int i, int TABLE_SIZE);
int calculaDivisao(int chave, int TABLE_SIZE);
int sondagemLinear(int pos, int i, int TABLE_SIZE);
int calculaDivisao(int chave, int TABLE_SIZE);
FilaPrio *cria_FilaPrio();
void libera_FilaPrio(FilaPrio *fp);
int estaCheia_FilaPrio(FilaPrio *fp);
int estaVazia_FilaPrio(FilaPrio *fp);
int insere_FilaPrio(FilaPrio *fp, Matriz matriz, int prio);
void promoverElemento(FilaPrio *fp, int filho);
Matriz *remove_FilaPrio(FilaPrio *fp);
void rebaixarElemento(FilaPrio *fp, int pai);
int consulta_FilaPrio(FilaPrio *fp);

int main(void)
{
  int row, column, p_i, t_loop; /* start game data */
  int i, j, l, k, x, y, alavanca = 0, alavanca2 = 0;
  int table[100];
  Hash *hash_table;
  struct itens item;
  FilaPrio *fp;
  int TABLE_SIZE = 1000, EDAzinhos = 0, areas_dominadas = 0, cont_turnos = 0;
  char command[256];

  hash_table = criaHash(TABLE_SIZE);
  fp = cria_FilaPrio();

  /* valores iniciais */
  scanf("%d %d %d %d", &row, &column, &p_i, &t_loop); /* lÃª dados iniciais*/
                                                      /* matriz[row][column].row = row;
  matriz[row][column].column = column;
  matriz[row][column].pontuacao = p_i;
  matriz[row][column].sondado = 1;
  insere_FilaPrio(fp, matriz[row][column], matriz[row][column].pontuacao);
  item.row = row;
  item.column = column;
  item.pontuacao = p_i;
  item.chave = row;
  item.status = 3;*/

  x = insereHash_enderAberto(hash_table, item);
  table[alavanca2++] = item.chave;

  for (k = (row - 1); k <= (row + 1); k++)
  {
    for (l = (column - 1); l <= (column); l++)
    {
      if (k != row && l != column)
      {
        item.row = k;
        item.column = l;
        item.pontuacao = 0;
        item.chave = k * l;
        item.status = 1;

        x = insereHash_enderAberto(hash_table, item);
        table[alavanca2++] = item.chave;
        //printf("X:%d||chave:%d ", x, item.chave);
        //printf("%d %d\n", k, l);
        //printf("\n");
      }
    }
    //cont_dominadas++;
    //printf("%d\n", cont_dominadas);
  }
  //printf("k:%d\n", k);

  if (x = buscaHash_enderAberto(hash_table, item.chave, &item))
  {
    //printf("Passou no primeiro!");
    row = item.row;
    column = item.column;
    //item.chave = 200;
    item.status = 2;
    //printf("linha:%d\n", item.row);
    //printf("coluna:%d\n", item.column);
    //printf("chave do item buscado:%d\n", item.chave);
  }

  printf("sondar %d %d\n", row, column);
  hash_table->item[row * column]->status = 2;

  printf("fimturno\n");
  fflush(stdout);

  /* turno 1 */
  scanf("%s %d %d %d", command, &row, &column, &p_i); /* sondar */
                                                      /* matriz[row][column].row = row;
  matriz[row][column].column = column;
  matriz[row][column].pontuacao = p_i;
  matriz[row][column].sondado = 1;*/

  //insere_FilaPrio(fp, matriz[row][column], matriz[row][column].pontuacao);
  //printf("linha:%d Colunas%d\n",row,column);
  printf("dominar %d %d\n", row, column);

  for (k = (row - 1); k <= (row + 1); k++)
  {
    for (l = (column - 1); l <= (column); l++)
    {
      if (k != row && l != column)
      {
        item.row = k;
        item.column = l;
        item.pontuacao = 0;
        item.chave = k * l;
        item.status = 1;

        x = insereHash_enderAberto(hash_table, item);
        table[alavanca2++] = item.chave;
        //printf("X:%d||chave:%d ", x, item.chave);
        //printf("%d %d\n", k, l);
        //printf("\n");
      }
    }
    //cont_dominadas++;
    //printf("%d\n", cont_dominadas);
  }

  if (x = buscaHash_enderAberto(hash_table, item.chave, &item))
  {
    row = item.row;
    column = item.column;
    //item.chave = 2;
    item.status = 2;
    //printf("linha:%d\n", item.row);
    //printf("coluna:%d\n", item.column);
  }

  printf("sondar %d %d\n", row, column);

  hash_table->item[row * column]->status = 2;

  printf("fimturno\n");

  fflush(stdout);

  while ((t_loop - 2) > cont_turnos)
  {
    /* turno 1 em diante */
    for (j = 0; j < EDAzinhos + 2; j++)
    {
      scanf("%s", command); /* dominar*/

      if (strcmp(command, "dominacao") == 0)
      {
        scanf("%d", &p_i);
      }

      else if (strcmp(command, "sondagem") == 0)
        scanf("%d %d %d", &row, &column, &p_i);

      else
        break;
    }

    printf("dominar %d %d\n", row, column);
    hash_table->item[row * column]->status = 3;
    //printf("row:%d coluna:%d\n", row, column);

    for (k = (row - 1); k <= (row + 1); k++)
    {
      //printf("k:%d \n", k);
      for (l = (column - 1); l <= (column); l++)
      {
        if (k != row && l != column)
        {
          item.row = k;
          item.column = l;
          item.chave = k * l;
          item.status = 1;

          x = insereHash_enderAberto(hash_table, item);
          table[alavanca2++] = item.chave;
          //printf("X:%d||chave:%d ", x, item.chave);
          //printf("%d %d\n", k, l);
          //printf("\n");
        }
      }
      //cont_dominadas++;
      //printf("%d\n", cont_dominadas);
    }
    //printf("k:%d\n", k);
    for (i = 0; i < EDAzinhos + 2; i++)
    {
      if (i == 0)
      {
        if (x = buscaHash_enderAberto(hash_table, item.chave, &item))
        {
          row = item.row;
          column = item.column;
          //item.chave = 2;
          item.status = 2;
          //printf("linha:%d\n", item.row);
          //printf("coluna:%d\n", item.column);
        }
      }
      else
      {
        x = buscaHash_enderAberto(hash_table, item.chave, &item);
        if (item.status == 1)
        {
          row = item.row;
          column = item.column;
          //item.chave = 2;
          item.status = 2;
          //printf("linha:%d\n", item.row);
          //printf("coluna:%d\n", item.column);
        }
        else

        {
          for (int n = 0; n < alavanca2; n++)
          {
            x = buscaHash_enderAberto(hash_table, table[n], &item);
            if (item.status == 1)
            {
              //printf("resultado X:%d\n",x);
              row = item.row;
              column = item.column;
              //row=hash_table->item[row-2]->row;
              //column=hash_table->item[row-2]->column;
              break;
            }
          }
        }
      }

      printf("sondar %d %d\n", row, column);
      hash_table->item[row * column]->status = 2;
    }

    EDAzinhos++;
    //t_loop--;
    areas_dominadas++;
    cont_turnos++;

    printf("fimturno\n");

    fflush(stdout);
  }

  liberaHash(hash_table);

  return 0;
}

/* Hash Table */
Hash *criaHash(int TABLE_SIZE)
{
  Hash *hash_table = (Hash *)malloc(sizeof(Hash));

  if (hash_table != NULL)
  {
    int i;
    hash_table->TABLE_SIZE = TABLE_SIZE;
    hash_table->item = (struct itens **)malloc(TABLE_SIZE * sizeof(struct itens *));

    if (hash_table->item == NULL)
    {
      free(hash_table);
      return NULL;
    }

    hash_table->qtd = 0;
    for (i = 0; i < hash_table->TABLE_SIZE; i++)
      hash_table->item[i] = NULL;
  }

  return hash_table;
}

void liberaHash(Hash *hash_table)
{
  if (hash_table != NULL)
  {
    int i;
    for (i = 0; i < hash_table->TABLE_SIZE; i++)
    {
      if (hash_table->item[i] != NULL)
        free(hash_table->item[i]);
    }
    free(hash_table->item);
    free(hash_table);
  }
}

int insereHash_enderAberto(Hash *hash_table, struct itens item)
{
  if (hash_table == NULL || hash_table->qtd == hash_table->TABLE_SIZE)
    return 0;

  int chave = item.chave;
  int i, pos, new_pos;
  pos = calculaDivisao(chave, hash_table->TABLE_SIZE);

  for (i = 0; i < hash_table->TABLE_SIZE; i++)
  {
    new_pos = sondagemLinear(pos, i, hash_table->TABLE_SIZE);
    if (hash_table->item[new_pos] == NULL)
    {
      struct itens *novo;
      novo = (struct itens *)malloc(sizeof(struct itens));

      if (novo == NULL)
        return 0;

      *novo = item;
      hash_table->item[new_pos] = novo;
      hash_table->qtd++;
      return 1;
    }
  }

  return 0;
}

int buscaHash_enderAberto(Hash *hash_table, int valor, struct itens *item)
{
  if (hash_table == NULL)
  {
    printf("aq 1\n");
    return 0;
  }
  int i, pos, new_pos;
  pos = calculaDivisao(valor, hash_table->TABLE_SIZE);

  for (i = 0; i < hash_table->TABLE_SIZE; i++)
  {
    new_pos = sondagemLinear(pos, i, hash_table->TABLE_SIZE);

    if (hash_table->item[new_pos] == NULL)
    {
      printf("aq 2\n");
      return 0;
    }

    if (hash_table->item[new_pos]->chave == valor)
    {
      *item = *(hash_table->item[new_pos]);
      return 1;
    }
  }
  printf("aq 3\n");
  return 0;
}

int sondagemLinear(int pos, int i, int TABLE_SIZE)
{
  return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}

int calculaDivisao(int chave, int TABLE_SIZE)
{
  return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

/* Priority Queue */
FilaPrio *cria_FilaPrio()
{
  FilaPrio *fp;

  fp = (FilaPrio *)malloc(sizeof(struct fila_prioridade));
  if (fp != NULL)
    fp->qtd = 0;
  return fp;
}

void libera_FilaPrio(FilaPrio *fp)
{
  free(fp);
}

int estaCheia_FilaPrio(FilaPrio *fp)
{
  if (fp == NULL)
    return -1;
  return (fp->qtd == MAX);
}

int estaVazia_FilaPrio(FilaPrio *fp)
{
  if (fp == NULL)
    return -1;
  return (fp->qtd == 0);
}

int insere_FilaPrio(FilaPrio *fp, Matriz matriz, int prio)
{
  if (fp == NULL)
    return 0;

  if (estaCheia_FilaPrio(fp))
    return 0;

  fp->dados[fp->qtd] = matriz;
  promoverElemento(fp, fp->qtd);
  fp->qtd++;
  return 1;
}

void promoverElemento(FilaPrio *fp, int filho)
{
  int pai;
  struct itens temp;
  pai = (filho - 1) / 2;

  while (filho > 0 && fp->dados[pai].pontuacao <= fp->dados[filho].pontuacao)
  {
    temp = fp->dados[filho];
    fp->dados[filho] = fp->dados[pai];
    fp->dados[pai] = temp;

    filho = pai;
    pai = (filho - 1) / 2;
  }
}

Matriz *remove_FilaPrio(FilaPrio *fp)
{
  if (fp == NULL)
    return NULL;

  if (estaVazia_FilaPrio(fp))
    return NULL;

  Matriz *temp;
  *temp = fp->dados[fp->qtd];
  fp->qtd--;
  fp->dados[0] = fp->dados[fp->qtd];
  rebaixarElemento(fp, 0);
  return temp;
}

void rebaixarElemento(FilaPrio *fp, int pai)
{
  struct itens temp;
  int filho = 2 * pai + 1;

  while (filho < fp->qtd)
  {
    /* Pai tem dois filhos? Quem é o maio? */
    if (filho < fp->qtd - 1)
    {
      if (fp->dados[filho].pontuacao < fp->dados[filho + 1].pontuacao)
        filho++;
    }

    /* Pai >= filho? terminar processo */
    if (fp->dados[pai].pontuacao >= fp->dados[filho].pontuacao)
      break;

    /* Trocar pai e filho de lugar e calcular novo filho*/
    temp = fp->dados[filho];
    fp->dados[filho] = fp->dados[pai];
    fp->dados[pai] = temp;

    pai = filho;
    filho = 2 * pai + 1;
  }
}

int consulta_FilaPrio(FilaPrio *fp)
{
  if (fp == NULL)
    return 0;

  if (estaVazia_FilaPrio(fp))
    return 0;

  return fp->dados[fp->qtd - 1].pontuacao;
}