#include <stdio.h>
#define tam 5
// Escreva uma função que dados dois arrays A e B mostre quais os elementos de A existem em B.
// Atenção: os arrays A e B devem ser passados como parâmetros para a função

int conferArray(int A[], int tamanhoA, int B[], int tamanhoB)
{
	printf("Elementos de A que existem em B: ");
	for (int i = 0; i < tamanhoA; i++)
	{
		for (int j = 0; j < tamanhoB; j++)
		{
			if (A[i] == B[j])
			{
				printf("%d ", A[i]);
				break;
			}
		}
	}
	printf("\n");
}

int main()
{
	int A[tam], B[tam];
	int tamanhoA = sizeof(A) / sizeof(A[0]);
	int tamanhoB = sizeof(B) / sizeof(B[0]);

	printf("Digite %d valores para o vetor A:\n", tam);
	for (int i = 0; i < tam; i++)
	{
		scanf("%d", &A[i]);
	}

	printf("Digite %d valores para o vetor B:\n", tam);
	for (int i = 0; i < tam; i++)
	{
		scanf("%d", &B[i]);
	}

	conferArray(A, tamanhoA, B, tamanhoB);
	return 0;
}
