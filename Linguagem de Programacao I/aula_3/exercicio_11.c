#include <stdio.h>

int main()
{
  // Criar um programa que leia 20 valores inteiros e imprima o produto dos ímpares e a soma dos pares

  int num, soma = 0, product = 1;

  for (int i = 0; i < 10; i++)
  {
    if (num >= 0)
    {
      scanf("%d", &num);
      if (num % 2 == 0)
      {
        soma += num;
      }
      else
      {
        product *= num;
      }
    }
  }

  printf("soma dos pares = %d \n Produto dos impares = %d", soma, product);

  return 0;
}