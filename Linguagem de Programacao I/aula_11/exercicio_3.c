#include <stdio.h>
#include <stdlib.h>
// Escreva uma funcao que receba dois inteiros e armazene-os em uma estrutura (campos x e y).
// A seguir copie essa estrutura para uma segunda estutura. Mostre essa segunda estrutura
struct Coordenadas
{
    int x;
    int y;
};

// Função para copiar estruturas
struct Coordenadas copiarEstrutura(struct Coordenadas original)
{
    struct Coordenadas copia;
    copia.x = original.y;
    copia.y = original.x;
    return copia;
}

int main()
{
    // Criando e inicializando a primeira estrutura
    struct Coordenadas primeiraEstrutura;
    printf("Digite o valor de x: ");
    scanf("%d", &primeiraEstrutura.x);

    printf("Digite o valor de y: ");
    scanf("%d", &primeiraEstrutura.y);

    // Copiando a estrutura para uma segunda estrutura
    struct Coordenadas segundaEstrutura = copiarEstrutura(primeiraEstrutura);

    printf("\nPrimeira Estrutura:\n");
    printf("x: %d\n", primeiraEstrutura.x);
    printf("y: %d\n", primeiraEstrutura.y);

    printf("\nSegunda Estrutura:\n");
    printf("x: %d\n", segundaEstrutura.x);
    printf("y: %d\n", segundaEstrutura.y);

    return 0;
}