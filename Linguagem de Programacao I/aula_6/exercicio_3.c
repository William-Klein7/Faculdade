#include <stdio.h>
int main()
// Faça um algoritmo que leia um nº inteiro.
// Crie um ponteiro apontando para essa variavel e utilizando ele
// mostre uma mensagem indicando se o conteudo apontado pelo ponteiro f
// (valor lido) é par ou ímpar e se é positivo ou negativo.

{
	int x;

	scanf("%d", &x);
	int *px = &x;

	if (*px < 0)
	{
		if (*px % 2 != 0)
		{
			printf("valor negativo e impar");
		}
		else
		{
			printf("valor negativo e par");
		}
	}else{
		if (*px % 2 != 0)
		{
			printf("valor positivo e impar");
		}
		else
		{
			printf("valor positivo e par");
		}
	}

	return 0;
}