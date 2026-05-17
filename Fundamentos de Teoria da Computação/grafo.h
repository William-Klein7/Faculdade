#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF INT_MAX

typedef struct
{
    int name;
} vertice;

typedef struct
{
    int inicio, fim;
} aresta;

typedef struct
{
    int tamanho;
    vertice *vertices;
    aresta *arestas;
    int numArestas;
} grafo;

void inicializaGrafo(grafo *g, int tamanho);
void adicionaAresta(grafo *g, int inicio, int fim);
void removerAresta(grafo *g, int inicio, int fim);
void adicionarVertice(grafo *g);
void removerVertice(grafo *g, int vert);
void verticesIsolados(grafo *g);
void grauMaxMin(grafo *g, int qtdv, int *vet);
void busca(grafo *g, int visitados[], int v);
int grauVertice(grafo *g, int v);
int saoVizinhos(grafo *g, int v1, int v2);
int ehCiclo(grafo *g, int qtdv);
int ehGrafoSimples(grafo *g);
int ehConexo(grafo *g);
void mostrarGrafo(grafo *g);
void dijkstra(grafo *g);
void todosVizinhos(grafo *g, int v1, int *vet);

void inicializaGrafo(grafo *g, int tamanho)
{
    g->tamanho = tamanho;
    g->vertices = (vertice *)malloc(tamanho * sizeof(vertice));
    g->arestas = NULL;
    g->numArestas = 0;

    for (int i = 0; i < tamanho; i++)
    {
        g->vertices[i].name = i;
    }
}

void adicionaAresta(grafo *g, int inicio, int fim)
{
    if (g->vertices[inicio].name == -1 || g->vertices[fim].name == -1)
        return;

    g->arestas = (aresta *)realloc(g->arestas, (g->numArestas + 1) * sizeof(aresta));
    g->arestas[g->numArestas].inicio = g->vertices[inicio].name;
    g->arestas[g->numArestas].fim = g->vertices[fim].name;
    g->numArestas++;
}

int grauVertice(grafo *g, int v)
{
    if (g->vertices[v].name == -1)
        return 0;

    int qtd = 0;
    for (int i = 0; i < g->numArestas; i++)
    {
        if (v == g->arestas[i].inicio || v == g->arestas[i].fim)
        {
            qtd++;
        }
    }
    return qtd;
}

void grauMaxMin(grafo *g, int qtdv, int *vet)
{
    vet[0] = 0;
    vet[1] = 20000;

    for (int i = 0; i < qtdv; i++)
    {
        if (g->vertices[i].name == -1)
            continue;

        int qtd = grauVertice(g, i);

        if (vet[0] < qtd)
            vet[0] = qtd;
        if (vet[1] > qtd)
            vet[1] = qtd;
    }
}

int saoVizinhos(grafo *g, int v1, int v2)
{
    if (g->vertices[v1].name == -1 || g->vertices[v2].name == -1)
        return 0;

    for (int i = 0; i < g->numArestas; i++)
    {
        if ((v1 == g->arestas[i].inicio && v2 == g->arestas[i].fim) || (v2 == g->arestas[i].inicio && v1 == g->arestas[i].fim))
        {
            return 1;
        }
    }
    return 0;
}

int ehCiclo(grafo *g, int qtdv)
{
    int *graus = (int *)calloc(qtdv, sizeof(int));
    int verticesValidos = 0;

    for (int i = 0; i < g->tamanho; i++)
        if (g->vertices[i].name != -1)
            verticesValidos++;

    if (g->numArestas != verticesValidos)
    {
        free(graus);
        return 0;
    }

    for (int i = 0; i < g->numArestas; i++)
    {
        graus[g->arestas[i].inicio]++;
        graus[g->arestas[i].fim]++;
    }

    for (int i = 0; i < qtdv; i++)
    {
        if (g->vertices[i].name == -1)
            continue;
        if (graus[i] != 2)
        {
            free(graus);
            return 0;
        }
    }

    free(graus);
    return 1;
}

int ehGrafoSimples(grafo *g)
{
    for (int j = 0; j < g->numArestas; j++)
    {
        if (g->arestas[j].inicio == g->arestas[j].fim)
        {
            return 0;
        }
    }

    for (int i = 0; i < g->numArestas; i++)
    {
        for (int j = i + 1; j < g->numArestas; j++)
        {
            if ((g->arestas[i].inicio == g->arestas[j].inicio &&
                 g->arestas[i].fim == g->arestas[j].fim) ||
                (g->arestas[i].inicio == g->arestas[j].fim &&
                 g->arestas[i].fim == g->arestas[j].inicio))
            {
                return 0;
            }
        }
    }

    return 1;
}

void busca(grafo *g, int visitados[], int v)
{
    if (g->vertices[v].name == -1)
        return;

    visitados[v] = 1;

    for (int i = 0; i < g->numArestas; i++)
    {
        int inicio = g->arestas[i].inicio;
        int fim = g->arestas[i].fim;

        if (inicio == v && !visitados[fim] && g->vertices[fim].name != -1)
            busca(g, visitados, fim);
        else if (fim == v && !visitados[inicio] && g->vertices[inicio].name != -1)
            busca(g, visitados, inicio);
    }
}

int ehConexo(grafo *g)
{
    int *visitados = (int *)calloc(g->tamanho, sizeof(int));

    int origem = -1;
    for (int i = 0; i < g->tamanho; i++)
    {
        if (g->vertices[i].name != -1)
        {
            origem = i;
            break;
        }
    }

    if (origem == -1)
        return 0;

    busca(g, visitados, origem);

    for (int i = 0; i < g->tamanho; i++)
    {
        if (g->vertices[i].name != -1 && !visitados[i])
        {
            free(visitados);
            return 0;
        }
    }

    free(visitados);
    return 1;
}

void verticesIsolados(grafo *g)
{
    int *graus = (int *)calloc(g->tamanho, sizeof(int));

    for (int i = 0; i < g->numArestas; i++)
    {
        graus[g->arestas[i].inicio]++;
        graus[g->arestas[i].fim]++;
    }

    int isolado = 0;
    for (int i = 0; i < g->tamanho; i++)
    {
        if (g->vertices[i].name != -1 && graus[i] == 0)
        {
            printf("Vertice isolado: %d\n", i);
            isolado = 1;
        }
    }

    if (!isolado)
    {
        printf("Nao ha vertices isolados.\n");
    }

    free(graus);
}

void todosVizinhos(grafo *g, int v1, int *vet)
{
    int count = 0;
    for (int i = 0; i < g->numArestas; i++)
    {
        if (v1 == g->arestas[i].inicio)
        {
            vet[count++] = g->arestas[i].fim;
        }
        else if (v1 == g->arestas[i].fim)
        {
            vet[count++] = g->arestas[i].inicio;
        }
    }
}

void mostrarGrafo(grafo *g)
{
    printf("\nLista de Adjacencia do Grafo:\n\n");

    for (int i = 0; i < g->tamanho; i++)
    {
        if (g->vertices[i].name == -1)
            continue;

        printf("%d ->", i);
        for (int j = 0; j < g->tamanho; j++)
        {
            if (g->vertices[j].name == -1)
                continue;

            if (saoVizinhos(g, i, j))
            {
                printf(" %d", j);
            }
        }
        printf("\n");
    }
}

void dijkstra(grafo *g)
{
    int origem;
    printf("\nDigite o vertice de origem\n");
    scanf("%d", &origem);

    if (g->vertices[origem].name == -1)
    {
        printf("Vertice removido!\n");
        return;
    }

    int *distancias = (int *)malloc(g->tamanho * sizeof(int));
    int *visitados = (int *)calloc(g->tamanho, sizeof(int));
    int *predecessores = (int *)malloc(g->tamanho * sizeof(int));

    for (int i = 0; i < g->tamanho; i++)
    {
        distancias[i] = INF;
        predecessores[i] = -1;
    }
    distancias[origem] = 0;

    for (int i = 0; i < g->tamanho; i++)
    {
        int v = -1;

        for (int j = 0; j < g->tamanho; j++)
        {
            if (g->vertices[j].name == -1 || visitados[j])
                continue;
            if (v == -1 || distancias[j] < distancias[v])
                v = j;
        }

        if (v == -1)
            break;

        visitados[v] = 1;

        for (int j = 0; j < g->numArestas; j++)
        {
            int u = g->arestas[j].inicio;
            int w = g->arestas[j].fim;
            int peso = 1;

            if (v == u && !visitados[w] && distancias[v] + peso < distancias[w])
            {
                distancias[w] = distancias[v] + peso;
                predecessores[w] = v;
            }
            if (v == w && !visitados[u] && distancias[v] + peso < distancias[u])
            {
                distancias[u] = distancias[v] + peso;
                predecessores[u] = v;
            }
        }
    }

    printf("Distancias minimas a partir do vertice %d:\n", origem);
    for (int i = 0; i < g->tamanho; i++)
    {
        if (g->vertices[i].name == -1)
            continue;

        if (distancias[i] == INF)
        {
            printf("Vertice %d: Nao alcancavel\n", i);
        }
        else
        {
            printf("Vertice %d: Distancia = %d\n", i, distancias[i]);
        }
    }

    for (int i = 0; i < g->tamanho; i++)
    {
        if (i != origem && distancias[i] != INF && g->vertices[i].name != -1)
        {
            printf("\nCaminho do vertice %d ao vertice %d: ", origem, i);
            int v = i;
            while (v != -1)
            {
                printf("%d ", v);
                v = predecessores[v];
            }
            printf("\n");
        }
    }

    free(distancias);
    free(visitados);
    free(predecessores);
}

void removerAresta(grafo *g, int inicio, int fim)
{
    int novaQtd = 0;
    aresta *novasArestas = (aresta *)malloc(g->numArestas * sizeof(aresta));

    for (int i = 0; i < g->numArestas; i++)
    {
        int iName = g->arestas[i].inicio;
        int fName = g->arestas[i].fim;

        if (!((iName == inicio && fName == fim) || (iName == fim && fName == inicio)))
        {
            novasArestas[novaQtd++] = g->arestas[i];
        }
    }

    free(g->arestas);
    g->arestas = novasArestas;
    g->numArestas = novaQtd;
}

void adicionarVertice(grafo *g)
{
    g->vertices = (vertice *)realloc(g->vertices, (g->tamanho + 1) * sizeof(vertice));
    g->vertices[g->tamanho].name = g->tamanho;
    g->tamanho++;
}

void removerVertice(grafo *g, int vert)
{
    if (g->vertices[vert].name == -1)
        return;

    int novaQtd = 0;
    aresta *novasArestas = (aresta *)malloc(g->numArestas * sizeof(aresta));

    for (int i = 0; i < g->numArestas; i++)
    {
        if (g->arestas[i].inicio != vert && g->arestas[i].fim != vert)
        {
            novasArestas[novaQtd++] = g->arestas[i];
        }
    }

    free(g->arestas);
    g->arestas = novasArestas;
    g->numArestas = novaQtd;

    g->vertices[vert].name = -1;
}
