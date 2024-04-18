#include <stdio.h>

// Escreva um programa que inverta as posições de um array de tamanho 10 usando ponteiros

void functroca(int *a, int *b)
{
	int troca = *a;
	*a = *b;
	*b = troca;
}

int main()
{
	int vet[10];
	int *ptr, *ptrAux;
	ptr = vet;
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", ptr++);
	}
	ptr = vet;
	ptrAux = vet + 9;

	while (ptr > ptrAux)
	{
		functroca(ptr, ptrAux);
		ptr++;
		ptrAux--;
	}

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", *ptr);
		ptr++;
	}

	return 0;
}