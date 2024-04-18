#include <stdio.h>
#include <stdlib.h>
int jogada()
{
	int moeda;
	moeda = rand();
	if (moeda % 2 == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int main()
// Escreva um programa que simule o lançamento de uma moeda.
// Para cada lançamento de moeda o programa deve imprimir CARA ou COROA.
// Deixe o programa lançar 100 moedas e conte o número de vezes que cada lado aparece.
// Imprima os resultados. O programa deve chamar uma função separada chamada
// jogada que não utiliza argumentos e retorna 0 para cara e 1 para coroa.

{
	int cara = 0, coroa = 0;

	for (int i = 0; i < 100; i++)
	{
		if (jogada() == 1)
		{
			cara++;
		}
		else
		{
			coroa++;
		}
	}
	printf("cara: %d ", cara);
	printf("coroa: %d ", coroa);

	return 0;
}