#include <stdio.h>
int main()
// Escreva um programa que imprima na tela o fatorial de um programa recebido
// Ex:   5! = 5 x 4 x 3 x 2 x 1
// Ex:   0! = 1 (fatorial de zero é 1)

{
	int num, soma = 1;

	scanf("%d", &num);

	if (num == 0)
	{
		printf("fatorial de zero é 1");
	}
	else
	{
		if (num < 0)
		{
			for (int i = num; i < -1; i++)
			{
				soma *= i;
			}
		}
		else
		{
			for (int i = num; i > 1; i--)
			{
				soma *= i;
			}
		}
	}

	printf("O fatorial de %d e: %d", num, soma);

	return 0;
}