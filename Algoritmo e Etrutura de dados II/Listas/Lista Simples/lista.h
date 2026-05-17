#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  struct nolista *proximo;
  int elemento;
} nolista, lista;

void inicializalista(lista *l)
{
  l->proximo = NULL;
}

int listavazia(lista *l)
{
  return l->proximo == NULL;
}

int listacheia(lista *l)
{
  return 0;
}

void insereiniciolista(lista *l, int elemento)
{
  nolista *no = (nolista *)malloc(sizeof(nolista));
  no->elemento = elemento;
  no->proximo = l->proximo;
  l->proximo = no;
}

void removeiniciolista(lista *l)
{
  if (!listavazia(l))
  {
    nolista *no = l->proximo;
    l->proximo = no->proximo;
    free(no);
  }
}

int iniciolista(lista *l)
{
  if (!listavazia(l))
  {
    nolista *no = l->proximo;
    return no->elemento;
  }
  else
  {
    printf("Lista vazia \n");
    return -1; // Return an invalid value indicating the list is empty
  }
}

void inserefimlista(lista *l, int elemento)
{
  nolista *no = (nolista *)malloc(sizeof(nolista));
  no->elemento = elemento;
  no->proximo = NULL;
  nolista *temp = l;
  while (temp->proximo != NULL)
  {
    temp = temp->proximo;
  }
  temp->proximo = no;
}

void removefimlista(lista *l)
{
  if (!listavazia(l))
  {
    nolista *noatual = l;
    nolista *anterior = NULL;

    while (noatual->proximo != NULL)
    {
      anterior = noatual;
      noatual = noatual->proximo;
    }

    if (anterior == NULL)
    {
      free(l->proximo);
      l->proximo = NULL;
    }
    else
    {
      anterior->proximo = NULL;
      free(noatual);
    }
  }
}

int fimlista(lista *l)
{
  if (!listavazia(l))
  {
    nolista *noatual = l;
    while (noatual->proximo != NULL)
    {
      noatual = noatual->proximo;
    }
    return noatual->elemento;
  }
  else
  {
    return -1;
  }
}

int tamanholista(lista *l)
{
  nolista *noatual = l;
  int qtd = 0;
  while (noatual->proximo != NULL)
  {
    qtd++;
    noatual = noatual->proximo;
  }
  return qtd;
}

nolista *alocanolista(nolista *proximo, int elemento)
{
  nolista *no = (nolista *)malloc(sizeof(nolista));
  no->elemento = elemento;
  no->proximo = proximo;
  return no;
}

void inserelista(lista *l, int elemento, int no)
{
  nolista *atual = l;
  nolista *anterior = NULL;
  int qtd = 0;

  while (atual != NULL && qtd < no)
  {
    anterior = atual;
    atual = atual->proximo;
    qtd++;
  }
  if (anterior == NULL)
  {
    l = alocanolista(atual, elemento);
  }
  else
  {
    anterior->proximo = alocanolista(atual, elemento);
  }
}

void liberalista(lista *l)
{
  nolista *atual = l->proximo;
  nolista *temp = atual;
  while (atual != NULL)
  {
    atual = atual->proximo;
    free(temp);
  }
  l->proximo = NULL;
}

void removenolista(lista *l, int no)
{
  nolista *atual = l;
  nolista *anterior = NULL;
  int qtd = 0;

  while (atual != NULL && qtd < no)
  {
    anterior = atual;
    atual = atual->proximo;
    qtd++;
  }
  if (anterior == NULL)
  {
    l->proximo = atual->proximo;
  }
  else
  {
    anterior->proximo = atual->proximo;
  }
  free(atual);
}

void removelista(lista *l, int elemento)
{
  nolista *atual = l->proximo;
  nolista *anterior = l;

  while (atual != NULL)
  {
    if (atual->elemento == elemento)
    {
      anterior->proximo = atual->proximo;
      free(atual);
      atual = anterior->proximo;
    }
    else
    {
      anterior = atual;
      atual = atual->proximo;
    }
  }
}

int elementolista(lista *l, int no)
{
  nolista *atual = l;
  int qtd = 0;
  while (atual != NULL && qtd < no)
  {
    atual = atual->proximo;
    qtd++;
  }
  if (atual != NULL)
  {
    return atual->elemento;
  }
  else
  {
    return -1;
  }
}

int qtdelementolista(lista *l, int elemento)
{
  nolista *atual = l->proximo;
  int qtd = 0;
  while (atual != NULL)
  {
    if (atual->elemento == elemento)
    {
      qtd++;
    }
    atual = atual->proximo;
  }
  return qtd;
}

int noelementolista(lista *l, int elemento)
{
  nolista *atual = l->proximo;
  int i = 0;
  while (atual != NULL)
  {
    if (atual->elemento == elemento)
    {
      return i;
    }
    i++;
    atual = atual->proximo;
  }
  return -1;
}

void exibeestruturalista(lista *l)
{
  int nr_no = 1;
  printf("&lista: %6p     &1oNo': %p\n", (void *)l, (void *)l->proximo);
  if (!listavazia(l))
  {
    printf("\nNo' &No'       &Proximo    Elemento");
    printf("\n--- ---------  ----------  --------\n");
    nolista *atual = l->proximo;
    while (atual != NULL)
    {
      printf("%2d      %6p       %6p       %7d\n", nr_no, (void *)atual,
             (void *)atual->proximo, atual->elemento);
      nr_no++;
      atual = atual->proximo;
    }
  }
}

void exibeelementolista(lista *l, int elemento)
{
  nolista *atual = l->proximo;
  int nr_no = 1;
  int found = 0;
  while (atual != NULL)
  {
    if (atual->elemento == elemento)
    {
      if (!found)
      {
        printf("\nNo' &No'       &Proximo    Elemento");
        printf("\n--- ---------  ----------  --------\n");
        found = 1;
      }
      printf("%2d      %6p       %6p       %7d\n", nr_no, (void *)atual,
             (void *)atual->proximo, atual->elemento);
    }
    nr_no++;
    atual = atual->proximo;
  }
  if (!found)
  {
    printf("Elemento %d nao encontrado na lista.\n", elemento);
  }
}

void invertelista(lista *l)
{
  nolista *prev = NULL;
  nolista *current = l->proximo;
  nolista *next = NULL;
  while (current != NULL)
  {
    next = current->proximo;
    current->proximo = prev;
    prev = current;
    current = next;
  }
  l->proximo = prev;
}