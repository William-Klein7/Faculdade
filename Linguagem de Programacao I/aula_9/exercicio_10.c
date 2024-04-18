#include <stdio.h>
void primo(int num)
{
	int aux = 0;
	for (int i = 2; i * i <= num; i++)
	{
		if (num % i == 0)
		{
			aux++;
		}
	}
	if (aux == 0)
	{
		printf("%d e primo\n", num);
	}
	else
	{
		printf("%d nao e primo\n", num);
	}
}
int main()
// Fazer um programa que leia um valor e chame uma função para dizer se o
// número é primo ou não. O programa deverá ser finalizado quando o valor 0
// (zero) for digitado. Garanta que o número lido é positivo ou zero.

{
	int num;
	do
	{
		scanf("%d", &num);
		if (num == 0)
		{
			break;
		}

		if (num < 0)
		{
			printf("digite 0 ou um numero maior\n");
		}
		else
		{
			primo(num);
		}

	} while (num != 0);

	return 0;
}