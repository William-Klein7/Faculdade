#include <stdio.h>
int main()
// Faça um programa que leia um valor do usuário e mostre o seu resultado em octal

{
	 int valor;

    printf("Digite um valor inteiro: ");
    scanf("%d", &valor);

    printf("O valor em hexadecimal e: %o\n", valor);

	return 0;
}