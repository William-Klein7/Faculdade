// Faça uma função que aloque dinamicamente uma área de memória para armazenamento de uma variável inteira.
// Dentro do main(), utilize essa função para alocar DOIS inteiros (chame a função duas vezes). Solicite ao
// usuário que informe os valores de cada uma das variáveis e a seguir efetue a soma desses dois valores. Mostre o resultado da soma.
#include <stdio.h>
#include <stdlib.h>

int *alocarInteiro()
{
  int *ptr = (int *)malloc(sizeof(int));

  return ptr;
}

int main()
{
  int *inteiro1, *inteiro2;
  int soma;

  inteiro1 = alocarInteiro();
  printf("Informe o primeiro valor inteiro: ");
  scanf("%d", inteiro1);

  inteiro2 = alocarInteiro();
  printf("Informe o segundo valor inteiro: ");
  scanf("%d", inteiro2);

  soma = *inteiro1 + *inteiro2;

  printf("A soma dos dois valores e: %d\n", soma);

  free(inteiro1);
  free(inteiro2);

  return 0;
}