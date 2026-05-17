#include <stdio.h>
#include <stdlib.h>

#define ERRO_ARVORE -99999

typedef struct noarvore
{
  int chave;
  struct noarvore *esquerdo;
  struct noarvore *direito;
} noarvore, arvore;

void inicializa_arvore(arvore *a)
{
  a->esquerdo = NULL;
  a->direito = NULL;
  a->chave = 0;
}

int isvazia_arvore(arvore *a)
{
  return (a->esquerdo == NULL);
}

noarvore *inserir(noarvore *raiz, int chave)
{
  if (raiz == NULL)
  {
    noarvore *novo = (noarvore *)malloc(sizeof(noarvore));
    novo->chave = chave;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    return novo;
  }
  if (chave < raiz->chave)
    raiz->esquerdo = inserir(raiz->esquerdo, chave);
  else if (chave > raiz->chave)
    raiz->direito = inserir(raiz->direito, chave);
  return raiz;
}

int calcular_grau(noarvore *no)
{
  if (no == NULL)
    return 0;
  int grau = 0;
  if (no->esquerdo)
    grau++;
  if (no->direito)
    grau++;
  return grau;
}

noarvore *buscar(noarvore *raiz, int chave, int profundidade)
{
  if (raiz == NULL || raiz->chave == chave)
  {
    return raiz;
  }
  int grau = calcular_grau(raiz);
  printf("&%p____ &%p_ %d_______ &%p_ %d____ %d\n", raiz, raiz->esquerdo, raiz->chave, raiz->direito, grau, profundidade);

  if (chave < raiz->chave)
    return buscar(raiz->esquerdo, chave, profundidade + 1);
  else
    return buscar(raiz->direito, chave, profundidade + 1);
}

noarvore *remover(noarvore *raiz, int chave)
{
  if (raiz == NULL)
    return NULL;
  if (chave < raiz->chave)
    raiz->esquerdo = remover(raiz->esquerdo, chave);
  else if (chave > raiz->chave)
    raiz->direito = remover(raiz->direito, chave);
  else
  {
    if (calcular_grau(raiz) < 2)
    {
      noarvore *temp = raiz->esquerdo ? raiz->esquerdo : raiz->direito;
      free(raiz);
      return temp;
    }
    else
    {
      noarvore *temp = raiz->direito;
      while (temp->esquerdo != NULL)
      {
        temp = temp->esquerdo;
      }
      raiz->chave = temp->chave;
      raiz->direito = remover(raiz->direito, temp->chave);
    }
  }
  return raiz;
}

int maior_elemento(noarvore *raiz)
{
  if (raiz == NULL)
    return ERRO_ARVORE;
  if (raiz->direito == NULL)
    return raiz->chave;
  return maior_elemento(raiz->direito);
}

int menor_elemento(noarvore *raiz)
{
  if (raiz == NULL)
    return ERRO_ARVORE;
  if (raiz->esquerdo == NULL)
    return raiz->chave;
  return menor_elemento(raiz->esquerdo);
}

void percurso_arvore(noarvore *a, int ordem)
{
  if (a)
  {
    if (ordem == 1)
      printf("%d ", a->chave);
    percurso_arvore(a->esquerdo, ordem);
    if (ordem == 2)
      printf("%d ", a->chave);
    percurso_arvore(a->direito, ordem);
    if (ordem == 3)
      printf("%d ", a->chave);
  }
}

void preordem_arvore(arvore *a)
{
  if (a->esquerdo)
  {
    printf("Pré-ordem: ");
    percurso_arvore(a->esquerdo, 1);
    printf("\n");
  }
  else
  {
    printf("Árvore vazia.\n");
  }
}

void emordem_arvore(arvore *a)
{
  if (a->esquerdo)
  {
    printf("Em ordem: ");
    percurso_arvore(a->esquerdo, 2);
    printf("\n");
  }
  else
  {
    printf("Árvore vazia.\n");
  }
}

void posordem_arvore(arvore *a)
{
  if (a->esquerdo)
  {
    printf("Pós-ordem: ");
    percurso_arvore(a->esquerdo, 3);
    printf("\n");
  }
  else
  {
    printf("Árvore vazia.\n");
  }
}

void liberar_arvore(noarvore *raiz)
{
  if (raiz)
  {
    liberar_arvore(raiz->esquerdo);
    liberar_arvore(raiz->direito);
    free(raiz);
  }
}

int main()
{
  arvore a;
  inicializa_arvore(&a);
  a.esquerdo = NULL;

  int opcao, elemento;
  do
  {
    printf("\n1 - Inserir\n2 - Remover\n3 - Elemento\n4 - Maior elemento\n5 - Menor elemento\n6 - Exibir em Pré-Ordem\n7 - Exibir em Pós-Ordem\n8 - Exibir em Ordem\n0 - Sair\nOpcao: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
      printf("Elemento a ser inserido na arvore: ");
      scanf("%d", &elemento);
      a.esquerdo = inserir(a.esquerdo, elemento);
      break;
    case 2:
      printf("Elemento a ser removido da arvore: ");
      scanf("%d", &elemento);
      a.esquerdo = remover(a.esquerdo, elemento);
      break;
    case 3:
      printf("Listar dados do elemento na arvore: ");
      scanf("%d", &elemento);
      buscar(a.esquerdo, elemento, 0);
      break;
    case 4:
      elemento = maior_elemento(a.esquerdo);
      if (elemento == ERRO_ARVORE)
        printf("Arvore vazia.\n");
      else
        printf("Maior elemento: %d\n", elemento);
      break;
    case 5:
      elemento = menor_elemento(a.esquerdo);
      if (elemento == ERRO_ARVORE)
        printf("Arvore vazia.\n");
      else
        printf("Menor elemento: %d\n", elemento);
      break;
    case 6:
      preordem_arvore(&a);
      break;
    case 7:
      posordem_arvore(&a);
      break;
    case 8:
      emordem_arvore(&a);
      break;
    case 0:
      liberar_arvore(a.esquerdo);
      printf("Encerrando...\n");
      break;
    default:
      printf("Opcao invalida.\n");
    }
  } while (opcao != 0);

  return 0;
}
