#include <stdio.h>
int main()
// Escreva um programa que dados 15 números,
// imprima seus quadrados, obs: você não precisa necessariamente imprimir no final.

{

	int num, vet[15];
	for (int i = 0; i < 15; i++)
	{
		scanf("%d", &num);
		vet[i] = num * num;
	}
	printf("o quadrado dos numeros e:\n");
	for (int i = 0; i < 15; i++)
	{
		printf("%d ", vet[i]);
	}

	return 0;
}