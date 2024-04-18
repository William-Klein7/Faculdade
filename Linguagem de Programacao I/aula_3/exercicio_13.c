#include <stdio.h>
int main()
// Infelizmente o algoritmo que calcula o valor do táxi tem as variáveis tempo e distância,
// ou seja, mesmo que o carro esteja parado em um sinal, a conta do taxi vai aumentando.
// Faça um programa que dado o tempo e a distância, calcule o valor a ser pago.
// O custo é 0,02 centavos por segundo e R$ 1,00 por quilômetro.

{
    float tempo, distancia, valort = 0;
    printf("Digite o tempo: ");
    scanf("%f", &tempo);
    printf("\nDigite a distancia: ");
    scanf("%f", &distancia);

    valort = tempo * 0.02;

    printf("\nvalor a ser pago: R$%.2f", distancia+valort);

    return 0;
}