#include <stdio.h>
int main()
// Escreva um programa que imprime os primos até um número digitado.

{
	int num, comparador = 0;

	printf("digite um numero: ");
	scanf("%d", &num);

	for (int i = 2; i <= num; i++)
	{

		for (int j = 2; j * j <= i; j++)
		{
			if (i % j == 0)
			{
				comparador = 1;
			}
		}

		if (comparador == 0)
		{
			printf("%d e um numero primo\n", i);
		}
		comparador = 0;
	}

	return 0;
}