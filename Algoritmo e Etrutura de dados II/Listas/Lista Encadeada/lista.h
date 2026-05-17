#include <stdio.h>
#include <stdlib.h>

typedef struct nolista
{
  struct nolista *proximo, *anterior;
  int elemento;
} lista, nolista;

void inicializalista(lista *l)
{

  l->proximo = NULL;
  l->anterior = NULL;
}

int listavazia(lista *l)
{
  return (l->proximo == NULL);
}

void insereiniciolista(lista *l, int elemento)
{

  nolista *nlst = (nolista *)malloc(sizeof(nolista));
  nlst->elemento = elemento;
  nlst->anterior = NULL;
  if (listavazia(l))
  {
    l->proximo = nlst;
    l->anterior = nlst;
    nlst->proximo = NULL;
    l->elemento++;
  }
  else
  {
    nlst->proximo = l->proximo;
    l->proximo->anterior = nlst;
    l->proximo = nlst;
    l->elemento++;
  }
}

void inserefimlista(lista *l, int elemento)
{
  nolista *nlst = (nolista *)malloc(sizeof(nolista));
  nlst->elemento = elemento;
  nlst->proximo = NULL;

  if (listavazia(l))
  {
    l->proximo = nlst;
    l->anterior = nlst;
    l->elemento++;
  }
  else
  {
    nlst->anterior = l->anterior;
    l->anterior->proximo = nlst;
    l->anterior = nlst;
    l->elemento++;
  }
}

void inserelista(lista *l, int elemento, int no)
{
  int nr_no = 1, i;
  nolista *temp = l->proximo;
  nolista *nlst = (nolista *)malloc(sizeof(nolista));
  nlst->elemento = elemento;

  for (i = 0; i < no - 1; i++)
  {
    temp = temp->proximo;
  }
  nlst->proximo = temp->proximo;
  temp->proximo = nlst;
  l->elemento++;
}

void removeiniciolista(lista *l)
{

  nolista *segundo = l->proximo;
  if (!listavazia(l))
  {
    l->proximo = segundo->proximo;
    free(segundo);
  }
}
void removefimlista(lista *l)
{
  nolista *ultimo = l->anterior;
  if (!listavazia(l))
  {
    l->anterior = ultimo->anterior;
    l->anterior->proximo = NULL;
    free(ultimo);
  }
}

void removenolista(lista *l, int no)
{
  int i;
  nolista *remover, *temp = l->proximo;

  for (i = 1; i < no - 1; i++)
  {
    temp = temp->proximo;
  }

  remover = temp->proximo;
  temp->proximo = remover->proximo;
  free(remover);
}
void removelista(lista *l, int elemento)
{
}

int iniciolista(lista *l)
{
  return l->proximo->elemento;
}

int fimlista(lista *l)
{
  return l->anterior->elemento;
}
int elementolista(lista *l, int no)
{
  int i;
  nolista *temp = l->proximo;
  for (i = 1; i < no; i++)
    temp = temp->proximo;
  return temp->elemento;
}

int qtdelementolista(lista *l, int elemento)
{
  nolista *temp = l->proximo;
  int cont = 0;

  while (temp->proximo != NULL)
  {

    if (temp->elemento == elemento)
      cont++;

    temp = temp->proximo;
  }

  return cont;
}

void liberalista(lista *l)
{
  nolista *temp = l->proximo;
  nolista *remover;

  while (temp != NULL)
  {
    remover = temp;
    temp = temp->proximo;

    if (temp != NULL)
    {
      temp->anterior = remover->anterior;
    }

    free(remover);
  }

  l->proximo = NULL;
}

void invertelista(lista *l)
{
  nolista *atual = l->proximo;
  nolista *temp = NULL;

  while (atual != NULL)
  {
    temp = atual->anterior;
    atual->anterior = atual->proximo;
    atual->proximo = temp;
    atual = atual->anterior;
  }

  if (temp != NULL)
  {
    temp = temp->anterior;
    l->proximo = temp;
    l->anterior = temp;
  }
}