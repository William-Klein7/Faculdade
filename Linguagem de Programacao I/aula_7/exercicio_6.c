#include <stdio.h>
int main()

// Sendo A um vetor com 100 elementos, mostre o conteúdo do vetor utilizando
// 4 ponteiros (p,q,r,s) simultâneos posicionados em:

// - p posição 0

// - q posição 25

// - r  posição 50

// - s posição 75.

{
	int vet[100];
	int *p, *q, *r, *s;
	p = vet;
	for (int i = 0; i < 100; i++)
	{
		scanf("%d", p++);
	}
	p = vet;
	q = vet + 25;
	r = vet + 50;
	s = vet + 75;

	printf("p ");
	printf("q ");
	printf("r ");
	printf("s \n");
	for (int i = 0; i < 25; i++)
	{
		printf("%d ", *p++);
		printf("%d ", *q++);
		printf("%d ", *r++);
		printf("%d \n", *s++);
	}

	return 0;
}