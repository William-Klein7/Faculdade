#include <stdio.h>
#include <math.h>
int main()
// Escreva um programa que leia a altura e o raio de um cilindro circular.
// A seguir crie ponteiros e aponte eles para cada uma dessas variaveis.
// Utilizando esses ponteiros imprima o volume do cilindro,
// segundo a fórmula:   volume = pi * (raio * raio) * altura   ,     onde pi = 3.14

{
	float raio, alt, volume = 0, pi = 3.14;
	printf("Digite o raio:");
	scanf("%f", &raio);
	float *pRaio = &raio;

	printf("Digite a altura:");
	scanf("%f", &alt);
	float *pAlt = &alt;

	volume = pi * pow(*pRaio, 2) * *pAlt;

	printf("volume do cilindro %.2f", volume);

	return 0;
}