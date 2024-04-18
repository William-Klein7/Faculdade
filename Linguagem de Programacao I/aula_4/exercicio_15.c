#include <stdio.h>
int main()
// Faca um programa que leia uma matriz de 5 x 5 e um vetor de 5 posicoes.
// A seguir mostre quais os valores que existem no vetor e tambem existem na matriz

{
	int tam = 5;
	int m[tam][tam], vet[tam];

	printf("Insira a  matriz:\n");
	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			scanf("%d", &m[i][j]);
		}
	}

	printf("Insira o vetor:\n");
	for (int i = 0; i < tam; i++)
	{
		scanf("%d", &vet[i]);
	}

	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			for (int k = 0; k < tam; k++)
			{
				if (vet[i] == m[j][k])
				{
					printf("%d existe no vetor e tambem existe na matriz\n", vet[i]);
					j = tam;
					k = tam;
				}
			}
		}
	}

	return 0;
}