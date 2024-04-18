#include <stdio.h>
int main()
// Faca um programa que leia um vetor com 10 elementos positivos e/ou
// negativos e no final diga quantos elementos negativos e quantos positivos foram encontrados

{

	int vet[10], i, contp = 0, contn = 0;

	printf("Informe o vetor: ");

	for (i = 0; i < 10; i++)
	{
		scanf("%d", &vet[i]);
		if (vet[i] >= 0)
		{
			contp++;
		}
		else
		{
			contn++;
		}
	}

	printf("Pos: %d\n", contp);
	printf("Neg: %d", contn);

	return 0;
}