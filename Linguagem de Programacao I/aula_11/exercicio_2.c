#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Um comerciante deseja armazenar o nome e o valor de 10 produtos de seu estabelecimento.
// Monte um array de structs para armazena-los

struct Produto
{
    char nome[50];
    float valor;
};

int main()
{
    // Criando um array de structs para armazenar 10 produtos
    struct Produto produtos[10];

    // Preenchendo o array com dados
    for (int i = 0; i < 10; ++i)
    {
        printf("Digite o nome do produto %d: ", i + 1);
        fgets(produtos[i].nome, sizeof(produtos[i].nome), stdin);
        produtos[i].nome[strcspn(produtos[i].nome, "\n")] = '\0'; // Remover a quebra de linha

        printf("Digite o valor do produto %d: ", i + 1);
        scanf("%f", &produtos[i].valor);
        while (getchar() != '\n')
            ; // Limpar o buffer de entrada
    }

    // Exibindo os dados armazenados
    printf("\nProdutos Armazenados:\n");
    for (int i = 0; i < 10; ++i)
    {
        printf("Produto %d:\n", i + 1);
        printf("Nome: %s\n", produtos[i].nome);
        printf("Valor: R$ %.2f\n", produtos[i].valor);
        printf("\n");
    }

    return 0;
}