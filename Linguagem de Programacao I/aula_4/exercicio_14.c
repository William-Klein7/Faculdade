#include <stdio.h>
int main()
// Faca um programa que leia um vetor de 30 posições.
// A seguir mostre esse vetor de forma inversa (da ultima posicao para a primeira)

{
	int vet[30], i;
	for (i = 0; i < 30; i++)
	{
		scanf("%d", &vet[i]);
	}

	for (i = 0; i < 30; i++)
	{
		printf("\n%d", vet[i]);
	}

	for (i = 29; i > -1; i--)
	{
		printf("%d ", vet[i]);
	}
	return 0;
}