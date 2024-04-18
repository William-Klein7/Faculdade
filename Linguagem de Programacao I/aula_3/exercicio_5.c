#include <stdio.h>
int main()
// Escreva um programa que leia de forma repetitiva um dado um número positivo,
// e diga se ele é primo ou não. O programa deve parar quano o usuário digitar o número -1.

{
	int rept, num, comparador = 0;

	do
	{
		 
		if (num <= 1)
		{
			printf("numeros menores ou iguais a 1 nao sao primos");
		}

		for (int i = 2; i * i <= num; i++)
		{
			if (num % i == 0)
			{
				printf("%d nao e um numero primo.\n", num);
				comparador = 1;
			}
		}

		if (comparador == 0)
		{
			printf("%d e um numero primo.\n", num);
		}

		printf("se deseja acabar digite -1 senao digite 1: ");
		scanf("%d", &rept);
		comparador = 0;
		printf("\n");

	} while (rept != -1);

	return 0;
}