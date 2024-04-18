#include <stdio.h>
int main()
// Faca um programa que leia dois valores x e y e entao inverta os valores dessas variaveis
// ( x recebe y e y recebe x) usando ponteiros

{
	int x, y, aux;
	printf("digite um valor:");
	scanf("%d", &x);
	int *px = &x;

	printf("digite outro valor:");
	scanf("%d", &y);
	int *py = &y;

	printf(" valores antes da troca: %d, %d", x, y);

	aux = *px;
	*px = *py;
	*py = aux;

	printf(" valores trocados: %d, %d", x, y);

	return 0;
}