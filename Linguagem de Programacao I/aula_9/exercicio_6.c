#include <stdio.h>
#include <string.h>
// Faça um programa que leia duas strings e utilize uma função para
// determinar qual das duas strings possui o maior tamanho

int tamanhoMaiorString(const char *str1, const char *str2)
{
	int tamanhoStr1 = strlen(str1);
	int tamanhoStr2 = strlen(str2);

	if (tamanhoStr1 > tamanhoStr2)
	{
		return 1;
	}
	else if (tamanhoStr2 > tamanhoStr1)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

int main()
{
	char string1[100], string2[100];

	printf("Digite a primeira string: ");
	fgets(string1, sizeof(string1), stdin);
	string1[strcspn(string1, "\n")] = '\0';

	printf("Digite a segunda string: ");
	fgets(string2, sizeof(string2), stdin);
	string2[strcspn(string2, "\n")] = '\0';

	int resultado = tamanhoMaiorString(string1, string2);

	if (resultado == 1)
	{
		printf("A primeira string e maior.\n");
	}
	else if (resultado == 2)
	{
		printf("A segunda string e maior.\n");
	}
	else
	{
		printf("As duas strings tem o mesmo tamanho.\n");
	}

	return 0;
}