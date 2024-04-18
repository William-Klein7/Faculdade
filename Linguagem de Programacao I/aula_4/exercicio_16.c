#include <stdio.h>
int main()
// Faca um programa que leia dois vetores de 10 posicoes.
// A seguir crie um terceiro vetor que armazene a multiplicacao das posicoes pares
// do primeiro pelas posicoes impares do segundo. Mostre o vetor resultante.

{
	int vet1[10], vet2[10], result[5];

	printf("escreva os valores do primeiro vetor: \n");
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &vet1[i]);
	}

	printf("escreva os valores do segundo vetor: \n");
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &vet2[i]);
	}

	printf("resultado do terceiro vetor: ");
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			result[i] = vet1[i] * vet2[i + 1];
			printf("%d ", result[i]);
		}
	}

	return 0;
}