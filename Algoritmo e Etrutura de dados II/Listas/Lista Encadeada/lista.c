#include <stdio.h>
#include "lista.h"

int main(void)
{
  int opcao, operacao, elemento, no;
  lista l;
  inicializalista(&l);

  do
  {
    printf("========== OPERACOES CONVENCIONAIS SOBRE A LISTA ==============\n");
    printf("Inserir: 1-Inicio  2-Fim   3-No'          12-ExibeNo'DoElemento\n");
    printf("Remover: 4-Inicio  5-Fim   6-No'  7-Lista    13-Inicializar\n");
    printf("Exibir.: 8-Inicio  9-Fim  10-No' 11-Tamanho  14-Inverter\n");
    printf("NAO CONVENCIONAIS: 15-ExibeElementoEmNo's    16-ExibeEstrutura\n");
    printf("\nInforme a sua opcao (0-Sair): ");
    scanf("%d", &opcao);

    if ((opcao > 0 && opcao < 4) && listacheia(&l))
    {
      printf("\nLista Cheia...\n\n");
      continue;
    }

    if ((opcao > 3 && opcao < 16) && listavazia(&l))
    {
      printf("\nLista Vazia...\n\n");
      continue;
    }

    switch (opcao)
    {
    case 1:
    case 2:
    case 3:
      printf("\nInforme o elemento a ser inserido: ");
      scanf("%d", &elemento);
      if (opcao == 1)
        insereiniciolista(&l, elemento);
      else if (opcao == 2)
        inserefimlista(&l, elemento);
      else
      {
        printf("\nInforme o No' no qual o elemento sera' inserido: ");
        scanf("%d", &no);
        inserelista(&l, elemento, no);
      }
      break;
    case 4:
      removeiniciolista(&l);
      break;
    case 5:
      removefimlista(&l);
      break;
    case 6:
      printf("\nInforme o No' a ser removido: ");
      scanf("%d", &no);
      removenolista(&l, no);
      break;
    case 7:
      printf("\nInforme o elemento que sera removido: ");
      scanf("%d", &elemento);
      removelista(&l, elemento);
      break;
    case 8:
      printf("\nElemento do inicio da lista: %d\n", iniciolista(&l));
      break;
    case 9:
      printf("\nElemento do final da lista: %d\n", fimlista(&l));
      break;
    case 10:
      printf("\nInforme o No' do elemento: ");
      scanf("%d", &no);
      printf("\nElemento do %do. No' da lista: %d\n", no, elementolista(&l, no));
      break;
    case 11:
      printf("\nTamanho (em Nos) da Lista: %d\n", tamanholista(&l));
      break;
    case 12:
      printf("\nInforme o Elemento a ser procurado: ");
      scanf("%d", &elemento);
      printf("\n1o.No'encontrado: %d  ", noelementolista(&l, elemento));
      printf("  Numero de Vezes que aparece na lista: %d\n", qtdelementolista(&l, elemento));
      break;
    case 13:
      liberalista(&l);
      break;
    case 14:
      invertelista(&l);
      break;
    case 15:
      printf("\nInforme o Elemento a ser exibido: ");
      scanf("%d", &elemento);
      exibeelementolista(&l, elemento);
      break;
    case 16:
      exibeestruturalista(&l);
      break;
    }
    printf("\n");
  } while (opcao != 0);
  return (0);
}