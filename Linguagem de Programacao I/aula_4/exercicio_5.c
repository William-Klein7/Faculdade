#include <stdio.h>
int main()
// Faca um programa que leia uma matriz M[10,5]
// e no final apresente a soma de todos os seus elementos

{
	int mat[10][5];
	int soma = 0, l, c;
	printf("Informe a Matriz: \n");
	for (l = 0; l < 10; l++)
	{
		for (c = 0; c < 5; c++)
		{
			scanf("%d", &mat[l][c]);
			soma = soma + mat[l][c];
		}
	}
	for (l = 0; l < 10; l++)
	{
		for (c = 0; c < 5; c++)
		{
			printf("%d ", mat[l][c]);
		}
		printf("\n");
	}
	printf("Soma: %d", soma);
	return;
}