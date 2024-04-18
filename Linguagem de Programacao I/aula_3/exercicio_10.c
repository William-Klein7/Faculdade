#include <stdio.h>
int main()
// Entrar com 20 números e imprimir a soma dos positivos e o total de números negativos.

{
	int num, soma = 0, cont = 0;

	for (int i = 0; i < 20; i++)
	{
		scanf("%d", &num);
		if (num >= 0)
		{
			soma += num;
		}
		else
		{
			cont++;
		}
	}

	printf("soma dos positivos = %d \n total de numeros negativos = %d", soma, cont);

	return 0;
}