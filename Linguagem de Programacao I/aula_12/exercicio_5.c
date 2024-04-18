#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define count 10
// Escreva um programa que aloque dinamicamente um array de struct de 10 posicoes para armazenar pessoas
// (cada pessoa fica armazenada em uma posicao). A struct deve conter nome, idade e sexo de cada pessoa.

typedef struct
{
    char nome[50];
    int idade;
    char sexo;
} pessoa;

int main()
{
    pessoa *pessoas = (pessoa *)malloc(count * sizeof(pessoa));

    for (int i = 0; i < count; i++)
    {
        printf("Digite o nome da pessoa %d: ", i + 1);
        fgets(pessoas[i].nome, sizeof(pessoas[i].nome), stdin);
        pessoas[i].nome[strcspn(pessoas[i].nome, "\n")] = '\0';

        printf("Digite a idade da pessoa %d: ", i + 1);
        scanf("%d", &pessoas[i].idade);

        printf("Digite o sexo da pessoa %d: ", i + 1);
        scanf(" %c", &pessoas[i].sexo);
        while (getchar() != '\n');
    }

    printf("\nDados das Pessoas:\n");
    for (int i = 0; i < count; i++)
    {
        printf("Pessoa %d - Nome: %s, Idade: %d, Sexo: %c\n", i + 1, pessoas[i].nome, pessoas[i].idade, pessoas[i].sexo);
    }
    free(pessoas);
    return 0;
}
