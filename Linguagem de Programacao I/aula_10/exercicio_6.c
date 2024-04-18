// Faça uma função que aloque dinamicamente uma área de memória para armazenamento de um array de inteiros com tamanho recebido com parâmetro.
// Dentro do main(), solicite ao usuário que informe um tamanho para o array a ser alocado. Invoque a função passando como parâmetro esse tamanho.
// A seguir, peça para o usuário fornecer cada um dos valores do array. Mostre os valores armazenados.

// ** Não esqueça de liberar a memória alocada.
#include <stdio.h>
#include <stdlib.h>

int *alocarArrayInteiros(int tamanho)
{
  int *array = (int *)malloc(tamanho * sizeof(int));

  return array;
}

int main()
{
  int tamanho;

  printf("Informe o tamanho do array: ");
  scanf("%d", &tamanho);

  int *array = alocarArrayInteiros(tamanho);

  for (int i = 0; i < tamanho; i++)
  {
    printf("Informe o valor para a posicao %d: ", i + 1);
    scanf("%d", &array[i]);
  }

  printf("Valores armazenados no array:\n");
  for (int i = 0; i < tamanho; i++)
  {
    printf("%d ", array[i]);
  }
  printf("\n");

  free(array);

  return 0;
}
