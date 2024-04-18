#include <stdio.h>
#define tam 5
int main()
// De forma similar ao anterior, faca um programa que leia duas matrizes M1[5,5] e M2[5,5]
// e entao armazene em um vetor V os valores que existem em M1 e tambem existem em M2.
// Mostre o vetor V resultante.

{
	int m1[tam][tam], m2[tam][tam], v[25], cont = 0;

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
						v[cont] = m1[i][j];
						cont++;
					}
				}
			}
		}
	}

	printf("Os numeros da primeira matriz que sao iguais a da segunda matriz sao:\n");
	for (int i = 0; i < cont; i++)
	{
		printf("%d ", v[i]);
	}

	return 0;
}