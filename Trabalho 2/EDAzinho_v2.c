#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#define MAX 262139

/*
	sondagem L' C' P
	dominacao P
*/

struct item
{
	int value;
	int prio;
};

struct hash
{
	int linha, coluna;
	//struct itens **item; /* um ponteiro cria o vetor o outro armazena o endereço */
};

typedef struct hash Hash;

struct fila_prioridade
{
	int qtd;
	struct item dados[MAX];
};

typedef struct fila_prioridade FilaPrio;
//typedef struct hash Hash;

int **hash_init(int TABLE_SIZE);
void liberaHash(int **hash_table, int TABLE_SIZE);
FilaPrio *cria_FilaPrio();
void libera_FilaPrio(FilaPrio *fp);
int estaCheia_FilaPrio(FilaPrio *fp);
int estaVazia_FilaPrio(FilaPrio *fp);
int insere_FilaPrio(FilaPrio *fp, int value, int prio);
void promoverElemento(FilaPrio *fp, int filho);
int remove_FilaPrio(FilaPrio *fp);
void rebaixarElemento(FilaPrio *fp, int pai);
int consulta_FilaPrio(FilaPrio *fp);
//void gera_matriz_6x6(int mat[6][6]);

int main(void)
{
	//int d, p_s, t_score, m, score; /* game score */

	int row, column, p_i, t_loop, contaturno, valor_arbitro; /* start game data */
	int **hash_table;
	FilaPrio *fp;
	int TABLE_SIZE = 262139, EDAzinhos = 1, flag = 1, consulta;
	char command[256];
	//int mat[6][6];

	hash_table = hash_init(TABLE_SIZE);
	fp = cria_FilaPrio();

	scanf("%d %d %d %d", &row, &column, &p_i, &t_loop); /* lê dados iniciais*/
	hash_table[row][column] = 1;

	/* print teste */
	printf("%d %d\n", hash_table[row][column], hash_table[0][0]);
	consulta = consulta_FilaPrio(fp);
	printf("%d\n", consulta);
	//gera_matriz_6x6(mat);
	/* fim print teste */

	insere_FilaPrio(fp, p_i, p_i);

	//printf("sondar %d %d\n", (row + 1), (column + 1));

	while (contaturno < t_loop)
	{
		//scanf("%s", command); /* lê comando */
		if (contaturno == 0)
		{
			printf("sondar %d %d", row + 1, column + 1);
			scanf("%d", &valor_arbitro);
			insere_FilaPrio(fp, valor_arbitro, valor_arbitro);
		}
		else
		{
			if (strcmp(command, "sondar") == 0)
			{
			}

			else if (strcmp(command, "dominar") == 0)
			{
			}
			else
			{
				flag = 1;
				break;
			}
		}
		contaturno++;
		printf("fimturno\n");
	}

	if (flag == 1)
		EDAzinhos = 0;

	liberaHash(hash_table, TABLE_SIZE);

	return 0;
}

/* Hash Table */
int **hash_init(int TABLE_SIZE)
{
	int **hash_table;
	int i;

	hash_table = (int **)malloc(sizeof(int *) * TABLE_SIZE);

	for (i = 0; i < TABLE_SIZE; i++)
		hash_table[i] = (int *)malloc(sizeof(int) * TABLE_SIZE);

	return hash_table;
}

void liberaHash(int **hash_table, int TABLE_SIZE)
{
	int i;

	for (i = 0; i < TABLE_SIZE; i++)
		free(hash_table[i]);

	free(hash_table);
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

int insere_FilaPrio(FilaPrio *fp, int value, int prio)
{
	if (fp == NULL)
		return 0;

	if (estaCheia_FilaPrio(fp))
		return 0;

	fp->dados[fp->qtd].value = value;
	fp->dados[fp->qtd].prio = prio;
	promoverElemento(fp, fp->qtd);
	fp->qtd++;
	return 1;
}

void promoverElemento(FilaPrio *fp, int filho)
{
	int pai;
	struct item temp;
	pai = (filho - 1) / 2;

	while (filho > 0 && fp->dados[pai].prio <= fp->dados[filho].prio)
	{
		temp = fp->dados[filho];
		fp->dados[filho] = fp->dados[pai];
		fp->dados[pai] = temp;

		filho = pai;
		pai = (filho - 1) / 2;
	}
}

int remove_FilaPrio(FilaPrio *fp)
{
	if (fp == NULL)
		return 0;

	if (estaVazia_FilaPrio(fp))
		return 0;

	fp->qtd--;
	fp->dados[0] = fp->dados[fp->qtd];
	rebaixarElemento(fp, 0);
	return 1;
}

void rebaixarElemento(FilaPrio *fp, int pai)
{
	struct item temp;
	int filho = 2 * pai + 1;

	while (filho < fp->qtd)
	{
		/* Pai tem dois filhos? Quem é o maio? */
		if (filho < fp->qtd - 1)
		{
			if (fp->dados[filho].prio < fp->dados[filho + 1].prio)
				filho++;
		}

		/* Pai >= filho? terminar processo */
		if (fp->dados[pai].prio >= fp->dados[filho].prio)
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

	return fp->dados[fp->qtd - 1].value;
}

/*void gera_matriz_6x6(int mat[6][6]){
	   int i, j, numAleatorios;

    srand(time(NULL));

    // gera os números aleatórios e imprime a matriz
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            numAleatorios = (rand() % 99) + 1;
            mat[i][j] = numAleatorios;
            printf("%3d | ", mat[i][j]); // %3d é para usar 3 casas para mostrar o número
        }
        printf("\n");
    }
}*/