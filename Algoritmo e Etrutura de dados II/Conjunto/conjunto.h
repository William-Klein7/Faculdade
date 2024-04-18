#include <stdio.h>

#define tam 50

typedef struct
{
  int elements[tam];
  int sizeCon;
} conjunto;

void inicializar(conjunto *c)
{
  c->sizeCon = 0;
}

void setelemento(conjunto *c, int elemento)
{
  if (c->sizeCon > tam)
  {
    printf("Conjunto nao inicializado.\n");
    return;
  }
  if (c->sizeCon < tam)
  {
    for (int i = 0; i < c->sizeCon; i++)
    {
      if (c->elements[i] == elemento)
      {
        printf("Elemento ja existe no conjunto.\n");
        return;
      }
    }
    c->elements[c->sizeCon++] = elemento;
  }
  else
  {
    printf("O conjunto ja atingiu o tamanho maximo.\n");
  }
}

void removeElemento(conjunto *c, int elemento)
{
  int i, j;
  if (c->sizeCon > tam)
  {
    printf("Conjunto nao inicializado.\n");
    return;
  }
  if (c->sizeCon == 0)
  {
    printf("Este conjunto nao possui nenhum elemento.\n");
    return;
  }
  for (i = 0; i < c->sizeCon; i++)
  {
    if (c->elements[i] == elemento)
    {
      for (j = i; j < c->sizeCon - 1; j++)
      {
        c->elements[j] = c->elements[j + 1];
      }
      c->sizeCon--;
      printf("Elemento %d removido do conjunto.\n", elemento);
      return;
    }
  }
  printf("Elemento %d nao encontrado no conjunto.\n", elemento);
}

void exibirConjunto(conjunto *c)
{
  if (c->sizeCon > tam)
  {
    printf("Conjunto nao inicializado.\n");
    return;
  }
  if (c->sizeCon == 0)
  {
    printf("Este conjunto nao possui nenhum elemento.\n");
    return;
  }
  else
  {
    printf("{ ");
    for (int i = 0; i < c->sizeCon; i++)
    {
      printf("%d ", c->elements[i]);
    }
    printf("}\n");
  }
}

void interseccao(conjunto *c1, conjunto *c2, conjunto *c3)
{
  if (c1->sizeCon > tam)
  {
    printf("1o conjunto nao inicializado.\n");
    return;
  }
  if (c1->sizeCon == 0)
  {
    printf("O 1o conjunto nao possui nenhum elemento.\n");
    return;
  }
  if (c2->sizeCon > tam)
  {
    printf("2o conjunto nao inicializado.\n");
    return;
  }
  if (c2->sizeCon == 0)
  {
    printf("O 2o conjunto nao possui nenhum elemento.\n");
    return;
  }
  inicializar(c3);
  for (int i = 0; i < c1->sizeCon; i++)
  {
    for (int j = 0; j < c2->sizeCon; j++)
    {
      if (c1->elements[i] == c2->elements[j])
      {
        setelemento(c3, c1->elements[i]);
        break;
      }
    }
  }
}