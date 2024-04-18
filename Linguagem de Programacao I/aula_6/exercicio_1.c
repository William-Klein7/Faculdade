#include <stdio.h>
int main()
// Faca um programa que leia um valor inteiro fornecido pelo usuario.
// Mostre o endereco de memoria dessa variavel e o seu conteudo.

{
	int x;

	scanf("%d", &x);
	int *px = &x;
	printf("endereco de memoria do valor e: %p", px);

	return 0;
}