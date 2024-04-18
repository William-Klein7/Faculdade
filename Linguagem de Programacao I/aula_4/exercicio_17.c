#include <stdio.h>
#include <ctype.h>
int main()
// Faca um programa que leia uma string fornecida pelo usuario. A seguir, converta
// todas as consoantes para maiusculas e as vogais para minusculas (limite o tamanho em 50 caracteres)

{
	char str[256], result[51];
	int i;

	printf("Digite uma string: ");
	fgets(str, sizeof(str), stdin);

	for (i = 0; i < 50 && str[i]; i++)
	{

		if (isalpha(str[i]))
		{
			if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
			{
				result[i] = tolower(str[i]);
			}
			else
			{
				result[i] = toupper(str[i]);
			}
		}
		else
		{
			result[i] = str[i];
		}
	}
	result[i] = '\0';

	printf("Resultado: %s\n", result);
	return 0;
}