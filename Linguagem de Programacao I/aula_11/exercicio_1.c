#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Faça um programa que através de uma função leia uma struct de dados chamada pessoa
// e contém o nome, idade e endereco.
// A seguir chame outra  função que deverá imprimir o conteúdo da struct lida anteriormente.

// Definindo a struct Pessoa
struct Pessoa
{
    char nome[50];
    int idade;
    char endereco[100];
};

// Função para ler os dados da struct Pessoa
struct Pessoa lerPessoa()
{
    struct Pessoa p;

    printf("Digite o nome: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0'; // Remover a quebra de linha

    printf("Digite a idade: ");
    scanf("%d", &p.idade);
    while (getchar() != '\n')
        ; // Limpar o buffer de entrada

    printf("Digite o endereco: ");
    fgets(p.endereco, sizeof(p.endereco), stdin);
    p.endereco[strcspn(p.endereco, "\n")] = '\0'; // Remover a quebra de linha

    return p;
}

// Função para imprimir os dados da struct Pessoa
void imprimirPessoa(struct Pessoa p)
{
    printf("Nome: %s\n", p.nome);
    printf("Idade: %d\n", p.idade);
    printf("Endereco: %s\n", p.endereco);
}

int main()
{
    // Chamando a função para ler os dados da struct
    struct Pessoa pessoa = lerPessoa();

    // Chamando a função para imprimir os dados da struct
    imprimirPessoa(pessoa);
    return 0;
}
