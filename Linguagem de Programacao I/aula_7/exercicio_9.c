#include <stdio.h>
int main()

// Faça um programa que efetue a soma dos valores de cada posição de dois
// arrays 4 x 4 e armazene em um terceiro array de 4 x 4 o resultado. Utilize somente ponteiros.

{
	int matriz1[4][4], matriz2[4][4], resultado[4][4];

	printf("digite a primeira matrix:");
	int *ptr1 = &matriz1[0][0];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			scanf("%d", ptr1++);
		}
	}
	ptr1 = &matriz1[0][0];

	printf("digite a segunda matrix:");
	int *ptr2 = &matriz2[0][0];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			scanf("%d", ptr2++);
		}
	}

	ptr2 = &matriz2[0][0];
	int *ptrResultado = &resultado[0][0];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			*ptrResultado = *ptr1 + *ptr2;
			ptr1++;
			ptr2++;
			ptrResultado++;
		}
	}

	int *ptrSaida = &resultado[0][0];
	printf("Resultado:\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", *ptrSaida++);
		}
		printf("\n");
	}

	return 0;
}