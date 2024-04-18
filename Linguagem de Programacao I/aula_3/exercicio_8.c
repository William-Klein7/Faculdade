#include <stdio.h>
int main()
// Entrar com nome, idade e sexo de 5 pessoas,
// e imprimir na tela o nome dos homens maiores de 21 anos.

{
	char nome[50];
	int idade;
	char sexo;

	for (int i = 0; i < 5; i++)
	{
		printf("Digite o nome da pessoa %d: ", i + 1);
		scanf("%s", nome);

		printf("Digite a idade da pessoa %d: ", i + 1);
		scanf("%d", &idade);

		printf("Digite o sexo da pessoa %d (M/F): ", i + 1);
		scanf(" %c", &sexo);

		if (sexo == 'M' && idade > 21)
		{
			printf("Nome: %s\n", nome);
		}
	}
	return 0;
}