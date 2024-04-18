#include <stdio.h>
#include <stdlib.h>
int main()
// Inicialize um vetor de 10 posicoes de inteiros aleatoriamente. (use a funcao rand() ).
// Mostre  todo o vetor usando dois ponteiros : um começando do início do vetor e outro do final.

{
	int vet[10];
	int *ptr1, *ptr2;
	for (int i = 0; i < 10; i++)
	{
		vet[i] = rand();
	}
	ptr1 = vet;
	ptr2 = vet + 9;
	printf("vetor: ");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", ptr1++);
	}
	printf("\n");
	for (int i = 0; i < 10; i++)
	{
		printf("ptr1= %d ", *ptr1);
		printf("ptr2= %d\n", *ptr2);
		ptr1++;
		ptr2--;
	}

	return 0;
}