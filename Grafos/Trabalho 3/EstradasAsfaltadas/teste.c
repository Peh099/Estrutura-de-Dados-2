#include <stdio.h>
#include <stdlib.h>

struct grafo
{
    int qtde_vertices;
    int grauMax;
    int **arestas;
    int *grau;
};

typedef struct grafo Grafo;

Grafo *cria_grafo(int qtde_vertices, int grauMax)
{
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));

    if (grafo != NULL)
    {
        grafo->qtde_vertices = qtde_vertices;
        grafo->arestas = (int **)malloc(qtde_vertices * (sizeof(int *)));
        grafo->grau = (int *)malloc(qtde_vertices * sizeof(int));
        grafo->grauMax = grauMax;
        for (int i = 0; i < qtde_vertices; i++)
            grafo->arestas[i] = (int *)malloc(grauMax * sizeof(int));
    }

    return grafo;
}

int insere_aresta(Grafo *grafo, int src, int dest, int digrafo, float peso)
{
    grafo->arestas[src][grafo->grau[src]] = dest;
    grafo->grau[src]++;

    if (digrafo == 0)
        insere_aresta(grafo, dest, src, 1, peso);
    return 1;
}

int dfs_aux(Grafo *grafo, int ini, int *visitado)
{
    for (int i = 0; i < grafo->qtde_vertices; i++)
        visitado[i] = 0;
}

int dfs(Grafo *grafo, int ini, int *visitado, int contador, int contaGrupo, int *grupo)
{

    visitado[ini] = contador;
    //  printf("grupo ini: %d\n", grupo[ini]);
    grupo[ini] = contaGrupo;
    // printf("grupo ini: %d\n", grupo[ini]);
    // printf("ini:%d\n", ini);
    //  printf("contador= %d, contaGrupo:%d\n", contador, contaGrupo);
    for (int i = 0; i < grafo->grauMax; i++)
    {
        // printf("visitado[ini]=%d,[visitado] %d, ini:%d contador = % d\n ", visitado[ini], visitado[i], ini, contador);

        if (!visitado[grafo->arestas[ini][i]])
            dfs(grafo, grafo->arestas[ini][i], visitado, contador + 1, contaGrupo, grupo);
    }
}

int pesquisa_grafo(Grafo *grafo, int ini, int *visitado, int *grupo, int contaGrupo)
{
    int contador = 1, contaDiferentes = 0;
    dfs_aux(grafo, ini, visitado);

    for (int i = 0; i < grafo->grauMax; i++)
    {
        // printf("[ENTROU PESQUISA] %d, i:%d\n", visitado[i], i);
        if (visitado[i] == 0)
        {
            //  printf("visita eh zero!i:%d\n", i);
            dfs(grafo, i, visitado, contador, contaGrupo, grupo);
            contaDiferentes++;
            contaGrupo++;
        }
    }

    return contaDiferentes;
}
int main(void)
{
    Grafo *grafo;
    int qtde_cidades, digrafo = 0, v = -1, w = -1;
    int contador = 0, i, contaDiferentes;
    int *visitou;
    int *grupo;
    int contaGrupo = 0;
    int joao_esta = 0;
    int grupo_joao = 0;
    int *qtde_grupo;
    int *menor_indice;

    //  printf("Digite a quantidade de cidades existentes:\n");
    scanf("%d", &qtde_cidades);
    // printf("Digite a cidade em que joao esta:\n");
    scanf("%d", &joao_esta);

    if (qtde_cidades == 1)
    {
        printf("Fique em casa\n");
    }
    else
    {

        grafo = cria_grafo(qtde_cidades, qtde_cidades);
        visitou = malloc(sizeof(int) * qtde_cidades);
        grupo = malloc(sizeof(int) * qtde_cidades);

        while (scanf("%d %d", &v, &w) != EOF)
            insere_aresta(grafo, v, w, digrafo, 0);

        if (v == -1)
        {
            printf("Fique em casa\n");
        }
        else
        {

            contaDiferentes = pesquisa_grafo(grafo, 0, visitou, grupo, contaGrupo);

            qtde_grupo = malloc(sizeof(int) * contaDiferentes);
            menor_indice = malloc(sizeof(int) * contaDiferentes);

            //  printf("Grupos:\n");
            int indice = 0;
            for (int i = 0; i < qtde_cidades; i++)
            {
                //   printf("grupo[%d]=%d\n", i, grupo[i]);
                qtde_grupo[grupo[i]]++;
                if (qtde_grupo[grupo[i]] == 1)
                {
                    //    printf("Menor desse grupo %d", i);
                    menor_indice[indice++] = i;
                }
                if (i == joao_esta)
                {
                    grupo_joao = grupo[i];
                }
            }

            // printf("\n\n");

            int maior = 0;
            int maiorGrupo = 0;
            int igual = 0;
            for (int i = 0; i < contaDiferentes; i++)
            {
                //  printf("grupo[%d] possui %d membros\n", i, qtde_grupo[i]);
                if (i == 0)
                {
                    //     printf("entrou no inicial?\n");
                    maior = qtde_grupo[i];
                    maiorGrupo = i;
                }
                else if (qtde_grupo[i] == maior)
                {
                    if (grupo[i] == grupo_joao)
                    {
                        maior = qtde_grupo[i];
                        maiorGrupo = i;
                    }
                    igual++;
                    //   printf("entrou no nao e igual?\n");
                }
                else if (qtde_grupo[i] > maior)
                {
                    maior = qtde_grupo[i];

                    maiorGrupo = i;
                }
            }

            for (int i = 0; i < contaDiferentes; i++)
            {
                //   printf("menor indice:%d\n", menor_indice[i]);
            }

            //   printf("contaGrupos:%d\n", contaDiferentes);
            // printf("maior grupo é o: %d com %d participantes,joao esta:%d\n", maiorGrupo, maior, joao_esta);
            if (maior == 0)
            {
                printf("Fique em casa\n");
            }
            else if (igual > 0)
            {
                // printf("entrou no igual?\n");
                if (maiorGrupo == grupo_joao)
                {
                    printf("Bora pra estrada\n");
                }
                else
                {
                    printf("Vamos para %d\n", menor_indice[maiorGrupo]);
                }
            }

            else if (maiorGrupo == grupo_joao)
            {
                printf("Bora pra estrada\n");
            }
            else if (maiorGrupo == joao_esta && maiorGrupo == 0)
            {
                printf("Fique em casa\n");
            }
            else if (maiorGrupo != joao_esta)
            {
                printf("Vamos para %d\n", menor_indice[maiorGrupo]);
            }
        }
    }

    return 0;
}