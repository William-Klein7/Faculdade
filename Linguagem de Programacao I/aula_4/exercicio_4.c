#include <stdio.h>
int main()
// Seja R uma matriz  4 X5. Determine o maior elemento de R e a sua posição.

{
	int mat[4][5], l, c, maior, posl, posc;
	for (l = 0; l < 4; l++)
	{
		for (c = 0; c < 5; c++)
		{
			scanf("%d", &mat[l][c]);
		}
	}

	maior = mat[0][0];
	posl = 0;
	posc = 0;

	for (l = 0; l < 4; l++)
	{
		for (c = 0; c < 5; c++)
		{
			if (mat[l][c] > maior)
			{
				maior = mat[l][c];
				posl = l;
				posc = c;
			}
		}
	}

	printf("Maior elemento: %d\n", maior);
	printf("Posicao: Linha %d, Coluna %d", posl, posc);
	
	return 0;
}