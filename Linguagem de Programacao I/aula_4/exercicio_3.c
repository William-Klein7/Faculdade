#include <stdio.h>
int main()
// Faça um programa que leia uma matriz M [15,15].
// Verifique quais os elementos dela que estão repetidos e quantas vezes eles aparecem.
// Ou seja, escrever cada elemento repetido dizendo quantas vezes ele aparece.

{
	int tam = 5;
	int mat[tam][tam], cont = 0;

	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			scanf("%d", &mat[i][j]);
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
					if (mat[i][j] == mat[k][l])
					{
						cont += 1;
					}
				}
			}
			if (cont != 0 && cont != 1)
			{
				printf("%d se repetio %d\n", mat[i][j], cont-1);
			}
			cont = 0;
		}
	}

	return 0;
}