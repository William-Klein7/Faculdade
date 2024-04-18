#include <stdio.h>
int main()
// Escreva   um programa que leia dois números em ponto flutuante e
// forneça o resultado da soma formatado com duas casas decimais

{
	float n1, n2, soma = 0;

	printf("Insira o primeiro valor: ");
	scanf("%f", &n1);
	printf("Insira o segundo valor: ");
	scanf("%f", &n2);

	soma = n1 + n2;

	printf("A soma e %.2f", soma);

	return 0;
}