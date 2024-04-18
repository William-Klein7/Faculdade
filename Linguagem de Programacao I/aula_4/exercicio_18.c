#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
// Faca um programa que leia uma string fornecida pelo usuario. A seguir leia um caracter.
// Verifique a existencia desse caracter na string e cada vez que o mesmo for encontrado
// deve ser trocado por '*'. Mostre o resultado. (limite o tamanho em 50 caracteres)

{
	char str[50], caractere;

	printf("Digite uma str: ");
	fgets(str, sizeof(str), stdin);

	printf("\nDigite um caractere: ");

	scanf("%c", &caractere);

	str[strcspn(str, "\n")] = '\0';

	int tamanhoString = strlen(str);

	for (int i = 0; i < tamanhoString; i++)
	{

		if (caractere == str[i])
		{
			str[i] = '*';
		}
	}

	printf("\nSubstuindo %c por *: \n", caractere);

	printf("\n  %s", str);
	return 0;
}