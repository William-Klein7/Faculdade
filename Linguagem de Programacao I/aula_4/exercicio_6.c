#include <stdio.h>
int main()
// Faca um programa que leia duas matrizes M1[5,5] e M2[5,5]  e entao armazene em um vetor V
// os valores que existem em M1 e nao existem em M2. Mostre o vetor V resultante.

{
	int tam = 2;
	int m1[tam][tam], m2[tam][tam], vet[25];
	int cont = 0, aux = 0;

	printf("Insira a primeira matriz:\n");
	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			scanf("%d", &m1[i][j]);
		}
	}

	printf("Insira a segunda matriz:\n");
	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			scanf("%d", &m2[i][j]);
		}
	}

	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			for (int k = 0; k < tam; k++)
			{
				for (int l = 0; l < tam; l++)
				{
					if (m1[i][j] == m2[k][l])
					{
						cont++;
					}
				}
			}
			if (cont == 0)
			{
				vet[aux] = m1[i][j];
				aux++;
			}
			cont = 0;
		}
	}

	printf("Os valores que existem em M1 e nao existem em M2 sao: ");
	for (int i = 0; i < aux; i++)
	{
		printf("%d ", vet[i]);
	}

	return 0;
}