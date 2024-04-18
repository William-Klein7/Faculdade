#include <stdio.h>
int main()
// Escreva um programa que leia uma matriz quadrada P[3,3] e determine se esta matriz
// quadrada é uma matriz permutação.Uma matriz quadrada designa-se matriz permutação se os
// seus elementos são apenas zeros e uns e se em cada linha e coluna existe um único valor 1.
// A matriz
// P =
// | 1 0 0 |
// | 0 1 0 |
// | 0 0 1 |  é uma matriz permutação

{
	int tam = 3;
	int p[tam][tam], cont = 0;

	printf("Insira a matriz:\n");
	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			scanf("%d", &p[i][j]);
		}
	}

	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			if (p[i][j] == 0 || p[i][j] == 1)
			{
				if (i == j && p[i][j] == 0)
				{
					cont++;
				}
				if (i != j && p[i][j] == 1)
				{
					cont++;
				}
			}
			else
			{
				cont++;
			}
		}
	}

	if (cont == 0)
	{
		printf("E uma matriz de permutacao");
	}
	else
	{
		printf("Nao e uma matriz de permutacao");
	}

	return 0;
}