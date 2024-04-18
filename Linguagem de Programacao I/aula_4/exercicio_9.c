#include <stdio.h>
int main()
// Dada uma matriz B 5 x 5, determine a linha de B que possui a maior soma de seus elementos.

{
	int mat[5][5], l, c, soma = 0, soma2 = 0, soma3 = 0, soma4 = 0, soma5 = 0;
	for (l = 0; l < 5; l++)
		for (c = 0; c < 5; c++)
		{
			scanf("%d", &mat[l][c]);
		}

	for (l = 0; l < 1; l++)
	{
		for (c = 0; c < 5; c++)
		{
			soma = soma + mat[l][c];
		}
	}

	for (l = 1; l < 2; l++)
	{
		for (c = 0; c < 5; c++)
		{
			soma2 = soma2 + mat[l][c];
		}
	}

	for (l = 2; l < 3; l++)
	{
		for (c = 0; c < 5; c++)
		{
			soma3 = soma3 + mat[l][c];
		}
	}

	for (l = 3; l < 4; l++)
	{
		for (c = 0; c < 5; c++)
		{
			soma4 = soma4 + mat[l][c];
		}
	}

	for (l = 4; l < 5; l++)
	{
		for (c = 0; c < 5; c++)
		{
			soma5 = soma5 + mat[l][c];
		}
	}
	if (soma > soma2 && soma > soma3 && soma > soma4 && soma > soma5)
		printf("Soma da maior linha(1): \n%d\n", soma);
	else
	{
		if (soma2 > soma && soma2 > soma3 && soma2 > soma4 && soma2 > soma5)
			printf("Soma da maior linha(2): %d\n", soma2);
		else
		{
			if (soma3 > soma && soma3 > soma2 && soma3 > soma4 && soma3 > soma5)
				printf("Soma da maior linha(3): %d\n", soma3);
			else
			{
				if (soma4 > soma && soma4 > soma2 && soma4 > soma3 && soma4 > soma5)
					printf("Soma da maior linha(4): %d\n", soma4);
				else
					printf("Soma da maior linha(5): %d\n", soma5);
			}
		}
	}
	return 0;
}