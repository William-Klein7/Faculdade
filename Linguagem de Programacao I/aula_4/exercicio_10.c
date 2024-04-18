#include <stdio.h>
#define tam 5
int main()
// Escrever um programa que lê uma matriz M 5x5 e cria 2 vetores SL e SC que contenham,
// respectivamente, as somas das linhas e das colunas de M.
// Escrever a matriz e os vetores criados

{
	int matriz[tam][tam], SC[tam] = {0}, SL[tam] = {0};

	printf("Digite os elementos da matriz 5x5:\n");
	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			scanf("%d", &matriz[i][j]);
		}
	}

	for (int i = 0; i < tam; i++)
	{
		for (int j = 0; j < tam; j++)
		{
			SL[i] += matriz[i][j];
			SC[j] += matriz[i][j];
		}
	}

	printf("Soma das linhas:\n");
	for (int i = 0; i < tam; i++)
	{
		printf("%d ", SL[i]);
	}
	printf("\n");

	printf("Soma das colunas:\n");
	for (int i = 0; i < tam; i++)
	{
		printf("%d ", SC[i]);
	}
	printf("\n");

	return 0;
}