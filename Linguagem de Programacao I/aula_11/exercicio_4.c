#include <stdio.h>
#include <stdlib.h>
// Crie uma funcao que receba dois parametros inteiros e retorne a seguinte estrutura com
// os respectivos valores definidos

// struct retorno {
// int x = PARAMETRO RECEBIDO
// int y = PARAMETRO RECEBIDO
// }
// A seguir mostre os campos x e y da estrutura retornada
// Definindo a estrutura
struct Retorno
{
    int x;
    int y;
};

// Função que retorna uma estrutura com os parâmetros dados
struct Retorno criarEstrutura(int parametroX, int parametroY)
{
    struct Retorno resultado;
    resultado.x = parametroX;
    resultado.y = parametroY;
    return resultado;
}

int main()
{
    // Chamando a função para criar a estrutura
    struct Retorno resultado = criarEstrutura(10, 20);

    printf("x: %d\n", resultado.x);
    printf("y: %d\n", resultado.y);

    return 0;
}