#include <stdio.h>
#include <string.h>
int main()
// Faça um programa que leia uma frase fornecida pelo usuário e imprima a 
// frase letra por letra. Dica: Utilize um laço de repetição para isso

{
	char frase[50];

	fgets(frase ,sizeof(frase), stdin);
	int tamanhoF = strlen(frase);
	for (int i = 0; i < tamanhoF-1; i++)
	{
		printf("%c\n", frase[i]);
	}
	

	return 0;
}