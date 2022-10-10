#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#define MAX 262139

/*
	sondagem L' C' P
	dominacao P
*/
struct mat
{
	int pontuacao;
	int sondado;
	int row;
	int column;
};

struct fila_prioridade
{
	int qtd;
	struct mat dados[MAX];
};

typedef struct fila_prioridade FilaPrio;
typedef struct mat Matriz;

Matriz **hash_init(int TABLE_SIZE);
void liberaHash(Matriz **hash_table, int TABLE_SIZE);
FilaPrio *cria_FilaPrio();
void libera_FilaPrio(FilaPrio *fp);
int estaCheia_FilaPrio(FilaPrio *fp);
int estaVazia_FilaPrio(FilaPrio *fp);
int insere_FilaPrio(FilaPrio *fp, Matriz matriz, int prio);
void promoverElemento(FilaPrio *fp, int filho);
int remove_FilaPrio(FilaPrio *fp);
void rebaixarElemento(FilaPrio *fp, int pai);
int consulta_FilaPrio(FilaPrio *fp);

int main(void)
{
	int row, column, p_i, t_loop; /* start game data */
	//int **hash_table;
	int cont = 0, linha_atual = 0, coluna_atual = 0, pont_atual = 0, pont_total = 0;
	Matriz **matriz;
	FilaPrio *fp;
	char palavra[20];
	int TABLE_SIZE = 262139, EDAzinhos = 1, flag = 1, consulta, areas_dominadas;
	char command[256];

	matriz = hash_init(TABLE_SIZE);
	fp = cria_FilaPrio();

	//printf("%d\n", matriz[row][column].row);

	scanf("%d %d %d %d", &row, &column, &p_i, &t_loop); /* lê dados iniciais*/
	matriz[row][column].row = row;
	matriz[row][column].column = column;
	matriz[row][column].pontuacao = p_i;
	matriz[row][column].sondado = 1;

	//insere_FilaPrio(fp, matriz[row][column], matriz[row][column].pontuacao);

	/* print teste */
	//printf("%d %d\n", hash_table[row][column], hash_table[0][0]);
	//consulta = consulta_FilaPrio(fp);
	//printf("%d\n", consulta);
	/* fim print teste */

	while (cont < t_loop)
	{
		if (cont == 0)
		{
			printf("sondar %d %d\n", (row + 1), (column + 1));
			scanf("%d", &pont_atual);
			//matriz[linha_atual][coluna_atual].row = linha_atual;
			//matriz[linha_atual][coluna_atual].column = coluna_atual;
			//matriz[linha_atual][coluna_atual].pontuacao = pont_atual;
			//matriz[linha_atual][coluna_atual].sondado = 1;

			//insere_FilaPrio(fp, matriz[linha_atual][coluna_atual], matriz[linha_atual][coluna_atual].pontuacao);
			//printf("pontuacaoatual:%d\n", pont_atual);
			pont_total += p_i;
		}
		if (cont == 1)
		{
			
			printf("dominar %d %d\n", (row + 1), (column + 1));
			scanf("%d", &pont_atual);
			EDAzinhos += 1;
			//printf("pontuacaoatual:%d\n", pont_atual);
			pont_total += pont_atual;
		}
		//scanf("%s", command);	/* lê comando */
		/*
		if(strcmp(command, "sondar") == 0)
		{

		}

		else if(strcmp(command, "dominar") == 0)
		{

		}
		else
		{
			flag = 1;
			break;
		}*/
		//printf("pontuacaototal:%d\n", pont_total);

		cont++;
		printf("fimturno\n");

		fflush(stdout);
	}

	/*if (flag == 1)
		EDAzinhos = 0;*/

	//printf("pont_total:%d\n", pont_total);
	//printf("total_EDAZINHOS:%d\n", EDAzinhos);
	//consulta = consulta_FilaPrio(fp);
	//printf("consulta:%d\n", consulta);
	//printf("Matriz:%d\n", matriz[linha_atual][coluna_atual]);

	liberaHash(matriz, TABLE_SIZE);

	return 0;
}

/* Hash Table */
Matriz **hash_init(int TABLE_SIZE)
{
	Matriz **matriz;
	int i;

	matriz = (Matriz **)malloc(sizeof(Matriz *) * TABLE_SIZE);

	for (i = 0; i < TABLE_SIZE; i++)
		matriz[i] = (Matriz *)malloc(sizeof(Matriz) * TABLE_SIZE);

	return matriz;
}

void liberaHash(Matriz **matriz, int TABLE_SIZE)
{
	int i;

	for (i = 0; i < TABLE_SIZE; i++)
		free(matriz[i]);

	free(matriz);
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
	{
		printf("esta vazio no insere");
		return 0;
	}
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
	struct mat temp;
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
	struct mat temp;
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
	{
		printf("vazio1");
		return 0;
	}

	if (estaVazia_FilaPrio(fp))
	{
		printf("vazio2");
		return 0;
	}

	return fp->dados[fp->qtd - 1].pontuacao;
}