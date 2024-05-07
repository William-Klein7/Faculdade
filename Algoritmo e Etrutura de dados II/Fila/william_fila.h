#include <stdio.h>
#define tam 5

typedef struct
{
  int fila[tam];
  int inicio, count;
  int tamMax;
} fila;

void inicializar(fila *f);
void insere(fila *f, int elemento);
void retira(fila *f);
int inicio(fila *f);
int vazia(fila *f);
int cheia(fila *f);

void inicializar(fila *f)
{
  f->count = 0;
  f->inicio = -1;
  f->tamMax = tam;
}

void insere(fila *f, int elemento)
{
  if (!cheia(f))
  {
    if (f->inicio == -1)
      f->inicio = elemento;
    f->fila[f->count++] = elemento;
  }
  else
    printf("A fila esta cheia\n");
}

void retira(fila *f)
{
  if (!vazia(f))
  {
    if (f->count == 1)
    {
      f->inicio = -1;
      f->count--;
    }
    else
    {
      f->inicio = f->fila[1];
      for (int i = 0; i < f->count; i++)
      {
        f->fila[i - 1] = f->fila[i];
      }
      f->count--;
    }
  }
}

int inicio(fila *f)
{
  if (!vazia(f))
  {
    return f->inicio;
  }
  return -1;
}

int vazia(fila *f)
{
  if (f->inicio == -1 && f->count == 0)
  {
    return 1;
  }
  return 0;
}
int cheia(fila *f)
{
  if (f->count == tam && f->inicio != -1)
  {
    return 1;
  }
  return 0;
}