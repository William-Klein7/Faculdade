#include <stdio.h>

// Faca um programa que aloque dinamicamente um array de inteiros com tamanho fornecido pelo usuario.
// A seguir leia valores para esse array.
// A seguir percorra o array contando quantos elementos positivos e negativos foram informados

int main()

{
	int tam, qNeg = 0, qPos = 0;
	printf("Quantos numeros quer informar?");
	scanf("%d", &tam);

	int vet[tam];
	int *pVet = vet;

	printf("Digite os valores:");
	for (int i = 0; i < tam; i++)
	{
		scanf("%d", pVet);
		if (*pVet < 0)
		{
			qNeg++;
		}
		else
		{
			qPos++;
		}
		pVet++;
	}
	printf("Quantia de positivos: %d\n", qPos);
	printf("Quantia de negativos: %d", qNeg);

	return 0;
}