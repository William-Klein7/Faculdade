#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Escreva um programa que faça o jogador "adivinhar um número" da
// forma como segue: Seu programa escolhe um número para ser adivinhado selecionando
// um inteiro entre 0 e 50. O programa então escreve:

// Tenho um número de 0 a 50
// Voce pode adivinhar meu número?
// Por favor digite seu palpite

// O jogador digita então o primeiro palpite. O programa fornece uma das seguintes respostas:

// 1 - Excelente! Voce adivinhou o número
// 2 - Muito baixo. Tente novamente
// 3- Muito alto. Tente novamente

// Se o palpite do jogar estive errado o programa deve fazer um loop até que o jogador
// acerte o número. Seu programa deve continuar dizendo muito alto ou muito baixo para ajudar
// o jogador a chegar a uma resposta. Obrigatoriamente voce deve utilizar funções.

void conferNumber(int num, int palpite)
{
	while (1)
	{
		if (num > palpite)
		{
			printf("Muito baixo. Tente novamente \n");
			scanf("%d", &palpite);
		}
		else if (num < palpite)
		{
			printf("Muito alto. Tente novamente \n");
			scanf("%d", &palpite);
		}
		else
		{
			printf("Excelente! Voce adivinhou o numero \n");
			break;
		}
	}
}
int main()

{
	int num, numJ = 0;
	srand(time(0));
	num = rand() % 51;

	printf("Tenho um numero de 0 a 50 \nVoce pode adivinhar meu numero? \nPor favor digite seu palpite:");
	scanf("%d", &numJ);

	conferNumber(num, numJ);

	return 0;
}