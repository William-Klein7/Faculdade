#define TAM_PILHA 5
#include <stdio.h>

void inicializapilha(pilha *p)
{
    p->topo = 0;
}
int pilhacheia(pilha *p)
{
    if (p->topo != TAM_PILHA)
        return (0);
    return (1);
}
int pilhavazia(pilha *p)
{
    if (p->topo != 0)
        return (0);
    return (1);
}
void empilha(pilha *p, int elemento)
{
    if (!pilhacheia(p))
    {
        p->memoria[p->topo] = elemento;
        p->topo++;
    }
}
void desempilha(pilha *p)
{
    if (!pilhavazia(p))
        p->topo--;
}
int topopilha(pilha *p)
{
    if (!pilhavazia(p))
        return (p->memoria[p->topo - 1]);
    return (-1);
}
int tamanhopilha(pilha *p)
{
    return (p->topo);
}

void replicapilha(pilha *a, pilha *b)
{
    int i;
    inicializapilha(b);
    for (i = 0; i < a->topo; i++)
    {
        b->memoria[i] = a->memoria[i];
    }
    b->topo = a->topo;
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
