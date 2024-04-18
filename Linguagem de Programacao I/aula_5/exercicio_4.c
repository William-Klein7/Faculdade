#include <stdio.h>
int main()
// Escreva um programa que some dois valores fornecidos pelo 
// usuário e mostre o resultado com 10 posições alinhadas a esquerda

{
	float n1, n2, soma = 0;

	printf("Insira o primeiro valor: ");
	scanf("%f", &n1);
	printf("Insira o segundo valor: ");
	scanf("%f", &n2);

	soma = n1 + n2;

	printf("A soma e %010.f", soma);
	return 0;
}