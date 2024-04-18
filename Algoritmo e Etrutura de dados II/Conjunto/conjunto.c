#include <stdio.h>
#include "conjunto.h"

int main()
{
  conjunto c[10];
  int opcao, elemento, c2, c1, c3;

  while (1)
  {
    printf("Menu Geral - Operacoes Sobre Conjuntos\n1 - Inicializar\n2 - Inserir Membro\n3 - Remover Membro\n4 - Membros\n5 - Interseccao\n6 - Sai\nOperacao: ");
    scanf("%d", &opcao);
    if (opcao == 6)
      break;
    if (opcao == 1)
    {
      while (1)
      {
        printf("Qual conjunto inicializar(Maximo 10): ");
        scanf("%d", &opcao);
        if (opcao <= 0)
          break;
        else if (opcao > 0)
          inicializar(&c[opcao - 1]);
        printf("0 Para retornar ao menu geral\n");
      }
    }
    if (opcao == 2)
    {
      while (1)
      {
        printf("Em qual conjunto inserir (Conjunto ja inicializado de 1 ate 10): ");
        scanf("%d", &opcao);
        if (opcao <= 0)
          break;
        while (opcao > 0)
        {
          printf("Inserindo membro no conjunto %d:", opcao);
          scanf("%d", &elemento);
          if (elemento < 0)
            break;
          else
            setelemento(&c[opcao - 1], elemento);
          printf("-1 para retornar\n");
        }
        printf("0 Para retornar ao menu geral\n");
      }
    }
    if (opcao == 3)
    {
      while (1)
      {
        printf("Em qual conjunto remover (Conjunto ja inicializado de 1 ate 10): ");
        scanf("%d", &opcao);
        if (opcao <= 0)
          break;
        while (opcao > 0)
        {
          printf("Remover membro do conjunto %d:", opcao);
          scanf("%d", &elemento);
          if (elemento < 0)
            break;
          else
            removeElemento(&c[opcao - 1], elemento);
          printf("-1 para retornar\n");
        }
        printf("0 Para retornar ao menu geral\n");
      }
    }
    if (opcao == 4)
    {
      while (1)
      {
        printf("Informe o conjunto a ser listado (Conjunto ja inicializado de 1 ate 10): ");
        scanf("%d", &opcao);
        if (opcao <= 0)
          break;
        else
        {
          printf("Membros do conjunto %d\n", opcao);
          exibirConjunto(&c[opcao - 1]);
        }
        printf("0 Para retornar ao menu geral\n");
      }
    }
    if (opcao == 5)
    {
      printf("Informe o conjunto que vai receber a interseccao: ");
      scanf("%d", &c3);
      printf("Informe o 1o conjunto: ");
      scanf("%d", &c1);
      printf("Informe o 2o conjunto: ");
      scanf("%d", &c2);
      if (c1 > 0 && c2 > 0 && c3 > 0)
      {
        interseccao(&c[c1 - 1], &c[c2 - 1], &c[c3 - 1]);
        printf("Interseccao:\n");
        exibirConjunto(&c[c3 - 1]);
      }
      else
        printf("Endereco de conjunto invalido\n");
    }
    printf("\n");
  }
  printf("Tecle <enter> para continuar...");
  getchar();

  return 0;
}