#include <stdio.h>
int main()
// Entrar com 15 números e imprimir quantos números maiores que 30 foram digitados.

{
	int num, cont = 0;

	for (int i = 0; i < 15; i++)
	{
		scanf("%d", &num);
		if (num > 30)
		{
			cont++;
		}
	}
	printf("foram digitados %d numero(s) maiores que 30", cont);

	return 0;
}