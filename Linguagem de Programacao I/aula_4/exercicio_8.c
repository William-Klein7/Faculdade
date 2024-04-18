#include <stdio.h>
int main()
// Seja A uma matriz 5 x 5.  Fazer um programa   para:
// - Determinar a soma dos elementos da diagonal principal de A.
// - Colocar os elementos da diagonal principal de A em um vetor S.

{
	int mat[5][5], soma = 0, l, c, vetS[5], i = 0;
	printf("Infomre a Matriz: \n");
	for (l = 0; l < 5; l++)
	{
		for (c = 0; c < 5; c++)
		{
			scanf("%d", &mat[l][c]);
		}
	}
	for (l = 0; l < 5; l++)
	{
		for (c = 0; c < 5; c++)
		{
			if (l == c)
			{
				soma = soma + mat[l][c];
				vetS[i] = mat[l][c];
				i++;
			}
		}
	}
	printf("Soma: %d\n", soma);
	printf("Vetor S: \n");
	for (i = 0; i < 5; i++)
	{
		printf("%d ", vetS[i]);
	}
	return 0;
}