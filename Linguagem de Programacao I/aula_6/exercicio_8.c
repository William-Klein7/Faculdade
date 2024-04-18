#include <stdio.h>
int main()
// Faça um programa que calcule a média de idade de 10 pessoas. Atenção:  ATENCAO:
// Todas as variaveis usadas no programa devem ser manipuladas através de ponteiros

{
	int idade;
	float media = 0;

	int *p;
	float *pMedia = &media;

	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &idade);
		p = &idade;
		*pMedia += *p;
	}

	printf("A media das idades de 10 pessoas e: %2.f", (*pMedia) / 10);

	return 0;
}