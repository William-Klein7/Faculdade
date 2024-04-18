#include <stdio.h>
#include <stdlib.h>
// Escreva um programa que aloque dinamicamente uma estrutura para armazenar nome e endereco de uma pessoa.
// Faça o usuário informar esses dados.
// Preencha os campos da estrutura com a entrada fornecida pelo usuário. A seguir mostre os campos dessa estrutura.

struct Pessoa
{
	char nome[50];
	char endereco[100];
};

int main()
{
	struct Pessoa *pessoa = (struct Pessoa *)malloc(sizeof(struct Pessoa));

	printf("Digite o nome: ");
	fgets(pessoa->nome, sizeof(pessoa->nome), stdin);

	printf("Digite o endereco: ");
	fgets(pessoa->endereco, sizeof(pessoa->endereco), stdin);

	printf("\nDados da Pessoa:\n");
	printf("Nome: %s", pessoa->nome);
	printf("Endereco: %s", pessoa->endereco);

	free(pessoa);
	return 0;
}