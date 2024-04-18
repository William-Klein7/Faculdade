#include <stdio.h>
// Escreva um programa que imprime na tela a série de FIBONACCI até um numero dado.
// Esta séria começa com 1 e 1 e os próximos números são obtidos pela soma dos anteriores.
// Ex: 1 1 2 3 5 8 13 21 34 55
void printFibonacciSeries(int n) {
    int a = 1, b = 1, c;

    if (n >= 1) {
        printf("%d ", a);
    }
    if (n >= 2) {
        printf("%d ", b);
    }

    for (int i = 3; i <= n; i++) {
        c = a + b;
        printf("%d ", c);
        a = b;
        b = c;
    }
}

int main() {
    int n;

    printf("Digite um número para gerar a série de Fibonacci até esse ponto: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Por favor, digite um número maior ou igual a 1.\n");
        return 1;
    }

    printf("Série de Fibonacci até %d:\n", n);
    printFibonacciSeries(n);
    printf("\n");

    return 0;
}
