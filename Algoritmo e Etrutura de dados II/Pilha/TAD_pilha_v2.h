#define TAM_PILHA 5
#include <stdio.h>

void inicializapilha(pilha *p)
{
    int x;
    for (x = 0; x < TAM_PILHA; x++)
        p->memoria[x] = -1;
}
int pilhacheia(pilha *p)
{
    int x;
    for (x = 0; x < TAM_PILHA; x++)
        if (p->memoria[x] == -1)
            return (0);
    return (1);
}

int pilhavazia(pilha *p)
{
    if (p->memoria[0] == -1)
        return (1);
    return (0);
}
void empilha(pilha *p, int elemento)
{
    int x = 0;
    if (!pilhacheia(p))
    {
        do
        {
            if (p->memoria[x] == -1)
            {
                p->memoria[x] = elemento;
                break;
            }
            x++;
        } while (x < TAM_PILHA);
    }
}
void desempilha(pilha *p)
{
    int x = TAM_PILHA - 1;
    if (!pilhavazia(p))
    {
        do
        {
            if (p->memoria[x] != -1)
            {
                p->memoria[x] = -1;
                break;
            }
            x--;
        } while (x >= 0);
    }
}
int topopilha(pilha *p)
{
    int x, elemento_topo = -1;
    if (!pilhavazia(p))
    {
        for (x = 0; x < TAM_PILHA; x++)
            if (p->memoria[x] != -1)
                elemento_topo = p->memoria[x];
    }
    return (elemento_topo);
}
int tamanhopilha(pilha *p)
{
    int x, y;
    for (x = y = 0; x < TAM_PILHA; x++)
        if (p->memoria[x] != -1)
            y++;
    return (y);
}

void replicapilha(pilha *a, pilha *b)
{
    int i;
    inicializapilha(b);
    for (i = 0; i < TAM_PILHA; i++)
    {
        if (a->memoria[i] != -1)
        {
            b->memoria[i] = a->memoria[i];
        }
    }
}
void replicapilhaauxiliar(pilha *a, pilha *b)
{
    pilha temp;
    int elemento;
    inicializapilha(&temp);
    inicializapilha(b);
    while (pilhavazia(a) != 0)
    {
        elemento = topopilha(a);
        empilha(&temp, elemento);
        desempilha(a);
    }
    while (pilhavazia(&temp) != 0)
    {
        elemento = topopilha(&temp);
        desempilha(&temp);
        empilha(a, elemento);
        empilha(b, elemento);
    }
}