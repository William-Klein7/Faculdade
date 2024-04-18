#include <stdio.h>
int main()
// Escreva um programa que leia dois vetores ordenados, v1 e v2 com 10 elementos cada,
// retorne um novo array ordenado contendo os elementos de v1 e v2.
// Exemplo:
// arr1:  [3, 4, 6, 7]
// arr2:  [1, 3, 5, 6, 8, 11, 15]
// var res = uniao(arr1, arr2); // res=[1, 3, 3, 4, 5, 6, 6, 7, 8, 11, 15]

{
	int vet1[10], vet2[10], vetres[20], i, i2 = 0, aux;
	printf("Informe o vetor 1: \n");
	for (i = 0; i < 10; i++)
	{
		scanf("%d", &vet1[i]);
	}
	printf("Informe o vetor 2: \n");
	for (i = 0; i < 10; i++)
	{
		scanf("%d", &vet2[i]);
	}
	for (i = 0; i < 10; i++)
	{
		vetres[i2] = vet1[i];
		i2++;
	}
	for (i = 0; i < 10; i++)
	{
		vetres[i2] = vet2[i];
		i2++;
	}
	for (i = 0; i < 19; i++)
	{
		for (i2 = 0; i2 < 19 - i; i2++)
		{
			if (vetres[i2] > vetres[i2 + 1])
			{
				aux = vetres[i2];
				vetres[i2] = vetres[i2 + 1];
				vetres[i2 + 1] = aux;
			}
		}
	}
	printf("Vetor resultante: \n");
	for (i = 0; i < 20; i++)
	{
		printf("%d ", vetres[i]);
	}
	return 0;
}